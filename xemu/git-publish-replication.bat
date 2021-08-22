git config --global core.editor notepad
:: Wen Congyang <wencongyang2@huawei.com>,Xie Changlong <xiechanglong.d@gmail.com>
:: ./scripts/get_maintainer.pl  -f tests/test-replication.c 
python git-publish.py -b replication-base --to qemu-devel@nongnu.org --cc "QEMU Trivial <qemu-trivial@nongnu.org>,QEMU Block <qemu-block@nongnu.org>,Stefan Weil <sw@weilnetz.de>,Max Reitz <mreitz@redhat.com>,Kevin Wolf <kwolf@redhat.com>,Wen Congyang <wencongyang2@huawei.com>,Xie Changlong <xiechanglong.d@gmail.com>"

pause
