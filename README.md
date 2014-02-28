# TvSeriesOrganizer
Application targetting desktop and mobile to organize your tv series

[![Build Status](https://travis-ci.org/rom1504/TvSeriesOrganizer.png?branch=master)](https://travis-ci.org/rom1504/TvSeriesOrganizer)

[Screenshots](http://download.rom1504.fr/TvSeriesOrganizer/screenshot/screenshot.php)


## Features
 * List of episodes organized by season and series
 * From  http://www.thetvdb.com/ database, download list of episode and season with :
   * banners
   * poster
   * description
   * name
 * Good looking interface
 * Track the episode and series you have seen
 
### Roadmap
 * Download subtitles from subtitles website
 * Recommend you some other series you might like
 * Actors of series
 * Calendar and airing times
 * Explore series
 
## Installation

### Binary
 * linux 64bit : http://download.rom1504.fr/TvSeriesOrganizer/linux/TvSeriesOrganizer.tgz
 * android : http://download.rom1504.fr/TvSeriesOrganizer/android/TvSeriesOrganizer.apk

### Compilation
Dependencies : gcc >=4.8, Qt >=5.1 

Two possibilities :
 * git clone --recursive git://github.com/rom1504/TvSeriesOrganizer.git && cd TvSeriesOrganizer && qmake && make
 * git clone --recursive git://github.com/rom1504/TvSeriesOrganizer.git && cd TvSeriesOrganizer && qtcreator TvSeriesOrganizer.pro
 
## Technical description
 * Programmed with c++11, Qt5 and Qml
 * The app is made with a Model View Controller organization
 * Using Qml for the view makes it possible to target both desktop and mobile with the same code
