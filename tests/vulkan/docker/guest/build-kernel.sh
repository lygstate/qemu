#!/bin/bash
# Build our kernel

set -ex

pushd /kernel

./scripts/kconfig/merge_config.sh arch/x86/configs/x86_64_defconfig /config/x86_64.config
make -j12 vmlinux bzImage

popd
