git config --global core.editor notepad

:: ./scripts/get_maintainer.pl  -f plugins/*
python git-publish.py -b plugin-base -t plugin --forget-cc --to qemu-devel@nongnu.org --cc "Paolo Bonzini <pbonzini@redhat.com>,Richard Henderson <richard.henderson@linaro.org>,Alex Benn¨¦e <alex.bennee@linaro.org>,qemu-devel@nongnu.org"

pause
