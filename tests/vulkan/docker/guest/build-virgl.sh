#!/bin/bash
# Build our virglrenderer

set -ex

pushd $ROOT/virglrenderer

mkdir -p build/docker

if [ ! -f build/docker/build.ninja ]; then
    meson build/docker \
        -Dprefix=/usr \
        -Dplatforms=egl \
        -Dvenus-experimental=true \
        -Dminigbm_allocation=false \
        -Dbuildtype=debugoptimized
else
    meson --reconfigure build/docker \
        -Dprefix=/usr \
        -Dplatforms=egl \
        -Dvenus-experimental=true \
        -Dminigbm_allocation=false \
        -Dbuildtype=debugoptimized
fi

ninja -C build/docker install

popd
