git config --global core.editor notepad
:: Gerd Hoffmann <kraxel@redhat.com>
:: ./scripts/get_maintainer.pl  -f ui/curses.c 
python git-publish.py -b capstone-base --to qemu-devel@nongnu.org --cc "Mark Cave-Ayland <mark.cave-ayland@ilande.co.uk>,Kevin Wolf <kwolf@redhat.com>,QEMU Block <qemu-block@nongnu.org>,Stefan Weil <sw@weilnetz.de>,Peter Lieven <pl@kamp.de>,Paolo Bonzini <pbonzini@redhat.com>,Alex Benn¨¦e <alex.bennee@linaro.org>,Richard Henderson <richard.henderson@linaro.org>"

pause
