#!/bin/bash

set -e

sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update -qq
sudo apt-get remove g++ gcc g++-4.6 libstdc++6-4.6-dev
sudo apt-get install -qq g++-4.8 gcc-4.8
sudo apt-get install -qq libstdc++6:i386 lib32z1
sudo ln -s /usr/bin/g++-4.8 /usr/bin/g++
sudo ln -s /usr/bin/gcc-4.8 /usr/bin/gcc
sudo mkdir -p /opt
cd /opt
sudo wget http://dev.rom1504.fr/qt521_small.tgz -O - | sudo tar xz
sudo chmod -R a+rx /opt/