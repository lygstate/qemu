git config --global core.editor notepad

:: ./scripts/get_maintainer.pl --no-rolestats  --separator=, -f configure
python git-publish.py -b trivial-base --topic=indent-fix-1 --to qemu-devel@nongnu.org --cc "QEMU Trivial <qemu-trivial@nongnu.org>,Philippe Mathieu-Daud¨¦ <philmd@redhat.com>,Richard Henderson <richard.henderson@linaro.org>,Laurent Vivier <laurent@vivier.eu>,Alex Benn¨¦e <alex.bennee@linaro.org>,qemu-devel@nongnu.org"

pause
