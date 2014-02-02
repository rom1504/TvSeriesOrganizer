#!/bin/bash

binaryName=TvSeriesOrganizerApp/TvSeriesOrganizer
windowName=TvSeriesOrganizer
export DISPLAY=:10
Xvfb $DISPLAY -screen 0 1920x1080x24  &
sleep 1
$binaryName  &
sleep 2
info=`xwininfo -display $DISPLAY -name $windowName`
id=`echo "$info" | grep "Window id" | cut -f4 -d' '`
x=`echo "$info" | grep "Absolute upper-left X" | cut -f7 -d' '`
y=`echo "$info" | grep "Absolute upper-left Y" | cut -f7 -d' '`

mkdir -p  screenshot/

xwd -id $id | convert xwd:- screenshot/SeriesList.png
xte -x $DISPLAY "mousemove $(($x+40)) $(($y+20))"
xte -x $DISPLAY 'mouseclick 1'
usleep 200000
xwd -id $id | convert xwd:- screenshot/SeriesDetails.png
xte -x $DISPLAY "mousemove $(($x+40)) $(($y+20))"
xte -x $DISPLAY 'mouseclick 1'
usleep 200000
xwd -id $id | convert xwd:- screenshot/SeasonDetails.png
xte -x $DISPLAY "mousemove $(($x+40)) $(($y+20))"
xte -x $DISPLAY 'mouseclick 1'
usleep 200000
xwd -id $id | convert xwd:- screenshot/EpisodeDetails.png
pkill Xvfb
export DISPLAY=:0