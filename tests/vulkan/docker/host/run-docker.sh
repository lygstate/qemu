#!/bin/bash

# To run in this file's directory as a working directory

set -ex

ROOT=$(realpath ../../../../../)
XSOCK=/tmp/.X11-unix
XAUTH=/tmp/.docker.xauth
DISPLAY=":0"

xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

docker run -it --rm \
    --privileged \
    --ipc=host \
    -v /dev/log:/dev/log \
    -v /dev/vhost-net:/dev/vhost-net \
    -v /sys/kernel/debug:/sys/kernel/debug \
    -v $ROOT/mesa:/mesa \
    -v $ROOT/libepoxy:/libepoxy \
    -v $ROOT/virglrenderer:/virglrenderer \
    -v $ROOT/kernel:/kernel \
    -v $ROOT/qemu:/qemu \
    -v $ROOT/image:/image \
    -p 2222:22 \
    -p 1234:1234 \
    -e XDG_RUNTIME_DIR=/tmp \
    -e WAYLAND_DISPLAY=$WAYLAND_DISPLAY \
    -v $XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/tmp/$WAYLAND_DISPLAY \
    qemu
   # -v $XSOCK \
   # -v $XAUTH \
   # -e XAUTHORITY=$XAUTH \
   # -e DISPLAY=$DISPLAY \
