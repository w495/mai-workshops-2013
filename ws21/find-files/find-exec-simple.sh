#!/usr/bin/env bash

##
## Выполняет рекурсивный обход и подсчет числа выполнимых файлов
## в каталоге и в поддиректориях.
##

PROG=$0
DIR=$1

if [  -z "${DIR}" ]; then
echo "${PROG} <directory>
    Finds executable files in <directory> and it's subdirs
    and counts'em all.
"
    exit 1;
fi;

if [ ! -d "${DIR}" ]; then
  error "the ${DIR} argument must be a directory";
fi;

find "${DIR}" -type f -executable | wc -l
