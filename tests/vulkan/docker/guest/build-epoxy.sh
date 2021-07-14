#!/bin/bash
# Build our libepoxy

set -ex
pushd /libepoxy
meson build/docker -Dprefix=/usr/local
ninja -C build/docker install
popd
