git config --global core.editor notepad
:: 
:: ./scripts/get_maintainer.pl  -f tests/
python git-publish.py -b qapi-base --to qemu-devel@nongnu.org --cc "QEMU Trivial <qemu-trivial@nongnu.org>,Thomas Huth <thuth@redhat.com>,Markus Armbruster <armbru@redhat.com>"

pause
