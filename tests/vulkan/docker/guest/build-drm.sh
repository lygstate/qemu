#!/bin/bash
# Build our drm

set -ex
pushd $ROOT/drm
git  reset --hard libdrm-2.4.110
if [ ! -f build/docker/build.ninja ]; then
    meson build/docker -Dbuildtype=debugoptimized -Dprefix=/usr
else
    meson --reconfigure build/docker -Dbuildtype=debugoptimized -Dprefix=/usr
fi
ninja -C build/docker install
DESTDIR=$ROOT/install ninja -C build/docker install
popd
