#!/bin/bash

if [[ $# -ne 4 ]]
then
		echo "usage : $0 <binary name> <display> <locale> <screenshot folder>" 
		exit 1
fi

set -e
# ./screenshot.sh TvSeriesOrganizerApp/TvSeriesOrganizer :10 en screenshot
screenshot=$4
export LANGUAGE=$3
binaryName="$1 --size 1640x930"
windowName=TvSeriesOrganizer
export DISPLAY=$2
sleeptime=5
longSleepTime=7
verylongsleeptime=11
Xvfb $DISPLAY -screen 0 1920x1080x24  &
xvfb_pid=$!
sleep $longSleepTime
$binaryName  &
tso_pid=$!
sleep $longSleepTime
info=`xwininfo -display $DISPLAY -name $windowName`
id=`echo "$info" | grep "Window id" | cut -f4 -d' '`
x=`echo "$info" | grep "Absolute upper-left X" | cut -f7 -d' '`
y=`echo "$info" | grep "Absolute upper-left Y" | cut -f7 -d' '`

mkdir -p  $screenshot/

function moveClick
{
	xte -x $DISPLAY "mousemove $(($x+$1)) $(($y+$2))"
	xte -x $DISPLAY "mouseclick 1"
}

function takeScreenshot
{
	import -window $id $screenshot/$1.png
}

yTabBar=120
tabNumber=8
width=1640

function clickOnTab
{
	posxf=`echo "$width/$tabNumber*($1-1+0.5)" | bc`
	posx=${posxf/.*}
	moveClick $posx $yTabBar
}

function clickSearchInput
{
	moveClick 100 160
}

function clickAdd
{
	moveClick 790 300
}

function addSeries
{
	if [[ $3 -ne 1 ]]
	then
		clickOnTab 3
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
	sleep $sleeptime
}

function moveClickTakeScreenshot
{
	moveClick $1 $2
	sleep $sleeptime
	takeScreenshot $3
}

function clickForward
{
	moveClick 1600 15
}

function clickBack
{
	moveClick 50 20
}

function clickSettings
{
	moveClick 1600 15
}

function clickSmallCard
{
	moveClick 100 300
}

function sleepThenTakeScreenShot
{
	sleep $sleeptime
	takeScreenshot $1
}

takeScreenshot ExploreSeries

clickForward

addSeries "merlin" 1 1
addSeries "suits"
addSeries "breaking bad"

sleep $sleeptime
takeScreenshot SeriesCollectionLargeCard

clickSettings
sleep $sleeptime
takeScreenshot Settings

clickSmallCard
sleep $verylongsleeptime

clickBack

sleep $sleeptime
takeScreenshot SeriesCollectionSmallCard


moveClickTakeScreenshot 40 320 SeriesDetails
clickOnTab 2
sleepThenTakeScreenShot SeriesInfo
clickOnTab 3
sleepThenTakeScreenShot SeriesActors
clickOnTab 4
sleepThenTakeScreenShot SeriesFanArts
clickOnTab 5
sleepThenTakeScreenShot SeriesPosters
clickOnTab 1

moveClickTakeScreenshot 40 380 SeasonDetails
moveClickTakeScreenshot 40 280 EpisodeDetails

kill $tso_pid
kill $xvfb_pid