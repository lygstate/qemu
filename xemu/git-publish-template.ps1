git config --global core.editor notepad
# Gerd Hoffmann <kraxel@redhat.com>
# ./scripts/get_maintainer.pl  -f ui/curses.c 
python git-publish.py -b mem-alloca-base --topic=mem-alloca  --to qemu-devel@nongnu.org --cc "Philippe Mathieu-Daudé <f4bug@amsat.org>,Philippe Mathieu-Daudé <philmd@redhat.com>,Richard Henderson <richard.henderson@linaro.org>,Stefan Weil <sw@weilnetz.de>"

pause
