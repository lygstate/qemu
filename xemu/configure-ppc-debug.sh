#!/bin/sh

# ../xemu/configure-ppc-debug.sh
#  pacman -S mingw-w64-x86_64-libepoxy
../configure \
  --python=python3 \
  --enable-gtk --enable-sdl \
  --prefix=${XEMU_DEV_DIR}/xemu-dist${MINGW_PREFIX} \
  --disable-docs \
  --enable-stack-protector \
  --enable-gnutls \
  --enable-nettle \
  --enable-vnc \
  --enable-opengl \
  --enable-vnc-sasl \
  --enable-vnc-jpeg \
  --enable-vnc-png \
  --enable-membarrier \
  --enable-slirp=git \
  --disable-kvm \
  --enable-hax \
  --enable-whpx \
  --disable-spice \
  --enable-lzo \
  --enable-snappy \
  --enable-bzip2 \
  --enable-vdi \
  --enable-qcow1 \
  --enable-tools \
  --enable-libusb \
  --enable-usb-redir \
  --enable-libnfs \
  --enable-libssh \
  --target-list=x86_64-softmmu,i386-softmmu,arm-softmmu,aarch64-softmmu,ppc-softmmu,ppc64-softmmu \
  --disable-plugins --disable-modules \
  --enable-debug-info --enable-debug

ninja
# python ../xemu/list-objs.py
