#!/bin/bash

set -ex

# Comment out any of these lines if no build is needed,
# but then do not forget to rebuild the image.
#bash build-kernel.sh
bash build-mesa.sh
bash build-epoxy.sh
bash build-virgl.sh
bash build-gtk.sh
bash build-qemu.sh

bash run-qemu.sh
