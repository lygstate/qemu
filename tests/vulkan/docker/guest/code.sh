#!/bin/bash
set -ex

bash run-guest.sh

export IMG=$ROOT/image/ubuntu.qcow2
export ISO=$ROOT/image/ubuntu-21.10-desktop-amd64.iso

# Need this env variable to make SDL work with wayland
export SDL_VIDEODRIVER=wayland

# Debug settings for QEMU
echo "add-auto-load-safe-path /qemu/.gdbinit" >> /root/.gdbinit

cp /rootfs.cpio.gz $ROOT/image/rootfs.cpio.gz

export DISPLAY_OPTIONS="-device virtio-vga-gl,context_init=true,blob=true,hostmem=1G 
-vga none 
-display egl-headless,gl=es,show-cursor=on -vnc :0"

# Find "DisplayOptions" in ui.json
# -display egl-headless,gl=es,show-cursor=on -vnc :0"
# -display sdl,gl=es,show-cursor=on"

# export DISPLAY_OPTIONS="-display sdl"
