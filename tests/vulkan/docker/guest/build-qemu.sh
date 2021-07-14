#!/bin/bash
# Build our QEMU

set -ex

pushd /qemu
mkdir -p build/docker
pushd build/docker

if [ ! -f build.ninja ]; then
    ../../configure \
        --target-list=x86_64-softmmu \
        --enable-kvm \
        --disable-werror \
        --enable-opengl \
        --enable-virglrenderer \
        --enable-sdl \
        --enable-gtk
fi
make -j8 qemu-system-x86_64 && make install

popd
popd
