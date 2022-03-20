#!/bin/sh
rm -rf deps
mkdir -p deps
git submodule update --init
cp -rv "$(guix build -f deps.scm)"/* ./deps/
chmod -R u+w deps
cp -rv deps.overlay/* ./deps/
