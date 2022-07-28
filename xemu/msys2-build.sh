export mingw64_bin=`cygpath -w /mingw64/bin -m`
echo $mingw64_bin
find /mingw64/bin/*.py | xargs sed -i "s|^#!.*python3.exe$|#!$mingw64_bin/python3.exe|"
find /mingw64/bin/*.py | xargs sed -i "s|^#!.*python.exe$|#!$mingw64_bin/python.exe|"
# --target-list=ppc-softmmu \

mkdir -p build
cd build
../configure \
--target-list=ppc-softmmu \
--python=python3 \
--enable-stack-protector \
--enable-guest-agent \
--enable-plugins --enable-modules \
--enable-gnutls --enable-nettle \
--enable-sdl --enable-sdl-image --enable-gtk --disable-vte \
--enable-curses --enable-iconv \
--enable-vnc --enable-vnc-sasl --enable-vnc-jpeg --enable-vnc-png \
--enable-slirp=git \
--disable-brlapi --enable-curl \
--enable-fdt \
--disable-kvm --enable-hax --enable-whpx \
--enable-libnfs --enable-libusb \
--enable-live-block-migration --enable-usb-redir \
--enable-lzo --enable-snappy --enable-bzip2 --enable-zstd \
--enable-membarrier --enable-coroutine-pool \
--enable-libssh --enable-libxml2 \
--enable-jemalloc --enable-avx2 \
--enable-replication \
--enable-tools \
--enable-bochs --enable-cloop --enable-dmg --enable-qcow1 \
--enable-vdi --enable-vvfat --enable-qed --enable-parallels \
--enable-sheepdog \
--enable-debug-info --enable-debug

make -j16
make V=1 check
