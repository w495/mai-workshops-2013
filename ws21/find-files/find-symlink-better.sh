#!/usr/bin/env bash

##
## Выполняет удаление всех синонимов указанного файла
## из указанного каталога и его поддиректорий.
## Вариант с трассировкой и POSIX-аргументами.
##

PROGNAME=$0;

##
## Печатает сообщение об ошибке и выходит из скрипта с кодом `1`.
##
error () {
    echo -e  "ERROR: $PROGNAME: $@" ; usage; exit 1 ;
}

##
## Печатает предупреждение.
##
warn () {
    echo -e "WARN: $PROGNAME: $@";
}

##
## Печатает информационное сообщение,
## если программа была запущена с ключом `-v`.
## Т. е. в режиме трассировки.
##
verbose() {
    [[ "x${verbose}" = "xyes" ]] && echo -e "# verbose: $@" 1>&2;
}

##
## Печатает отладочное сообщение,
## если программа была запущена с ключом `-d`.
## Т. е. в режиме трассировки.
##
debug() {
    [[ "x${debug}" = "xyes" ]] && echo -e "# debug: $@" 1>&2;
}

##
## Проверяет входную строку на пустоту.
## Если строку пустая, печатает сообщение и завершает программу.
##
if_empty(){
    if [  -z "$1" ]; then
        error "$@";
    fi;
}

##
## Выводит справку
##
usage () {
cat <<USAGE
    Delete all symlinks for <file> from <directory>.
        $PROGNAME [-h]|[-v][-D] -d <directory> -f <file>
            -h          | --help            shows this test.
            -d <DIR>    | --dir =  <DIR>    sets directory.
            -f <FILE>   | --file = <FILE>   sets file.
            -v          | --verbose         uses verbose mode.
                                            It tells about all.
            -D          | --debug           uses debug mode.
                                            It tells more.
    EXAMPLES:
        $PROGNAME    -d /some/dir -f  /path/to/any/file
        $PROGNAME    -f  /path/to/any/file -d /some/dir
USAGE
}


(( $# == 0  )) && { usage ; exit 1 ; }

_args=$(getopt -o hvDd:f: -l "help,verbose,debug,dir:,file:" -n $0 --  "$@");
set -- $_args;

verbose="no";
denug="no";
dir=""
file=""

##
## Читаем в цикле аргументы командной строки,
## и предпринимаем соответствующие действия.
##
while [[ -n $_args ]] ; do
    case $1 in
        -h|--help)      usage               ;exit 0;;
        -v|--verbose)   verbose="yes"       ;shift;;
        -D|--debug)     debug="yes"         ;shift;;
        -d|--dir)       dir=$2              ;shift 2;;
        -f|--file)      file=$2             ;shift 2;;
        '--')                                break;;
        *) echo $'\n'"Unknown parameter '$1'."$'\n' ; usage ; exit 1 ;;
    esac;
done;

verbose "dir = ${dir%/}";
verbose "file = ${file}";

dir="${dir//\'}"
file="${file//\'}"

##
## Проверяем что оба аргумента не пустые.
##
if_empty "${dir}"   "there is no directory";
if_empty "${file}"  "there is no file";

##
## Проверяем что директория существует.
##
if [ ! -d "${dir}" ]; then
  error "the ${dir} argument must be a directory";
fi;

##
## Проверяем что файл существует.
##
if [ ! -f "${file}" ]; then
  error "the ${file} argument must be a file";
fi;


##
## Находим "похожие" файлы и запоминаем их в переменной `FILES`.
## Попутно выводим, как можно было бы сделать тоже самое,
## в простейшем варианте скрипта.
##
verbose 'find -L "${dir}" -samefile "${file}"';
verbose "find -L \"${dir}\" -samefile \"${file}\"";

files=$(find -L "${dir}" -samefile "${file}");

debug "files = ${files}";

##
## Фильтруем переменную `FILES`,
## чтобы исходного файла в итоге в списке не было.
## Сохраняем результат в переменной `XFILES`.
## Попутно выводим, как можно было бы сделать тоже самое,
## в простейшем варианте скрипта.
##
verbose 'find -L "${dir}" -samefile "${file}" grep -v "${file}" ';
verbose "find -L \"${dir}\" -samefile \"${file}\" | grep -v \"${file}\" ";

xfiles=$(echo "${files}" | grep -v "${file}");

debug "xfiles = ${xfiles}";

##
## Удаляем все файлы из отфильтрованного списка.
## Попутно выводим, как можно было бы сделать тоже самое,
## в простейшем варианте скрипта.
##
verbose 'find -L "${dir}" -samefile "${file}" grep -v "${file}" | xargs -i rm {} ';
verbose "find -L \"${dir}\" -samefile \"${file}\" | grep -v \"${file}\" | xargs -i rm {} ";

$(echo "${xfiles}" | xargs -i rm {});

verbose "yeah.";
