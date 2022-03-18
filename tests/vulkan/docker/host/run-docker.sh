#!/bin/bash

# To run in this file's directory as a working directory

set -ex

ROOT=$(realpath ../../../../../)
XSOCK=/tmp/.X11-unix
XAUTH=/tmp/.docker.xauth
export DISPLAY=":0"
export WAYLAND_DISPLAY="wayland-0"
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

docker rm -f qemu

docker run -it --name qemu --rm \
    --privileged \
    --ipc=host \
    -v /dev/log:/dev/log \
    -v /dev/vhost-net:/dev/vhost-net \
    -v /sys/kernel/debug:/sys/kernel/debug \
    -v $ROOT:$ROOT \
    -p 2222:22 \
    -p 1234:1234 \
    -p 1235:1235 \
    -p 5900:5900 \
    -e ROOT=$ROOT \
    -e XDG_RUNTIME_DIR=/tmp \
    -e WAYLAND_DISPLAY=$WAYLAND_DISPLAY \
    -v $XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/tmp/$WAYLAND_DISPLAY \
    qemu
   # -v $XSOCK \
   # -v $XAUTH \
   # -e XAUTHORITY=$XAUTH \
   # -e DISPLAY=$DISPLAY \
