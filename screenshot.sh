#!/bin/bash

binaryName=TvSeriesOrganizerApp/TvSeriesOrganizer
windowName=TvSeriesOrganizer
export DISPLAY=:10
sleeptime=5
Xvfb $DISPLAY -screen 0 1920x1080x24  &
sleep $sleeptime
$binaryName  &
sleep $sleeptime
info=`xwininfo -display $DISPLAY -name $windowName`
id=`echo "$info" | grep "Window id" | cut -f4 -d' '`
x=`echo "$info" | grep "Absolute upper-left X" | cut -f7 -d' '`
y=`echo "$info" | grep "Absolute upper-left Y" | cut -f7 -d' '`

mkdir -p  screenshot/

function moveClick
{
	xte -x $DISPLAY "mousemove $(($x+$1)) $(($y+$2))"
	xte -x $DISPLAY "mouseclick 1"
}

function takeScreenshot
{
	xwd -id $id | convert xwd:- screenshot/$1.png
}

function addSeries
{
	moveClick 400 170
	sleep 1
	moveClick 100 240
	xte -x $DISPLAY "str $1"
	sleep 1
	xte -x $DISPLAY "key Return"
 	sleep $sleeptime
 	if [[ $2 -eq 1 ]]
 	then
		takeScreenshot SeriesSearch
	fi
	moveClick 515 305
	sleep 1
}

function moveClickTakeScreenshot
{
	moveClick $1 $2
	sleep $sleeptime
	takeScreenshot $3
}

addSeries "merlin" 1
addSeries "suits"
addSeries "breaking bad"

sleep $sleeptime
takeScreenshot SeriesList

moveClickTakeScreenshot 40 350 SeriesDetails
moveClickTakeScreenshot 200 90 SeriesInfo
moveClickTakeScreenshot 400 90 SeriesFanArts
moveClickTakeScreenshot 400 90 SeriesPosters
moveClick 100 90
moveClick 100 90

moveClickTakeScreenshot 40 400 SeasonDetails
moveClickTakeScreenshot 40 300 EpisodeDetails

pkill Xvfb
export DISPLAY=:0