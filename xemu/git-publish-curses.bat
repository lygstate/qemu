git config --global core.editor notepad
:: Gerd Hoffmann <kraxel@redhat.com>
:: ./scripts/get_maintainer.pl  -f ui/curses.c 
python git-publish.py -b curses-base --forget-cc --to "Daniel P. Berrang¨¦ <berrange@redhat.com>,qemu-devel@nongnu.org" --cc "QEMU Trivial <qemu-trivial@nongnu.org>,Paolo Bonzini <pbonzini@redhat.com>,Gerd Hoffmann <kraxel@redhat.com>,Philippe Mathieu-Daud¨¦ <philmd@redhat.com>,Richard Henderson <richard.henderson@linaro.org>,Laurent Vivier <laurent@vivier.eu>,Alex Benn¨¦e <alex.bennee@linaro.org>,qemu-devel@nongnu.org"

pause
