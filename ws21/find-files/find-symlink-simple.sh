#!/usr/bin/env bash

##
## Выполняет удаление всех синонимов указанного файла
## из указанного каталога и его поддиректорий.
## Простейший вариант скрипта.
## Запускать его нужно так:
##      ./find-symlink-simple.sh <директория> <file>
##

DIR=$1;
FILE=$2;

echo
echo "Find the same files (symbolic links) for \"${FILE}\" in \"${DIR}\"";
echo "Here they are: "
echo

find -L "${DIR}" -samefile "${FILE}"

echo
echo "And without \"${FILE}\" they are: "
echo

find -L "${DIR}" -samefile "${FILE}" | grep -v "${FILE}"

echo
echo "Ok! Kill'em all except \"${FILE}\" itself."
echo

find -L "${DIR}" -samefile "${FILE}" | grep -v "${FILE}" | xargs -i rm {}

echo

