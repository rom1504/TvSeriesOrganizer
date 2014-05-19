#!/bin/bash

set -e

cd ../TvSeriesOrganizerLinux
mkdir -p ~/.ssh
openssl aes-256-cbc -pass "pass:$MY_SECRET_ENV" -in .travis/id_rsa_deploy.enc -out ~/.ssh/id_rsa -d -a
chmod 600 ~/.ssh/id_rsa
./deploy.sh
sudo gcc usleep.c -o /bin/usleep
sudo apt-get install -qq xautomation x11-utils x11-apps
time ./multiScreenshot.sh 6 TvSeriesOrganizerApp/TvSeriesOrganizer /tmp/datadir_ screenshot/screenshot_ 
./sendScreenShot.sh