git config --global core.editor notepad

:: ./scripts/get_maintainer.pl --no-rolestats  --separator=, -f configure

:: ./scripts/get_maintainer.pl --no-rolestats  --separator=, a.patch

python git-publish.py -b ga-simple-base --to qemu-devel@nongnu.org --cc "QEMU Trivial <qemu-trivial@nongnu.org>,Paolo Bonzini <pbonzini@redhat.com>,Philippe Mathieu-Daud¨¦ <philmd@redhat.com>,Laurent Vivier <laurent@vivier.eu>,Marc-Andr¨¦ Lureau <marcandre.lureau@redhat.com>,Alex Benn¨¦e<alex.bennee@linaro.org>,qemu-devel@nongnu.org"

pause

:: msys2-patches
:: --sign-pull --pull-request
:: Richard Henderson <richard.henderson@linaro.org>,Kevin Wolf <kwolf@redhat.com>,Paolo Bonzini <pbonzini@redhat.com>
:: msys2-patches-base