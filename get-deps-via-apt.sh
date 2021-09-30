#!/bin/bash
set -euo pipefail
cd deps
apt source bzip2 && ln -sfv bzip2-* bzip2
apt source freetype && ln -sfv freetype-* freetype
apt source libogg && ln -sfv libogg-* libogg
apt source libvorbis && ln -sfv libvorbis-* libvorbis
apt source libjpeg-turbo && ln -sfv libjpeg-turbo-* libjpeg-turbo
apt source libsdl1.2 && ln -sfv libsdl1.2-* sdl
apt source sdl-image1.2 && ln -sfv sdl-image1.2-* sdl-image
apt source sdl-mixer1.2 && ln -sfv sdl-mixer1.2-* sdl-mixer
apt source sdl-ttf2.0 && ln -sfv sdl-ttf2.0-* sdl-ttf
apt source onscripter && ln -sfv onscripter-* onscripter
cp -v config/freetype/* freetype/include/freetype/config/
cp -v config/libjpeg-turbo/* libjpeg-turbo/
cp -v config/libogg/* libogg/include/ogg/
cp -v config/sdl/* sdl/include/
