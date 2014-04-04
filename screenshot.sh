#!/bin/bash

set -e

binaryName=TvSeriesOrganizerApp/TvSeriesOrganizer
windowName=TvSeriesOrganizer
export DISPLAY=:10
sleeptime=5
longSleepTime=7
Xvfb $DISPLAY -screen 0 1920x1080x24  &
sleep $longSleepTime
$binaryName  &
sleep $longSleepTime
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
	import -window $id screenshot/$1.png
}

yTabBar=90
tab1=100
tab2=300
tab3=500

function clickSearchInput
{
	moveClick 100 120
}

function clickAdd
{
	moveClick 520 260
}

function addSeries
{
	if [[ $3 -ne 1 ]]
	then
		moveClick $tab3 $yTabBar
	fi
	sleep 1
	clickSearchInput
	xte -x $DISPLAY "str $1"
	sleep 1
	xte -x $DISPLAY "key Return"
 	sleep $sleeptime
 	if [[ $2 -eq 1 ]]
 	then
		takeScreenshot SeriesSearch
	fi
	clickAdd
	sleep 1
}

function moveClickTakeScreenshot
{
	moveClick $1 $2
	sleep $sleeptime
	takeScreenshot $3
}

function clickForward
{
	moveClick 550 20
}

takeScreenshot ExploreSeries

clickForward

addSeries "merlin" 1 1
addSeries "suits"
addSeries "breaking bad"

sleep $sleeptime
takeScreenshot SeriesList

moveClickTakeScreenshot 40 320 SeriesDetails
moveClickTakeScreenshot $tab2 $yTabBar SeriesInfo
moveClickTakeScreenshot $tab3 $yTabBar SeriesFanArts
moveClickTakeScreenshot $tab3 $yTabBar SeriesPosters
moveClick $tab1 $yTabBar
moveClick $tab1 $yTabBar

moveClickTakeScreenshot 40 380 SeasonDetails
moveClickTakeScreenshot 40 280 EpisodeDetails

pkill Xvfb
export DISPLAY=:0