#!/bin/bash

set -e

ssh travis@download.rom1504.fr "rm -rf download/TvSeriesOrganizer/screenshot/screenshot"
scp -r screenshot travis@download.rom1504.fr:download/TvSeriesOrganizer/screenshot/
commitNumber=`git rev-parse HEAD`
command="cp -R download/TvSeriesOrganizer/screenshot/screenshot download/TvSeriesOrganizer/screenshot/screenshot-$commitNumber"
ssh travis@download.rom1504.fr $command
