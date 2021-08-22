git config --global core.editor notepad

:: ./scripts/get_maintainer.pl --no-rolestats  --separator=, -f configure
python git-publish.py -b cirrus-base --forget-cc --topic=cirrus-speed --to qemu-devel@nongnu.org --cc "Alex Benn¨¦e <alex.bennee@linaro.org>,Peter Maydell <peter.maydell@linaro.org>,Philippe Mathieu-Daud¨¦ <f4bug@amsat.org>,QEMU Trivial <qemu-trivial@nongnu.org>,Paolo Bonzini <pbonzini@redhat.com>,Thomas Huth <thuth@redhat.com>,qemu-devel@nongnu.org"

pause
