#!/bin/bash

CI_HOME=`pwd`
cp -R . ../TvSeriesOrganizerLinux
export ANDROID_NDK_TOOLCHAIN_VERSION=4.8
export ANDROID_NDK_TOOLS_PREFIX=arm-linux-androideabi
export ANDROID_NDK_HOST=linux-x86_64
export ANDROID_NDK_ROOT=/opt/ndk
export ANDROID_NDK_TOOLCHAIN_PREFIX=arm-linux-androideabi
export ANDROID_SDK_ROOT=/opt/sdk
export ANDROID_HOME=/opt/sdk
export ANDROID_NDK_PLATFORM=android-18
/opt/Qt/5.2.1/android_armv7/bin/qmake -r -spec android-g++
make
make install INSTALL_ROOT=$CI_HOME/android-build/
/opt/Qt/5.2.1/android_armv7/bin/androiddeployqt --input ./TvSeriesOrganizerApp/android-libTvSeriesOrganizer.so-deployment-settings.json --output $CI_HOME/android-build/ --android-platform android-18 --release

cd ../TvSeriesOrganizerLinux
/opt/Qt/5.2.1/gcc_64/bin/qmake
make