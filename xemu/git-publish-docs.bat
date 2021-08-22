git config --global core.editor notepad

:: ./scripts/get_maintainer.pl --no-rolestats  --separator=, -f configure
python git-publish.py -b docs-base --topic=docs-base-fix --to qemu-devel@nongnu.org --cc "Paolo Bonzini <pbonzini@redhat.com>,qemu-devel@nongnu.org"

pause
