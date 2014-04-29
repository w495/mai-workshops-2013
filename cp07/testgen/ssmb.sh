#!/usr/bin/env bash

##
## $> bash ./ssmb.sh 42
## 9 14
## 888 0   0   0   888 0   0   0   888 888 888 0   0   0
## 888 0   0   0   888 0   0   888 0   0   0   888 0   0
## 888 0   0   0   888 0   0   888 0   0   0   888 0   0
## 888 888 888 888 888 0   0   0   0   0   888 0   0   0
## 0   0   0   0   888 0   0   0   0   888 0   0   0   0
## 0   0   0   0   888 0   0   0   888 0   0   0   0   0
## 0   0   0   0   888 0   0   888 888 888 888 888 0   0
##

STRING="MAI";
NULL="0  ";
NOTN="888";

if [ "x$1" != "x" ]; then
    STRING=$1;
fi;

if [ "x$2" != "x" ]; then
    NULL=$2;
fi;

if [ "x$3" != "x" ]; then
    NOTN=$3;
fi;

FILE=$(mktemp);
banner ${STRING} | sed "s/ /${NULL} /gi" | sed "s/#/${NOTN} /gi" > ${FILE};
HEIGHT=$(wc -l ${FILE} | sed 's/[ ].*//gi');
WIDTH=$(head -2 ${FILE} | wc -w | sed 's/[ ].*//gi');

echo -n ${HEIGHT} ${WIDTH};
head -n -1 ${FILE};

