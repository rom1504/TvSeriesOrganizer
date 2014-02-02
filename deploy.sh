#!/bin/bash

cd TvSeriesOrganizerApp
mv TvSeriesOrganizerApp TvSeriesOrganizer
tar czf TvSeriesOrganizer.tgz TvSeriesOrganizer
 
scp -o StrictHostKeyChecking=no TvSeriesOrganizer.tgz travis@download.rom1504.fr:download/TvSeriesOrganizer/
commitNumber=`git rev-parse HEAD`
command="cp download/TvSeriesOrganizer/TvSeriesOrganizer.tgz download/TvSeriesOrganizer/TvSeriesOrganizer-$commitNumber.tgz"
ssh travis@download.rom1504.fr $command
