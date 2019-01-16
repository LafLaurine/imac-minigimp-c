CC=gcc
CFLAGS=-Wall
DIRNAME = $(shell basename $$PWD)
BACKUP = $(shell date + `basename $$PWD`-%m.%d.%H.%M.zip)
STDNAME = $(DIRNAME).zip

minigimp: main.o image.o lut.o histogram.o conversion.o
	$(CC) -o $@ $^ -lm
	@echo "COMPIL OK"

main.o: main.c image.h pixel.h lut.h histogram.h
	$(CC) -o $@ -c $< $(CFLAGS)

chargerImg.o: image.c image.h pixel.h
	$(CC) -o $@ -c $< $(CFLAGS)

lut.o : lut.c lut.h
	$(CC) -o $@ -c $< $(CFLAGS)


histogram.o : histogram.c histogram.h
	$(CC) -o $@ -c $< $(CFLAGS)

conversion.o : conversion.c conversion.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

zip:
	@echo "ZIP"
	cd ..& zip -r $(BACKUP) $(DIRNAME)