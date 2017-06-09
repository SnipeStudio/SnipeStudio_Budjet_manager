#!/bin/bash
build=$1
cat app_info.h | sed s/B1/$build/g > appinfo.h
cat appinfo.h
mv appinfo.h app_info.h
bnr=$string
echo "##teamcity[buildNumber '$bnr.$build']"
