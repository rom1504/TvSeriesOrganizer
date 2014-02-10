#!/bin/bash

cd TvSeriesOrganizerApp
tar czf TvSeriesOrganizer.tgz TvSeriesOrganizer
 
scp -o StrictHostKeyChecking=no TvSeriesOrganizer.tgz travis@download.rom1504.fr:download/TvSeriesOrganizer/linux/
commitNumber=`git rev-parse HEAD`
command="cp download/TvSeriesOrganizer/linux/TvSeriesOrganizer.tgz download/TvSeriesOrganizer/linux/TvSeriesOrganizer-$commitNumber.tgz"
ssh travis@download.rom1504.fr $command

cp ../../TvSeriesOrganizer/android-build/bin/QtApp-release-unsigned.apk TvSeriesOrganizer.apk
scp TvSeriesOrganizer.apk travis@download.rom1504.fr:download/TvSeriesOrganizer/android/
command="cp download/TvSeriesOrganizer/android/TvSeriesOrganizer.apk download/TvSeriesOrganizer/android/TvSeriesOrganizer-$commitNumber.apk"
ssh travis@download.rom1504.fr $command
