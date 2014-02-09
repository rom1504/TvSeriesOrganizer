# TvSeriesOrganizer
Application targetting desktop and mobile to organize your tv series

[![Build Status](https://travis-ci.org/rom1504/TvSeriesOrganizer.png?branch=master)](https://travis-ci.org/rom1504/TvSeriesOrganizer)

[Screenshots](http://download.rom1504.fr/TvSeriesOrganizer/screenshot/screenshot.html)


## Features
 * See a list of episode of a season
 * List of episodes organized by season and series
 
### Roadmap
 * Download those lists from the web
 * Download subtitles from subtitles website
 * Track the episode and series you have seen
 * Recommend you some other series you might like
 * Description and pictures of episode, season, series
 * Actors of series
 * Calendar and airing times
 * Good looking interface
 
## Installation

Dependencies : gcc >=4.8, Qt >=5.1 

### Binary
 * linux 64bit : http://download.rom1504.fr/TvSeriesOrganizer/bin/TvSeriesOrganizer.tgz

### Compilation
 * git clone --recursive git://github.com/rom1504/TvSeriesOrganizer.git
 * qmake && make
 
## Technical description
 * Programmed with c++11, Qt5 and Qml
 * The app is made with a Model View Controller organization
 * Using Qml for the view makes it possible to target both desktop and mobile with the same code
