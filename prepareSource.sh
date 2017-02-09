#!/bin/bash
string=`cat ./.build`
set -f
array=${string//./}
echo $array
major=${array[0]}
minor=${array[1]}
patch=${array[2]}
build=$0
cat app_info.h | sed "s/M1/$major/g" | sed s/M2/$minor/g | sed s/P1/$patch/g | sed s/B1/$build/g > ./app_info.h
bnr=`sudo cat %teamcity.build.checkoutDir%/.build`
echo $bnr
echo "##teamcity[buildNumber '$bnr.$build']"