#!/bin/bash
THIS_DIR="$(cd "$(dirname "$0")"; pwd -P)"

echo "The script you are running has basename `basename "$0"` dirname $THIS_DIR"
echo "The present working directory is `pwd`"


#libepoxy
cd $THIS_DIR/../../xemu-opengl/libepoxy
rm -rf build
#meson --prefix="${MINGW_PREFIX}" --buildtype=debug -Degl=yes build # -Dtests=true
#ninja -C build install

cd $THIS_DIR/../../xemu-opengl/virglrenderer
rm -rf build
meson --prefix="${MINGW_PREFIX}" --buildtype=debug -Dplatforms=egl build # -Dtests=true
ninja -C build install


# pacman -S mingw-w64-x86_64-meson
