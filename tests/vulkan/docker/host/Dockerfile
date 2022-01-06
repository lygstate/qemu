FROM ubuntu:impish
LABEL description="Test QEMU"

ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update \
    && apt-get install -yy --no-install-recommends \
        ca-certificates \
        gnupg \
    && echo "deb-src https://archive.ubuntu.com/ubuntu impish main" >> /etc/apt/sources.list \
    && cat /etc/apt/sources.list \
    && apt-get update \
    && apt-get upgrade -yy \
    && apt-get build-dep -yy \
        qemu virglrenderer

# Install required packages
RUN apt-get install -yy --no-install-recommends \
        wget \
        git \
        libsdl2-dev \
        libsdl2-image-dev \
        cpio

RUN apt-get install -yy --no-install-recommends \
        bc \
        libelf-dev \
        qemu-utils \
        libvulkan-dev \
        openssh-server \
        gdb

RUN apt-get install -yy --no-install-recommends \
        mesa-vulkan-drivers \
        vulkan-tools

RUN apt-get build-dep -yy mesa
RUN apt-get install -yy llvm
RUN apt-get install -yy mesa-utils x11-apps
RUN apt-get install -yy libzstd-dev

# Build GTK
RUN apt-get install -y libgstreamer-plugins-bad1.0-dev libgirepository1.0-dev


# Provide our own init script for kernel boot
WORKDIR /rootfs
COPY init.sh /rootfs/.
RUN find -H | cpio -H newc -o | xz --check=crc32 -T4 - > /rootfs.cpio.gz
RUN rm -r /rootfs
WORKDIR /

# Used for building our kernel
WORKDIR config
COPY x86_64.config /config
WORKDIR /

ENV DEST_DIR=/usr/local/bin

COPY build-kernel.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/build-kernel.sh

COPY build-mesa.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/build-mesa.sh

COPY build-epoxy.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/build-epoxy.sh

COPY build-virgl.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/build-virgl.sh

COPY build-gtk.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/build-gtk.sh

COPY build-qemu.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/build-qemu.sh

COPY create-image.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/create-image.sh

COPY run-qemu.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/run-qemu.sh

COPY run.sh "$DEST_DIR"
RUN chmod +x "$DEST_DIR"/run.sh
ENTRYPOINT ["/usr/local/bin/run.sh"]
