#!/bin/bash
# Build our wayland-protocols

set -ex
pushd $ROOT/wayland-protocols
git reset --hard 1.25
if [ ! -f build/docker/build.ninja ]; then
    meson build/docker -Dbuildtype=debugoptimized -Dprefix=/usr
else
    meson --reconfigure build/docker -Dbuildtype=debugoptimized -Dprefix=/usr
fi
ninja -C build/docker install
DESTDIR=$ROOT/install ninja -C build/docker install
popd
