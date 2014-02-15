#!/usr/bin/env bash

##
##  Скрипт генерирует случайные директории со случайными поддиректориями
##  и копирует создает в них файлы со случайными именами:
##      * копии всех файлов из текущей папки;
##      * жесткие ссылки файлов из текущей папки;
##      * символические ссылки файлов из текущей папки;
##      * пустые файлы.
##  При повторном запуске скрипта,
##  результаты предыдущего запуска будут удалены.
##
##  ВНИМАНИЕ:   при удалении результатов предыдущего запуска,
##              удаляться все директории из текущей папки.
##              Смиритесь, или найдите, как это исправить.
##              Подсказка: исправить это очень просто.
##
##  Если скрипт запущен как `./gentest.sh delete`, то просто будут удалены
##  результаты предыдущего запуска без создания новых директории.
##

##
## Удалим все директории в текущей папке.
## Для этого пройдемся по всему ее содержимому.
##
for i in * ; do
    ##
    ## Если встретили директорию, то удалим ее.
    ##
    if [ -d "$i" ]; then
        echo "# rm -rf $i";
        ##
        ## Удаляем рекурсивно, молча и беспощадно. Читайте `man rm`.
        ##
        rm -rf "$i";
    fi;
done;

##
## Проверим, чему равен аргумент командной строки.
## Символ `x` добавляется, чтобы избежать сравнение с пустой строкой.
##
if [ "x$1" == "xdelete" ]; then
    echo "only delete!";
    ##
    ## Выходим из скрипта с кодом `0`.
    ##
    exit 0;
fi


##
## Получим список файлов в текущей папке.
## Для этого воспользуемся конвейером командной оболочки
##
FILES=$(ls -l | grep ^- | awk '{print $9}');

##
## Случайно создадим 5 директорий
##
for i in {1..5}; do
    ##
    ## `${RANDOM}` дает случайное число
    ##

    DIRNAME1="${i}-${RANDOM}";

    echo -e "# ${i}\t-> ${DIRNAME1}";

    mkdir "${DIRNAME1}";

    ##
    ## А в пяти случайных директориях создадим 5 случайных поддиректорий.
    ##
    for i in {1..5}; do

        DIRNAME2="${i}-${i}-${RANDOM}";

        echo -e "# ${i}x${i}\t-> ${DIRNAME2}";

        mkdir "${DIRNAME1}/${DIRNAME2}";

        ##
        ## Для каждой поддиректории проведем действия над файлами
        ## из текущей папки.
        ##
        for FNAME in $FILES; do

            ##
            ## С помощью конвейера создадим строку из восьми случайных символов.
            ## Попробуйте в консоли вот такую команду:
            ##
            ##  cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 8 | head -n 1;
            ##
            ## Кстати, очень удобно для генерации каптч и паролей.
            ## На самом деле, тут мы создадим не одну строку, а шесть.
            ##

            RS=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 8 | head -n 6);

            ##
            ## Сейчас мы собираемся пройтись по списку
            ## из шести случайных строк.
            ## И для каждой выполнить разные действия.
            ## А чтобы их отличать, мы заведем счетчик
            ##
            COUNTER=0;

            for MY_RANDOM_STRING in $RS; do

                NEW_FNAME=${DIRNAME1}/${DIRNAME2}/${MY_RANDOM_STRING};

                if   [ $COUNTER -eq 1 ]; then

                    ##
                    ## Создадим копию файла
                    ##

                    cp "${FNAME}" "${NEW_FNAME}.copy";

                elif [ $COUNTER -eq 2 ]; then

                    ##
                    ## Создадим символическую ссылку.
                    ## Она будет битой.
                    ##

                    ln -s "${FNAME}" "${NEW_FNAME}";

                elif [ $COUNTER -eq 3 ]; then

                    ##
                    ## Создадим символическую ссылку.
                    ## Она будет относительной.
                    ##

                    ln -s "../../${FNAME}" "${NEW_FNAME}";

                elif [ $COUNTER -eq 4 ]; then

                    ##
                    ## Создадим символическую ссылку.
                    ## Она будет абсолютной.
                    ##

                    ln -s "${PWD}/${FNAME}" "${NEW_FNAME}";

                elif [ $COUNTER -eq 5 ]; then

                    ##
                    ## Создадим жесткую ссылку
                    ##

                    ln "${FNAME}" "${NEW_FNAME}";

                else

                    ##
                    ## Создадим пустой файл
                    ##

                    touch "${NEW_FNAME}";

                fi;

                ##
                ## Увеличиваем счетчик на единичку.
                ##

                let COUNTER=COUNTER+1;

            done;
        done;
    done;
done;