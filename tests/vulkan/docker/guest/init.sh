#!/bin/bash

set +xe

mount -t proc none /proc
mount -t sysfs none /sys
mount -t devtmpfs none /dev || echo possibly already mounted
mkdir -p /dev/pts
mount -t devpts devpts /dev/pts
mount -t virtiofs local /usr/local
mount -t debugfs none /sys/kernel/debug
echo "nameserver 8.8.8.8" >/etc/resolv.conf

exec /sbin/initrd
