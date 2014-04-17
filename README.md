# TvSeriesOrganizer
Application targetting desktop and mobile to organize your tv series

[![Build Status](https://travis-ci.org/rom1504/TvSeriesOrganizer.png?branch=master)](https://travis-ci.org/rom1504/TvSeriesOrganizer) <a href="https://play.google.com/store/apps/details?id=com.rom1504.TvSeriesOrganizer">
  <img  width="80px" alt="Get it on Google Play"
       src="https://developer.android.com/images/brand/en_generic_rgb_wo_45.png" />
</a>  <a href="https://www.transifex.com/projects/p/tvseriesorganizer/"><img src="https://ds0k0en9abmn1.cloudfront.net/static/charts/images/tx-logo-micro.646b0065fce6.png"/></a>  [Screenshots](http://download.rom1504.fr/TvSeriesOrganizer/screenshot/screenshot.php)   <a href="https://plus.google.com/110075491961402357259" rel="publisher">Google+</a>    <a href="https://www.facebook.com/TvSeriesOrganizer">Facebook</a>   <a href="https://twitter.com/TvSeriesOrga">Twitter</a>


Translations are done with [Transifex](https://www.transifex.com/projects/p/tvseriesorganizer/), you can contribute there if you want



## Features
 * List of episodes organized by season and series
 * From  http://www.thetvdb.com/ database, download list of episode and season with :
   * banners
   * poster
   * description
   * name
 * Good looking interface
 * Track the episode and series you have seen
 * Air time of episodes
 * Display upcoming series/season/episode
 * Search and add any series you want
 * Explore series using http://trakt.tv/ database
 * See all the actors of the tv series : importance in the series, names and role
 
### Roadmap
 * Download subtitles from subtitles website
 * Recommend you some other series you might like
 * Calendar and airing times
 
## Installation

### Binary
 * linux 64bit : http://download.rom1504.fr/TvSeriesOrganizer/linux/TvSeriesOrganizer.tgz
 * ubuntu 64bit : http://download.rom1504.fr/TvSeriesOrganizer/ubuntu/TvSeriesOrganizer.deb
 * android : http://download.rom1504.fr/TvSeriesOrganizer/android/TvSeriesOrganizer.apk

### Compilation
Dependencies : gcc >=4.8, Qt >=5.2.1

Two possibilities :
 * git clone --recursive git://github.com/rom1504/TvSeriesOrganizer.git && cd TvSeriesOrganizer && qmake && make
 * git clone --recursive git://github.com/rom1504/TvSeriesOrganizer.git && cd TvSeriesOrganizer && qtcreator TvSeriesOrganizer.pro
 
## Technical description
 * Programmed with c++11, Qt5 and Qml
 * The app is made with a Model View Controller organization
 * Using Qml for the view makes it possible to target both desktop and mobile with the same code

## Languages
All series, season and episode text translation have been done in many languages by thetvdb contributors.
The text of this application (menu, google play description, buttons, ...) have been translated from English in :
 * French (rom1504)
 * Italian (giuseppep (https://www.transifex.com/accounts/profile/giuseppep/))
 * Romanian (ArianServ (https://www.transifex.com/accounts/profile/ArianServ/))