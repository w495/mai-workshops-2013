## 
## Определим компилятор.
## 
CC=gcc

## 
## Определим сборщик.
## 
LD=gcc

## 
## Зададим флаги компиляции.
## 
CFLAGS=-c -Wall -pedantic -std=c99

## 
## Зададим флаги сборки.
## В них мы подключаем библиотеку libm
## 
LDFLAGS=

## 
## Зададим имя для исполняемого файла.
## 
EXECUTABLE=swap-dual-list

## 
## Опишем модули программы
## 
MODULES=list main_list

##
## Строка с исходными кодами.
##
SOURCES  = $(patsubst %,%.c,$(MODULES))

##
## Строка с объектными файлами.
##
OBJECTS  = $(patsubst %,%.o,$(MODULES))


## 
## Опишем суффиксы, которые используются в целях.
## 
.SUFIXES: .h .c .o

## 
## Цели, которые не создают одноименных файлов.
## 
.PHONY : all depend 		\
	clean clean_obj 	\
	pack clean_pack repack 	\
	snapshot clean_snapshots

##
## Соберем "всё", т.е. соберем исполняемый файл.
## Псевдоним для цели `$(EXECUTABLE)`.
##	
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	# 
	# 	Собираем исполняемый файл из объектных.
	# 
	$(LD) $(LDFLAGS) $^ -o $@

%.o:  %.c
	$(CC) $(CFLAGS) $< -o $@


clean: clean_obj
	# 
	# 	Удаляем исполняемый файл.
	# 
	rm -f "$(EXECUTABLE)";
	rm -f *~
	
clean_obj:
	# 
	# 	Удаляем объектные файлы.
	# 
	rm -f $(OBJECTS);

