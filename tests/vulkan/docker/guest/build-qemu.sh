#!/bin/bash
# Build our QEMU

set -ex

pushd $ROOT/qemu
mkdir -p build/docker
pushd build/docker

if [ ! -f build.ninja ]; then
    ../../configure \
        --target-list=x86_64-softmmu \
        --enable-kvm \
        --disable-werror \
        --enable-opengl \
        --enable-virglrenderer \
        --disable-sdl \
        --disable-gtk \
        --disable-debug-info
fi
ninja qemu-system-x86_64 && ninja install

popd
popd
