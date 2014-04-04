##
## Зададим имя для исполняемого файла.
##
EXECUTABLE=swap-dual-list

all:
	(cd src && $(MAKE) all) \
	&& mv src/$(EXECUTABLE) ./$(EXECUTABLE) \
	|| exit 1;

cleanall: clean
	rm -rf $(EXECUTABLE)

clean:
	(cd src && $(MAKE) clean)
