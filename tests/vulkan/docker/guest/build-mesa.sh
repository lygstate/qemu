#!/bin/bash
# Build our mesa

set -ex

pushd $ROOT/mesa

mkdir -p build/docker

if [ ! -f build/docker/build.ninja ]; then
    meson build/docker \
        -Dprefix=/usr \
        -Dgallium-drivers=swrast \
        -Dbuildtype=debugoptimized \
        -Dllvm=enabled \
        -Dglx=dri \
        -Degl=enabled \
        -Dgbm=enabled \
        -Dgallium-vdpau=disabled \
        -Dvulkan-drivers=swrast \
        -Dvalgrind=disabled
else
    meson --reconfigure build/docker \
        -Dprefix=/usr \
        -Dgallium-drivers=swrast \
        -Dbuildtype=debugoptimized \
        -Dllvm=enabled \
        -Dglx=dri \
        -Degl=enabled \
        -Dgbm=enabled \
        -Dgallium-vdpau=disabled \
        -Dvulkan-drivers=swrast \
        -Dvalgrind=disabled
fi
ninja -C build/docker install
popd


pushd $ROOT/mesa

mkdir -p build/guest

if [ ! -f build/guest/build.ninja ]; then
    meson build/guest \
        -Dprefix=/usr \
        -Dgallium-drivers=swrast,zink \
        -Dbuildtype=debugoptimized \
        -Dllvm=enabled \
        -Degl=enabled \
        -Dgbm=enabled \
        -Dgallium-vdpau=disabled \
        -Dvulkan-drivers=virtio-experimental \
        -Dvalgrind=disabled
else
    meson --reconfigure build/guest \
        -Dprefix=/usr \
        -Dgallium-drivers=swrast,zink \
        -Dbuildtype=debugoptimized \
        -Dllvm=enabled \
        -Degl=enabled \
        -Dgbm=enabled \
        -Dgallium-vdpau=disabled \
        -Dvulkan-drivers=virtio-experimental \
        -Dvalgrind=disabled
fi
DESTDIR=$ROOT/install ninja -C build/guest install
popd
