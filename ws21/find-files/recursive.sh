#!/usr/bin/env bash

##
## Процедура обработки.
##
handle() {
    local fullname="$1";
    local filename=$(basename "$1");
    local fileext="${filename##*.}";
    local ext2lower=$(echo "${ext}" | tr "A-Z" "a-z");

    ##
    ## Что угодно ...
    ##

    echo  ${fullname};
}

##
## Процедура сканирования.
##
scan() {
    ##
    ## Убираем завершающий `/`
    ##
    local dir="${1%\/}";
    for e in "${dir}"/*; do
        if [ -d "$e" -a ! -L "$e" ]; then
            scan "$e";
        else
            handle "$e";
        fi;
    done;
}

##
## `$#` --- число аргументов командной строки.
## Если их `0`, то работаем с текущей директорией.
##
[ $# -eq 0 ] && dir=${PWD} || dir=$@


scan "${dir}"
