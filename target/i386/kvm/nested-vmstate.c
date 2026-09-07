#include "qemu/osdep.h"
#include "cpu.h"
#include "migration/vmstate.h"
#include "qemu/error-report.h"
#include "kvm_i386.h"
#include "system/kvm.h"

#include <linux/kvm.h>

static bool vmx_vmcs12_needed(void *opaque)
{
    struct kvm_nested_state *nested_state = opaque;
    return (nested_state->size >
            offsetof(struct kvm_nested_state, data.vmx[0].vmcs12));
}

static const VMStateDescription vmstate_vmx_vmcs12 = {
    .name = "cpu/kvm_nested_state/vmx/vmcs12",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = vmx_vmcs12_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT8_ARRAY(data.vmx[0].vmcs12,
                            struct kvm_nested_state,
                            KVM_STATE_NESTED_VMX_VMCS_SIZE),
        VMSTATE_END_OF_LIST()
    }
};

static bool vmx_shadow_vmcs12_needed(void *opaque)
{
    struct kvm_nested_state *nested_state = opaque;
    return (nested_state->size >
            offsetof(struct kvm_nested_state, data.vmx[0].shadow_vmcs12));
}

static const VMStateDescription vmstate_vmx_shadow_vmcs12 = {
    .name = "cpu/kvm_nested_state/vmx/shadow_vmcs12",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = vmx_shadow_vmcs12_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT8_ARRAY(data.vmx[0].shadow_vmcs12,
                            struct kvm_nested_state,
                            KVM_STATE_NESTED_VMX_VMCS_SIZE),
        VMSTATE_END_OF_LIST()
    }
};

static bool vmx_nested_state_needed(void *opaque)
{
    struct kvm_nested_state *nested_state = opaque;

    return (nested_state->format == KVM_STATE_NESTED_FORMAT_VMX &&
            nested_state->hdr.vmx.vmxon_pa != -1ull);
}

static const VMStateDescription vmstate_vmx_nested_state = {
    .name = "cpu/kvm_nested_state/vmx",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = vmx_nested_state_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_U64(hdr.vmx.vmxon_pa, struct kvm_nested_state),
        VMSTATE_U64(hdr.vmx.vmcs12_pa, struct kvm_nested_state),
        VMSTATE_U16(hdr.vmx.smm.flags, struct kvm_nested_state),
        VMSTATE_END_OF_LIST()
    },
    .subsections = (const VMStateDescription * const []) {
        &vmstate_vmx_vmcs12,
        &vmstate_vmx_shadow_vmcs12,
        NULL,
    }
};

static bool svm_nested_state_needed(void *opaque)
{
    struct kvm_nested_state *nested_state = opaque;

    /*
     * HF_GUEST_MASK and HF2_GIF_MASK are already serialized
     * via hflags and hflags2, all that's left is the opaque
     * nested state blob.
     */
    return (nested_state->format == KVM_STATE_NESTED_FORMAT_SVM &&
            nested_state->size > offsetof(struct kvm_nested_state, data));
}

static const VMStateDescription vmstate_svm_nested_state = {
    .name = "cpu/kvm_nested_state/svm",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = svm_nested_state_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_U64(hdr.svm.vmcb_pa, struct kvm_nested_state),
        VMSTATE_UINT8_ARRAY(data.svm[0].vmcb12,
                            struct kvm_nested_state,
                            KVM_STATE_NESTED_SVM_VMCB_SIZE),
        VMSTATE_END_OF_LIST()
    }
};

static bool nested_state_needed(void *opaque)
{
    X86CPU *cpu = opaque;
    CPUX86State *env = &cpu->env;

    return (env->nested_state &&
            (vmx_nested_state_needed(env->nested_state) ||
             svm_nested_state_needed(env->nested_state)));
}

static int nested_state_post_load(void *opaque, int version_id)
{
    X86CPU *cpu = opaque;
    CPUX86State *env = &cpu->env;
    struct kvm_nested_state *nested_state = env->nested_state;
    int min_nested_state_len = offsetof(struct kvm_nested_state, data);
    int max_nested_state_len = kvm_max_nested_state_length();

    /*
     * If our kernel don't support setting nested state
     * and we have received nested state from migration stream,
     * we need to fail migration
     */
    if (max_nested_state_len <= 0) {
        error_report("Received nested state when kernel cannot restore it");
        return -EINVAL;
    }

    /*
     * Verify that the size of received nested_state struct
     * at least cover required header and is not larger
     * than the max size that our kernel support
     */
    if (nested_state->size < min_nested_state_len) {
        error_report("Received nested state size less than min: "
                     "len=%d, min=%d",
                     nested_state->size, min_nested_state_len);
        return -EINVAL;
    }
    if (nested_state->size > max_nested_state_len) {
        error_report("Received unsupported nested state size: "
                     "nested_state->size=%d, max=%d",
                     nested_state->size, max_nested_state_len);
        return -EINVAL;
    }

    /* Verify format is valid */
    if ((nested_state->format != KVM_STATE_NESTED_FORMAT_VMX) &&
        (nested_state->format != KVM_STATE_NESTED_FORMAT_SVM)) {
        error_report("Received invalid nested state format: %d",
                     nested_state->format);
        return -EINVAL;
    }

    return 0;
}

static const VMStateDescription vmstate_kvm_nested_state = {
    .name = "cpu/kvm_nested_state",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (const VMStateField[]) {
        VMSTATE_U16(flags, struct kvm_nested_state),
        VMSTATE_U16(format, struct kvm_nested_state),
        VMSTATE_U32(size, struct kvm_nested_state),
        VMSTATE_END_OF_LIST()
    },
    .subsections = (const VMStateDescription * const []) {
        &vmstate_vmx_nested_state,
        &vmstate_svm_nested_state,
        NULL
    }
};

const VMStateDescription vmstate_nested_state = {
    .name = "cpu/nested_state",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = nested_state_needed,
    .post_load = nested_state_post_load,
    .fields = (const VMStateField[]) {
        VMSTATE_STRUCT_POINTER(env.nested_state, X86CPU,
                vmstate_kvm_nested_state,
                struct kvm_nested_state),
        VMSTATE_END_OF_LIST()
    }
};
