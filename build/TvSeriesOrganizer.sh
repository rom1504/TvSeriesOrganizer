#!/bin/sh
appname=TvSeriesOrganizer


if [ `basename $0` = $appname ]
then
dirname="/opt/TvSeriesOrganizer"
else
dirname=`dirname $0`
fi

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$dirname/qtlib
export LD_LIBRARY_PATH
$dirname/$appname "$@"

