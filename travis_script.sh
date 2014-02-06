#!/bin/bash

CI_HOME=`pwd`
export ANDROID_NDK_TOOLCHAIN_VERSION=4.8
export ANDROID_NDK_TOOLS_PREFIX=arm-linux-androideabi
export ANDROID_NDK_HOST=linux-x86_64
export ANDROID_NDK_ROOT=$CI_HOME/android-ndk-r9
export ANDROID_NDK_TOOLCHAIN_PREFIX=arm-linux-androideabi
export ANDROID_SDK_ROOT=$CI_HOME/android-sdk-linux
export ANDROID_HOME=$CI_HOME/android-sdk-linux
export ANDROID_NDK_PLATFORM=android-18
$CI_HOME/android_armv7/bin/qmake -r -spec $CI_HOME/android_armv7/mkspecs/android-g++
make
make install INSTALL_ROOT=$CI_HOME/android-build/
androiddeployqt --input ./TvSeriesOrganizerApp/android-libTvSeriesOrganizerApp.so-deployment-settings.json --output $CI_HOME/android-build/ --android-platform android-18 --release