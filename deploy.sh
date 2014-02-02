#!/bin/bash

cd TvSeriesOrganizerApp
mv TvSeriesOrganizerApp TvSeriesOrganizer
tar czf TvSeriesOrganizer.tgz TvSeriesOrganizer
 
scp -o StrictHostKeyChecking=no TvSeriesOrganizer.tgz travis@download.rom1504.fr:download/TvSeriesOrganizer/bin/
commitNumber=`git rev-parse HEAD`
command="cp download/TvSeriesOrganizer/bin/TvSeriesOrganizer.tgz download/TvSeriesOrganizer/bin/TvSeriesOrganizer-$commitNumber.tgz"
ssh travis@download.rom1504.fr $command
