#!/bin/bash

set -e

sudo mkdir -p /opt
cd /opt
sudo wget http://dl.google.com/android/android-sdk_r23-linux.tgz -O - | sudo tar zx
sudo mv android-sdk-linux sdk
echo yes | sudo /opt/sdk/tools/android update sdk -a --filter android-19,platform-tool,build-tools-20.0.0,tools --no-ui --force
sudo wget http://dev.rom1504.fr/android-ndk-r9_small.tgz -O - | sudo tar zx
sudo mv android-ndk-r9 ndk
sudo chmod -R a+rx /opt/
sudo ln -s `sudo find /opt/sdk -name "zipalign"` /opt/sdk/tools/