#!/bin/bash

set -ex

pushd $ROOT/qemu
export EGL_LOG_LEVEL=debug
# If the image has not been created yet, we create
# it and start the ubuntu installation from cdrom
if [ ! -f $IMG ]; then
  bash create-image.sh

  # No need for graphics acceleration at the moment
  build/docker/qemu-system-x86_64 \
    -enable-kvm \
    -M q35 \
    -smp 1 \
    -m 4G \
    -net nic,model=virtio \
    -net user,hostfwd=tcp::22-:22 \
    -hda $IMG \
    -display sdl \
    -boot d -cdrom $ISO
else
  vulkaninfo | grep deviceName

  # handle SIGUSR1 noprint nostop
  # Uncomment to start QEMU with gdb
  # gdb --args \
  gdbserver 0.0.0.0:1235 \
  build/docker/qemu-system-x86_64 \
    -enable-kvm \
    -M q35 \
    -smp 1 \
    -m 4G \
    -cpu host \
    -net nic,model=virtio \
    -net user,hostfwd=tcp::22-:22,hostfwd=tcp::1234-:1234 \
    -hda $IMG \
    -initrd $ROOT/image/rootfs.cpio.gz \
    -kernel $ROOT/kernel/arch/x86_64/boot/bzImage \
    -append "root=/dev/sda3 nokaslr" \
    -usb -device usb-tablet \
    -object memory-backend-memfd,id=mem1,size=4G \
    -machine memory-backend=mem1 \
    $DISPLAY_OPTIONS \
    -d guest_errors
    # -s -S \
fi

popd
