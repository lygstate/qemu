#!/bin/bash

# To run in this file's directory as working directory

# e: exists as soon as any line in bash fails
# x: prints each command that is going to be executed prepending it with a +
set -ex

# Get the absolute path of the parent directory of the
# current working directory (not this script's directory)
src_root="$(realpath ../guest)"

USER_ID=$(id -u)
GROUP_ID=$(id -g)

# Build a docker image
# from a dockerfile
# Set a name to this image
# Build context is the set of file in this path
docker build \
    -f Dockerfile \
    -t qemu \
    --build-arg USER_ID=$USER_ID \
    --build-arg GROUP_ID=$GROUP_ID \
    "${src_root}"
