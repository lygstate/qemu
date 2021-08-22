git config --global core.editor notepad

:: ./scripts/get_maintainer.pl  -f plugins/*
python git-publish.py -b texi-base -t texi --forget-cc --to qemu-devel@nongnu.org --cc "Peter Maydell <peter.maydell@linaro.org>,Kevin Wolf <kwolf@redhat.com>,QEMU Trivial <qemu-trivial@nongnu.org>,qemu-devel@nongnu.org"

pause
