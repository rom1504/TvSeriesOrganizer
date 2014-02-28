#!/bin/bash

cd TvSeriesOrganizerApp

mkdir -p deploy/TvSeriesOrganizer
cd deploy/TvSeriesOrganizer
cp ../../TvSeriesOrganizer .
mkdir qtlib
cd qtlib
p=`pwd`
cd /opt/Qt/5.2.1/gcc_64/lib
cp libicudata.so.51  libicuuc.so.51   libQt5DBus.so.5  libQt5Network.so.5  libQt5Quick.so.5 libicui18n.so.51  libQt5Core.so.5  libQt5Gui.so.5   libQt5Qml.so.5 libQt5Xml.so.5 $p/
cd $p/..
cp -R /opt/Qt/5.2.1/gcc_64/plugins /opt/Qt/5.2.1/gcc_64/qml .
ln -s plugins/imageformats plugins/platforminputcontexts plugins/platformthemes plugins/generic plugins/platforms .
ln -s qml/QtGraphicalEffects qml/QtQml qml/QtQuick qml/QtQuick.2 .
cp ../../../TvSeriesOrganizer.sh .
cd ..
tar czf ../TvSeriesOrganizer.tgz TvSeriesOrganizer
cd ..
 
scp -o StrictHostKeyChecking=no TvSeriesOrganizer.tgz travis@download.rom1504.fr:download/TvSeriesOrganizer/linux/
commitNumber=`git rev-parse HEAD`
command="cp download/TvSeriesOrganizer/linux/TvSeriesOrganizer.tgz download/TvSeriesOrganizer/linux/TvSeriesOrganizer-$commitNumber.tgz"
ssh travis@download.rom1504.fr $command

cp ../../TvSeriesOrganizer/android-build/bin/QtApp-release.apk TvSeriesOrganizer.apk
scp TvSeriesOrganizer.apk travis@download.rom1504.fr:download/TvSeriesOrganizer/android/
command="cp download/TvSeriesOrganizer/android/TvSeriesOrganizer.apk download/TvSeriesOrganizer/android/TvSeriesOrganizer-$commitNumber.apk"
ssh travis@download.rom1504.fr $command
