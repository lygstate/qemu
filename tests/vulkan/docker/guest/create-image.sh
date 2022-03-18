#!/bin/bash
# Create a QEMU image to run

set -ex

pushd $ROOT/image

IMG=ubuntu.qcow2

if [ ! -f $IMG ]; then
    ISO_NAME=ubuntu-21.10-desktop-amd64.iso
    ISO=21.10/$ISO_NAME
    if [ ! -f $ISO_NAME ]; then
        wget https://releases.ubuntu.com/$ISO
    fi

    qemu-img create -f qcow2 $IMG 16G
fi

popd
