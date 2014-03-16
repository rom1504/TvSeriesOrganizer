#!/bin/bash

cd ../TvSeriesOrganizerLinux
mkdir -p ~/.ssh
openssl aes-256-cbc -pass "pass:$MY_SECRET_ENV" -in .travis/id_rsa_deploy.enc -out ~/.ssh/id_rsa -d -a
chmod 600 ~/.ssh/id_rsa
./deploy.sh
sudo gcc usleep.c -o /bin/usleep
sudo add-apt-repository ppa:xorg-edgers/ppa -y
sudo apt-get update -qq
sudo apt-get install -qq xvfb xautomation x11-utils x11-apps
./screenshot.sh
./sendScreenShot.sh