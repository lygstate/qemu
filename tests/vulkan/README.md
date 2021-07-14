# Vulkan QEMU development and testing environment

1. Change directory to `test/vulkan/docker/host` and run `build-docker.sh` to create the Docker image.
2. Then execute `run-docker.sh` to launch QEMU in a container.

## What is run

At start up, the container launches the `test/vulkan/docker/guest/run.sh` script, which triggers building of the various required components and then runs QEMU.

You are free to comment out any of the build scripts listed in this file, but then you should make sure to run `build-docker.sh` again so that your changes would be uploaded to the Docker image.
