#!/bin/bash

set -e

CI_HOME=`pwd`
cp -R . ../TvSeriesOrganizerLinux
export ANDROID_NDK_TOOLCHAIN_VERSION=4.8
export ANDROID_NDK_TOOLS_PREFIX=arm-linux-androideabi
export ANDROID_NDK_HOST=linux-x86_64
export ANDROID_NDK_ROOT=/opt/ndk
export ANDROID_NDK_TOOLCHAIN_PREFIX=arm-linux-androideabi
export ANDROID_SDK_ROOT=/opt/sdk
export ANDROID_HOME=/opt/sdk
export ANDROID_NDK_PLATFORM=android-19
/opt/Qt/5.2.1/android_armv7/bin/qmake -r -spec android-g++
make
make install INSTALL_ROOT=$CI_HOME/android-build/
if [[ $MY_SECRET_ENV != "" ]]
then
	openssl aes-256-cbc -pass "pass:$MY_SECRET_ENV" -in .travis/android_release.keystore.enc -out .travis/android_release.keystore -d -a
	openssl aes-256-cbc -pass "pass:$MY_SECRET_ENV" -in .travis/keystore_password.enc -out .travis/keystore_password -d -a
	/opt/Qt/5.2.1/android_armv7/bin/androiddeployqt --input ./TvSeriesOrganizerApp/android-libTvSeriesOrganizer.so-deployment-settings.json --output $CI_HOME/android-build/ --android-platform $ANDROID_NDK_PLATFORM --sign .travis/android_release.keystore TvSeries --storepass `cat .travis/keystore_password`
else
	/opt/Qt/5.2.1/android_armv7/bin/androiddeployqt --input ./TvSeriesOrganizerApp/android-libTvSeriesOrganizer.so-deployment-settings.json --output $CI_HOME/android-build/ --android-platform $ANDROID_NDK_PLATFORM --release
fi

cd ../TvSeriesOrganizerLinux
/opt/Qt/5.2.1/gcc_64/bin/qmake
make