git config --global core.editor notepad
:: Gerd Hoffmann <kraxel@redhat.com>
:: ./scripts/get_maintainer.pl  -f block/nfs.c 
python git-publish.py -b msys_nfs_base --to qemu-devel@nongnu.org --cc "QEMU Trivial <qemu-trivial@nongnu.org>,Peter Lieven <pl@kamp.de>,Kevin Wolf <kwolf@redhat.com>,Max Reitz <mreitz@redhat.com>,qemu-block@nongnu.org"

pause
