git config --global core.editor notepad
:: Gerd Hoffmann <kraxel@redhat.com>
:: ./scripts/get_maintainer.pl  -f ui/curses.c 
python git-publish.py -b whpx-base --to qemu-devel@nongnu.org --cc "Sunil Muthuswamy <sunilmut@microsoft.com>,Ed Maste <emaste@freebsd.org>,Paolo Bonzini <pbonzini@redhat.com>"

pause
