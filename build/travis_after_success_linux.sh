#!/bin/bash

set -e

build/getSshKey.sh
build/deploy_linux.sh
sudo apt-get install -qq xautomation x11-utils x11-apps bc
cp source/SignalList/libSignalList.so.1.0.0 libSignalList.so.1
time build/multiScreenshot.sh 6 source/TvSeriesOrganizerApp/TvSeriesOrganizer /tmp/datadir_ screenshot/screenshot_ 
build/sendScreenShot.sh