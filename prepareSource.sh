#!/bin/bash
string=`cat ./.build`
set -f
IFS="."
array=($string)
IFS=" "
echo ${array[1]}
major=${array[0]}
minor=${array[1]}
patch=${array[2]}
build=$1
cat app_info.h | sed s/B1/$build/g > appinfo.h
cat appinfo.h
mv appinfo.h app_info.h
bnr=$string
echo "##teamcity[buildNumber '$bnr.$build']"
