#!/usr/bin/env bash

##
## Выполняет удаление всех синонимов указанного файла
## из указанного каталога и его поддиректорий.
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
## если программа была запущена с ключом `-i`.
## Т. е. в режиме трассировки.
##
info() {
    [[ "x${info}" = "xyes" ]] && echo -e "# info: $@" 1>&2;
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
## Выводит справку
##
usage () {
echo "
USAGE:
   Delete all symlinks for <file> from <directory>.
   $PROGNAME [-i][-D]  ? | [<directory> <file>]
     ? shows this text.
    -i uses info mode. It tells about really actions.
    -D uses debug mode. It tells about all events.

EXAMPLES:
    $PROGNAME         /some/dir /path/to/any/file
    $PROGNAME -i      /some/dir /path/to/any/file
    $PROGNAME -D      /some/dir /path/to/any/file
    $PROGNAME -i -D   /some/dir /path/to/any/file
"
}

##
## Читаем в цикле аргументы командной строки,
## и предпринимаем соответствующие действия.
##
while [[ -n $@ ]] ; do
    case $1 in
        '?')
            usage;
            exit 0;;
        '-i')
            info="yes";
            info "info\t\t\t= ${info}";
            shift;;
        '-D')
            debug="yes";
            debug "debug\t\t\t= ${debug}";
            shift;;
        '--')
            usage;
            break;;
        *)
            DIR=$1;
            shift;
            FILE=$1;
            shift;

            info "directory\t\t= ${DIR}" ;
            info "file\t\t\t= ${FILE}" ;

            ##
            ## Проверяем оба ли аргумента введены.
            ##
            [[ "x${DIR}" = "x" ]]                               \
                && error $'\n'"Wrong usage! Where is dir?"$'\n';
            [[ "x${FILE}" = "x" ]]                              \
                && error $'\n'"Wrong usage! Where is file?"$'\n';

            DIRPATH=$(readlink -e  ${DIR});
            FILEPATH=$(readlink -e  ${FILE});

            info "directory full path\t= ${DIRPATH}" ;
            info "file full path\t\t= ${FILEPATH}" ;

            ##
            ## Проверяем есть ли такие папка и файл.
            ## Если их не существует, то после `readlink -e`
            ## Вернется пустая строка.
            ## Такую проверку можно осуществлять иначе:
            ##
            ## if [ -d ${DIRPATH}  ]; then ... fi;
            ##
            ## if [ -f ${FILEPATH} ]; then ... fi;
            ##
            [[ "x${DIRPATH}" = "x" ]]                               \
                && error $'\n'"Wrong usage! No such dir?"$'\n';
            [[ "x${FILEPATH}" = "x" ]]                               \
                && error $'\n'"Wrong usage! No such file?"$'\n';

            info "GO!"

            ##
            ## Находим "похожие" файлы и запоминаем их в переменной `FILES`.
            ## Попутно выводим, как можно было бы сделать тоже самое,
            ## в простейшем варианте скрипта.
            ##
            info '\tfind -L "${DIRPATH}" -samefile "${FILEPATH}"' ;
            FILES=$(find -L "${DIRPATH}" -samefile "${FILEPATH}");
            debug "files are the same to ${FILE} = {${FILES}}";

            ##
            ## Фильтруем переменную `FILES`,
            ## чтобы исходного файла в итоге в списке не было.
            ## Сохраняем результат в переменной `XFILES`.
            ## Попутно выводим, как можно было бы сделать тоже самое,
            ## в простейшем варианте скрипта.
            ##
            info '\tfind -L "${DIRPATH}" -samefile "${FILEPATH}" | grep -v "${FILEPATH}' ;
            XFILES=$(echo "${FILES}" | grep -v "${FILEPATH}");
            debug "files without \"${FILE}\" they = {${XFILES}}"

            ##
            ## Удаляем все файлы из отфильтрованного списка.
            ## Попутно выводим, как можно было бы сделать тоже самое,
            ## в простейшем варианте скрипта.
            ##
            info '\tfind -L "${DIRPATH}" -samefile "${FILEPATH}" | grep -v "${FILEPATH} | xargs -i rm {}' ;
            $(echo "${XFILES}" | xargs -i rm {});
            info "done."

            exit 0;;
    esac;
done;

##
## Если мы добрались до этой строчки,
## значит параметры введены не было
##
echo $'\n'"Wrong usage!"$'\n'
usage;

