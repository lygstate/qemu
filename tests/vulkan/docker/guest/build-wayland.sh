#!/bin/bash
# Build our wayland

set -ex
pushd $ROOT/wayland
git reset --hard 1.20.0
if [ ! -f build/docker/build.ninja ]; then
    meson build/docker -Dbuildtype=debugoptimized -Dprefix=/usr
else
    meson --reconfigure build/docker -Dbuildtype=debugoptimized -Dprefix=/usr
fi
ninja -C build/docker install
DESTDIR=$ROOT/install ninja -C build/docker install
popd
