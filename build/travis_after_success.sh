#!/bin/bash

set -e

cd ../TvSeriesOrganizerLinux
mkdir -p ~/.ssh
openssl aes-256-cbc -pass "pass:$MY_SECRET_ENV" -in build/.travis/id_rsa_deploy.enc -out ~/.ssh/id_rsa -d -a
chmod 600 ~/.ssh/id_rsa
build/deploy.sh
sudo apt-get install -qq xautomation x11-utils x11-apps bc
cp source/SignalList/libSignalList.so.1.0.0 libSignalList.so.1
time build/multiScreenshot.sh 6 source/TvSeriesOrganizerApp/TvSeriesOrganizer /tmp/datadir_ screenshot/screenshot_ 
build/sendScreenShot.sh