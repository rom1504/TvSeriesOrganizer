#!/bin/sh
appname=TvSeriesOrganizer

dirname=`dirname $0`

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$dirname/qtlib
export LD_LIBRARY_PATH
$dirname/$appname "$@"

