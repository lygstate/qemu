git config --global core.editor notepad
:: 
:: ./scripts/get_maintainer.pl  -f tests/
python git-publish.py -b char-base --to qemu-devel@nongnu.org --cc "Marc-Andr¨¦ Lureau <marcandre.lureau@redhat.com>,Paolo Bonzini <pbonzini@redhat.com>,Philippe Mathieu-Daud¨¦ <philmd@redhat.com>,Yonggang Luo <luoyonggang@gmail.com>,Corey Minyard <cminyard@mvista.com>,qemu-devel@nongnu.org"

pause
