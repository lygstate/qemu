pacman -S base-devel git
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-gtk3
pacman -S mingw-w64-x86_64-python mingw-w64-x86_64-python-setuptools
pacman -S mingw-w64-x86_64-ninja

sudo dpkg -l $PACKAGES | sort > /packages.txt

sudo dpkg -l libgnutls | sort > /packages.txt

cd /mingw64/bin
cp x86_64-w64-mingw32-gcc-ar.exe x86_64-w64-mingw32-ar.exe
cp x86_64-w64-mingw32-gcc-ranlib.exe x86_64-w64-mingw32-ranlib.exe
cp x86_64-w64-mingw32-gcc-nm.exe x86_64-w64-mingw32-nm.exe
cp windres.exe x86_64-w64-mingw32-windres.exe
cp strip.exe x86_64-w64-mingw32-strip.exe
cp objcopy.exe x86_64-w64-mingw32-objcopy.exe
cp ld x86_64-w64-mingw32-ld.exe
cp as x86_64-w64-mingw32-as.exe
cp sdl2-config x86_64-w64-mingw32-sdl2-config
# https://wiki.qemu.org/Hosts/W32


Debugging Options:
--enable-debug-info --enable-debug 

git remote add github git@github.com:lygstate/qemu.git



# --enable-spice --enable-libnfs --enable-smartcard --enable-u2f --enable-libusb --enable-live-block-migration --enable-usb-redir \
#TODO:
enable-vde
enable-netmap
enable-cap-ng
glusterfs
tpm
numa
UI:
--enable-vte

--enable-brlapi
--enable-lzfse
https://github.com/msys2/MINGW-packages/issues/5580

TODO:
Fixes test-char and recover /char/stdio/*

msitools
--enable-guest-agent-msi

TODO:
Implement filemonitor-win32 like filemonitor-inotify.c and enable test-util-filemonitor
#  --target-list=ppc-softmmu \

sh scripts/ci/windows/msys2-build.sh >build.txt 2>&1

sh -c "cd build && make -i check > ../tests.txt 2>&1"

make -i check

# disable-pie
# pie doesn't working on mingw32

pacman -S mingw-w64-x86_64-spice-protocol

C:/CI-Tools/msys64/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/10.2.0/../../../../x86_64-w64-mingw32/bin/nm.exe


python E:/CI-Cor-Ready/xemu/qemu.org/scripts/pickle-to-json.py ^
E:/CI-Cor-Ready/xemu/qemu.org-x64/meson-private/meson_exe_sh_783fab9aa10daba2c47de638e11492402e9653af.dat ^
E:/CI-Cor-Ready/xemu/qemu.org-x64/meson-private/meson_exe_sh_783fab9aa10daba2c47de638e11492402e9653af.json

set https_proxy=socks5://127.0.0.1:7073
set http_proxy=socks5://127.0.0.1:7073

export https_proxy=socks5://127.0.0.1:7073
export http_proxy=socks5://127.0.0.1:7073

pacman -S mingw-w64-x86_64-python-numpy

pip install pandas


echo This message goes to stderr >&2


E:/CI-Cor-Ready/xemu/qemu.org/scripts/undefsym.py C:/CI-Tools/msys64/mingw64/bin/x86_64-w64-mingw32-nm.EXE libqemuutil.a
