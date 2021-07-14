#!/bin/bash

set -ex

pushd /qemu

IMG=/image/ubuntu.qcow2
ISO=/image/ubuntu-21.04-desktop-amd64.iso

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
    -display gtk \
    -boot d -cdrom $ISO
else
  # Debug settings for QEMU
  echo "add-auto-load-safe-path /qemu/.gdbinit" >> /root/.gdbinit

  cp /rootfs.cpio.gz /image/rootfs.cpio.gz

  vulkaninfo | grep deviceName

  export LIBGL_DRIVERS_PATH=/usr/local/lib/x86_64-linux-gnu/dri
  # Must use iris for GL_EXT_memory_object
  export MESA_LOADER_DRIVER_OVVERIDE=iris
  
  # Need this env variable to make SDL work with wayland
  export SDL_VIDEODRIVER=wayland

  export LD_LIBRARY_PATH="/usr/local/lib/x86_64-linux-gnu"

  # Uncomment to start QEMU with gdb
  # gdb --args \
   build/docker/qemu-system-x86_64 \
    -enable-kvm \
    -M q35 \
    -smp 1 \
    -m 4G \
    -cpu host \
    -net nic,model=virtio \
    -net user,hostfwd=tcp::22-:22,hostfwd=tcp::1234-:1234 \
    -hda $IMG \
    -initrd /image/rootfs.cpio.gz \
    -kernel /kernel/arch/x86_64/boot/bzImage \
    -append "root=/dev/sda3 nokaslr" \
    -display gtk,gl=on,show-cursor=on \
    -usb -device usb-tablet \
    -object memory-backend-memfd,id=mem1,size=4G \
    -machine memory-backend=mem1 \
    -device virtio-vga-gl,context_init=true,blob=true,hostmem=1G \
    -vga none \
    -d guest_errors
    #-display sdl,gl=on \
    #-s -S \
fi

popd
