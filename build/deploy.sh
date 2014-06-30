#!/bin/bash

set -e

cd source/TvSeriesOrganizerApp

mkdir -p deploy/TvSeriesOrganizer
cd deploy/TvSeriesOrganizer
cp ../../TvSeriesOrganizer .
cp ../../../SignalList/libSignalList.so.1.0.0 libSignalList.so.1
mkdir qtlib
cd qtlib
p=`pwd`
cd /opt/Qt/5.2.1/gcc_64/lib
cp libicudata.so.51  libicuuc.so.51   libQt5DBus.so.5  libQt5Network.so.5  libQt5Quick.so.5 libicui18n.so.51  libQt5Core.so.5  libQt5Gui.so.5  libQt5Qml.so.5 libQt5Widgets.so.5 $p/
cd $p/..
cp -R /opt/Qt/5.2.1/gcc_64/plugins /opt/Qt/5.2.1/gcc_64/qml .
ln -s plugins/imageformats plugins/platforminputcontexts plugins/platformthemes plugins/generic plugins/platforms .
ln -s qml/QtGraphicalEffects qml/QtQml qml/QtQuick qml/QtQuick.2 .
cp ../../../../build/TvSeriesOrganizer.sh .
cd ..
tar czf ../TvSeriesOrganizer.tgz TvSeriesOrganizer

mkdir package
mkdir -p package/DEBIAN
cp ../../../build/debianPackageInfo package/DEBIAN/control
mkdir -p package/opt
cp -R TvSeriesOrganizer package/opt/
mkdir -p package/usr/bin
cd package/usr/bin
ln -s ../../opt/TvSeriesOrganizer/TvSeriesOrganizer.sh TvSeriesOrganizer
cd ../../..
dpkg --build package ../TvSeriesOrganizer.deb



cd ..


scp -o StrictHostKeyChecking=no TvSeriesOrganizer.deb travis@download.rom1504.fr:download/TvSeriesOrganizer/ubuntu/
commitNumber=`git rev-parse HEAD`
command="cp download/TvSeriesOrganizer/ubuntu/TvSeriesOrganizer.deb download/TvSeriesOrganizer/ubuntu/TvSeriesOrganizer-$commitNumber.deb"
ssh travis@download.rom1504.fr $command

scp -o StrictHostKeyChecking=no TvSeriesOrganizer.tgz travis@download.rom1504.fr:download/TvSeriesOrganizer/linux/
commitNumber=`git rev-parse HEAD`
command="cp download/TvSeriesOrganizer/linux/TvSeriesOrganizer.tgz download/TvSeriesOrganizer/linux/TvSeriesOrganizer-$commitNumber.tgz"
ssh travis@download.rom1504.fr $command

cp ../../TvSeriesOrganizer/android-build/bin/QtApp-release.apk TvSeriesOrganizer.apk
scp TvSeriesOrganizer.apk travis@download.rom1504.fr:download/TvSeriesOrganizer/android/
command="cp download/TvSeriesOrganizer/android/TvSeriesOrganizer.apk download/TvSeriesOrganizer/android/TvSeriesOrganizer-$commitNumber.apk"
ssh travis@download.rom1504.fr $command
