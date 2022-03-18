#!/bin/bash
set -ex

rm -rf $ROOT/install
bash build-drm.sh
bash build-wayland-protocols.sh
bash build-wayland.sh
bash build-mesa.sh
rm -rf $ROOT/install.tar.gz
tar czv -C $ROOT/install -f $ROOT/install.tar.gz .
