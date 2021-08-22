git config --global core.editor notepad

:: ./scripts/get_maintainer.pl  -f plugins/*
python git-publish.py -b plugins-base -t plugins-trival --forget-cc --to qemu-devel@nongnu.org --cc "Alex Benn¨¦e <alex.bennee@linaro.org>,qemu-devel@nongnu.org"

pause
