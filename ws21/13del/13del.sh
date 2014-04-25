#! /usr/bin/env bash

##
## Удаление файлов с указанным префиксом, длина которых находится
## в указанном диапазоне.
##
## Автор: Зельднер Людмила Григорьевна,
## студентка группы 8о-101Б, МАИ, 2014 г.
##

PROGNAME=$0;
STAND="используется значение по умолчанию";

# Идем по параметрам в цикле
while [[ -n $@ ]] ; do
case $1 in
        '?'|'-h')
            echo "
Использование:
Удаление файлов с указанным префиксом, длина которых находится в указанном диапазоне.
    ? или -h  показывет этот текст.
    -i режим информации - печать действий
Примеры
    $PROGNAME <dir> <pref> <min> <max>
Единица измерения min, max - 512 байт"
            exit 0;;
        '-i')
            INF=y;
            shift;;
        *)
            DIR=$1 #директория
            shift;
            PR=$1  #префикс
            shift;
            MIN=$1 #начало диапазона
            shift;
            MAX=$1 #конец диапазона
            shift;

            if [ "x${DIR}" = "x" ]
            then
                echo "Не введена директория - $STAND: текущая директория";
                DIR=.;
            fi
            if [ "x${PR}" = "x" ]
            then
                echo "Не введен префикс - $STAND: inf";
                PR=inf;
            fi
            if [ "x${MIN}" = "x" ]
            then
                echo "Не введен минимум - $STAND: 0";
                MIN=0;
            fi
            if [ "x${MAX}" = "x" ]
            then
                echo "Не введен максимум - $STAND: 100000 (~5M)";
                MAX=100000;
            fi

            if [ ! -d "${DIR}" ]
            then
                echo "Такой директории не существует."
                exit 1;
            fi

            NUMBER_REGEXP='^[0-9]+$';
            if ! [[ ${MIN} =~ ${NUMBER_REGEXP} ]]
            then
                echo "Левая граница не является числом - $STAND: 0"
                MIN=0;
            fi
            if ! [[ ${MAX} =~ ${NUMBER_REGEXP} ]]
            then
                echo "Правая граница не является числом - $STAND: 100000 (~5M)"
                MAX=100000;
            fi

            if [ "$MIN" -gt "$MAX" ]
                then echo "Введенная левая граница больше правой (!)"

            fi
            if [ "x${INF}" = "xy" ]
            then
                echo "find ${DIR} -type f -name '${PR}*' -size +${MIN} -size -${MAX}"
            fi
            find "${DIR}" -type f -name "${PR}*" -size +"${MIN}" -size -"${MAX}" -delete
            exit 0;;
    esac;
done;

# Если параметры не введены
echo "Не введены параметры - используются значения по умолчанию:
текущая директория, inf, 0 - 100000 (~5M)"

# Устанавливаем значения по умолчанию
DIR=.; #директория
PR=inf;  #префикс
MIN=0; #начало диапазона
MAX=100000; #конец диапазона
echo "find \"${DIR}\" -type f -name \"${PR}*\" -size +\"${MIN}\" -size -\"${MAX}\""
find "${DIR}" -type f -name "${PR}*" -size +"${MIN}" -size -"${MAX}" -delete







