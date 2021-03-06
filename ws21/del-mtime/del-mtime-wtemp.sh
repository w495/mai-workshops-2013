#!/usr/bin/env bash

##
##  Удаляет все файлы с указанным суффиксом, к которым
##  не было обращений указанное число дней.
##
##  Как использовать:
##      ./del-mtime-wtemp.sh <? | -h | --help> \| <папка дни [суффикс]>
##
##  Если в качестве первого аргумента указан символ ? или -h  или --help ,
##  то выводится описание программы. Если не указан суффикс файла,
##  то он считается пустой строкой, и операции производятся со всеми файлами
##  из указанной папки. Перед каждым удалением у пользователя
##  запрашивается подтверждение.
##  Модификация программы с использованием временного файла.
##


##
## Название программы
##
PROG=$0;

##
## Аргументы командной строки
##
XDIR=$1;
DAYS=$2;
SUFF=$3;

##
## Строка с описанием программы.
## Используется управление цветом.
##
HELP="
\t$PROG <? | -h | --help> \| <папка дни [суффикс]>
\t\tиз указанной директории удаляет все файлы
\t\tс указанным суффиксом, к которым не было обращений
\t\tуказанное число дней.
\t\tЕсли в качестве первого аргумента указан символ  ?
\t\tили -h  или --help , то выводится описание программы.
\t\tЕсли не указан суффикс файла, то он считается пустой строкой,
\t\tи операции производятся со всеми файлами.
\t\tПеред каждым удалением у пользователя запрашивается подтверждение.
"

##
## Вариант определения времени модификации.
## Может быть atime, ctime и mtime
##
TIME_VARIANT="mtime";

##
## Регулярное выражение, для проверки,
## является ли веденное количество дней числом.
## http://ru.wikibooks.org/wiki/Регулярные_выражения
##
NUMBER_REGEXP='^[0-9]+$';

help(){
    echo -en "Использование:$HELP" >&2;
    ## Вывод на стандартный потоки ошибок
}

##
## Проверка на то что пользователь запросил справку
##
if [ "x${XDIR}" == "x?" ]                   \
    || [ "x${XDIR}" == "x-h" ]              \
    || [ "x${XDIR}" == "x--help" ] ; then
    help;
    exit 0;
fi;

##
## Проверка на наличие директории.
##
if [ ! -d "${XDIR}" ] ; then
    echo -en "ОШИБКА: Нет такой директории: \`${XDIR}'\n" >&2;
    ## Вывод на стандартный потоки ошибок
    exit 1;
fi;

##
## Проверка что были введены дни.
##
if [ -z "${DAYS}" ] ; then
    echo -en "ОШИБКА: Не указано количество дней!\n" >&2 ;
    ## Вывод на стандартный потоки ошибок
    exit 1;
fi;

##
## Проверка является ${DAYS} числом,
## если нет то, ругаемся и останавливаем программу.
## Проверка на число осуществляется через регулярные выражения.
##
if ! [[ ${DAYS} =~ ${NUMBER_REGEXP} ]] ; then
   echo -en "ОШИБКА:  \`${DAYS}' не похоже на количество дней\n" >&2;
   ## Вывод на стандартный потоки ошибок
   exit 1;
fi

##
## Создаем временный файл
##
TEMP=$(mktemp);

##
## Найдем все указанные файлы.
## Сразу же их записываем во временный файл.
## Для этого мы воспользуемся tee.
##
FILES=$(find "${XDIR}" -type f -name "*${SUFF}" "-${TIME_VARIANT}" "+${DAYS}" | tee "${TEMP}" ) ;

##
## До тех пор пока в FILES не пустая строка,
## читаем из временного файла по одной строке,
##
##
while [ ! "x${FILES}" == "x" ] ; do
    RES=$(head -1 "${TEMP}") ;
    ##
    ## Запрашиваем подтверждение у пользователя.
    ##
    read -p "Вы уверены, что хотите удалить файл \`${RES}'? [д\Н]: " ANS ;
    if [ "x${ANS}" == "xд" ] ; then
        ##
        ## Удаляем файл, если получили на то подтверждение.
        ##
        rm -f "$RES" ;
    fi ;
    ##
    ## Удаляем из файла одно строку с помощью sed.
    ## Результат кладем обратно во временный файл.
    ##
    FILES=$(sed '1d' "${TEMP}" | tee ${TEMP}) ;
done ;

