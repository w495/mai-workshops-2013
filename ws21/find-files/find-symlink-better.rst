========================
 find-symlink-better.sh
========================

------------------------------------------------
удаление всех синонимов указанного файла
------------------------------------------------

:Author: w@w-495.ru
:organization: MAI
:Date:   2014-02-15
:Copyright: public domain.
:Version: 0.0.1
:Manual section: 1
:Manual group: file processing

ОБЗОР
========

``./find-symlink-better.sh`` ``--help``

``./find-symlink-better.sh``  [-h]|[-v][-D] -d *directory* -f *file*


ОПИСАНИЕ
===========

Выполняет удаление всех синонимов указанного *файла*
из указанного *каталога* и его поддиректорий.

ПАРАМЕТРЫ
=========

-d, --dir= *directory*
    задает каталог

-f, --file= *file*
    задает файл

-v, --verbose
    включает режим трассировки

-D, --debug
    включает отладочный трассировки

-h, --help
    выводит справку


ПРИМЕРЫ
===========

``./find-symlink-better.sh``    -d */some/dir* -f  */path/to/any/file*

``./find-symlink-better.sh``    -f  */path/to/any/file* -d */some/dir*

ФАЙЛЫ
=====

better.sh

