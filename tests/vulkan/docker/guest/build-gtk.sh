#!/bin/bash
# Build our GTK

set -ex

pushd /gtk

mkdir -p build/docker

if [ ! -f build/docker/build.ninja ]; then
    meson build/docker \
        -Dprefix=/usr/local \
        -Dbuildtype=debugoptimized
else
    meson --reconfigure build/docker \
        -Dprefix=/usr/local \
        -Dbuildtype=debugoptimized
fi

ninja -C build/docker install

popd

