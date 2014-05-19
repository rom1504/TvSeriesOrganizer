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
binaryName="$1 --size 580x880"
windowName=TvSeriesOrganizer
export DISPLAY=$2
sleeptime=5
longSleepTime=7
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
	moveClick 560 15
}

function clickBack
{
	moveClick 50 20
}

function clickSettings
{
	moveClick 550 15
}

function clickSmallCard
{
	moveClick 100 270
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
sleep $sleeptime

clickBack

sleep $sleeptime
takeScreenshot SeriesCollectionSmallCard


moveClickTakeScreenshot 40 320 SeriesDetails
moveClickTakeScreenshot $tab2 $yTabBar SeriesInfo
moveClickTakeScreenshot $tab3 $yTabBar SeriesActors
moveClickTakeScreenshot $tab3 $yTabBar SeriesFanArts
moveClickTakeScreenshot $tab3 $yTabBar SeriesPosters
moveClick $tab1 $yTabBar
moveClick $tab1 $yTabBar
moveClick $tab1 $yTabBar

moveClickTakeScreenshot 40 380 SeasonDetails
moveClickTakeScreenshot 40 280 EpisodeDetails

kill $tso_pid
kill $xvfb_pid