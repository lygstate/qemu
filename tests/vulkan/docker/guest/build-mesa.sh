#!/bin/bash
# Build our mesa

set -ex

pushd /mesa

mkdir -p build/docker

if [ ! -f build/docker/build.ninja ]; then
    meson build/docker \
        -Dprefix=/usr/local \
        -Ddri-drivers=i965 \
        -Dgallium-drivers=swrast,virgl,iris \
        -Dbuildtype=debugoptimized \
        -Dllvm=enabled \
        -Dglx=dri \
        -Degl=enabled \
        -Degl-native-platforms=x11,drm,wayland \
        -Dgbm=enabled \
        -Dgallium-vdpau=disabled \
        -Dgallium-vs=disabled \
        -Dvulkan-drivers=swrast,intel,virtio-experimental \
        -Dvalgrind=disabled
else
    meson --reconfigure build/docker \
        -Dprefix=/usr/local \
        -Ddri-drivers=i965 \
        -Dgallium-drivers=swrast,virgl,iris \
        -Dbuildtype=debugoptimized \
        -Dllvm=enabled \
        -Dglx=dri \
        -Degl=enabled \
        -Degl-native-platforms=x11,drm,wayland \
        -Dgbm=enabled \
        -Dgallium-vdpau=disabled \
        -Dgallium-vs=disabled \
        -Dvulkan-drivers=swrast,intel,virtio-experimental \
        -Dvalgrind=disabled
fi
ninja -C build/docker install

popd
