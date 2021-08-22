git config --global core.editor notepad

:: ./scripts/get_maintainer.pl --no-rolestats  --separator=, -f configure
python git-publish.py -b qemu-version-fix-base --topic=qemu-version-fix --to qemu-devel@nongnu.org --cc "Peter Maydell <peter.maydell@linaro.org>,Philippe Mathieu-Daud¨¦ <f4bug@amsat.org>,QEMU Trivial <qemu-trivial@nongnu.org>,Paolo Bonzini <pbonzini@redhat.com>,Thomas Huth <thuth@redhat.com>,qemu-devel@nongnu.org"

pause
