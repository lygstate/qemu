# Vulkan QEMU development and testing environment

1. Change directory to `test/vulkan/docker/host` and run `build-docker.sh` to create the Docker image.
2. Then execute `run-docker.sh` to launch QEMU in a container.

## What is run

At start up, the container launches the `test/vulkan/docker/guest/run.sh` script, which triggers building of the various required components and then runs QEMU.

You are free to comment out any of the build scripts listed in this file, but then you should make sure to run `build-docker.sh` again so that your changes would be uploaded to the Docker image.

```bash
docker run -it --name qemu2 --entrypoint /bin/bash --rm qemu

docker exec -it qemu bash

```

```bash
sudo apt update
sudo apt install openssh-server
ssh lygstate@127.0.0.1 -p 2222

sudp apt upgrade
sudo apt install mesa-utils vulkan-tools net-tools llvm

scp -P 2222 install.tar.gz lygstate@127.0.0.1:/home/lygstate

scp -P 2222 lygstate@127.0.0.1:/home/lygstate/.local/share/xorg/Xorg.0.log Xorg.0.log
scp -P 2222 lygstate@127.0.0.1:/var/log/syslog syslog.txt

ssh lygstate@127.0.0.1 -p 2222
sudo truncate -s 0 /var/log/syslog
sudo truncate -s 0 /home/lygstate/.local/share/xorg/Xorg.0.log
sudo rm -rf /usr/lib/x86_64-linux-gnu/dri
sudo rm -rf /usr/share/vulkan/icd.d/
sudo tar xzvf install.tar.gz -C /
cd /usr/lib/x86_64-linux-gnu/dri
sudo ln -s -r zink_dri.so swrast_dri.so
sudo ln -s -r zink_dri.so kms_swrast_dri

ls ~/.local/share/xorg/Xorg.0.log
```

```bash
ssh lygstate@127.0.0.1 -p 2222
export DISPLAY=":0"
export WAYLAND_DISPLAY="wayland-0"

xdpyinfo
export GALLIUM_DRIVER=zink
glxinfo | grep Device
gdbserver :1235 glxinfo
vulkaninfo
glxgears
vkcube

cd /usr/lib/x86_64-linux-gnu
ls -la | grep GL

```


build mesa host
```bash
echo 'deb-src http://cn.archive.ubuntu.com/ubuntu/ jammy main restricted' | sudo tee -a /etc/apt/sources.list

sudo apt-get update
sudo pip3 install mako meson
apt-get install llvm
sudo apt build-dep -yy mesa
sudo apt build-dep -yy qemu
sudo rm -rf build
mkdir -p build/host
meson build/host \
    -Dprefix=/usr \
    -Dgallium-drivers=swrast,zink \
    -Dbuildtype=debugoptimized \
    -Dllvm=enabled \
    -Degl=enabled \
    -Dgbm=enabled \
    -Dvulkan-drivers=swrast \
    -Dvalgrind=disabled
sudo ninja -C build/host install
```
# -Dbuildtype=debugoptimized \

debugging kernel
```
dmesg
```

```
-rwxr-xr-x  3 root root 85171312  3月 21 03:02 kms_swrast_dri.so
-rwxr-xr-x  3 root root 85171312  3月 21 03:02 swrast_dri.so
-rwxr-xr-x  3 root root 85171312  3月 21 03:02 zink_dri.so
```


```
sudo vi /usr/share/xsessions/ubuntu.desktop
sudo vi /usr/share/wayland-sessions/ubuntu.desktop
sudo vi /usr/share/wayland-sessions/ubuntu-wayland.desktop
append --disable-acceleration-check

Exec=env GNOME_SHELL_SESSION_MODE=ubuntu /usr/bin/gnome-session --session=ubuntu --disable-acceleration-check
```

https://bugs.launchpad.net/ubuntu/+source/gnome-session/+bug/1251281

