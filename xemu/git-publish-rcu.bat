git config --global core.editor notepad
:: 
:: ./scripts/get_maintainer.pl --no-rolestats  --separator=, -f util/rcu.c
python git-publish.py -b rcu-base --to qemu-devel@nongnu.org --cc "QEMU Trivial <qemu-trivial@nongnu.org>,Juan Quintela <quintela@redhat.com>,Stefan Hajnoczi <stefanha@redhat.com>,Daniel Brodsky <dnbrdsky@gmail.com>"

pause
