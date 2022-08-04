#!/bin/sh
set -eu
rm -rf deps
mkdir -p deps
git submodule update --init
cp -rv "$(guix build -f deps.scm || kill $$)"/* ./deps/
chmod -R u+w deps
cp -rv deps.overlay/* ./deps/
