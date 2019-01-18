CC=gcc
CFLAGS=-Wall -O2 -Wno-unused-result -g 
LIB = -lm
OBJ = main.o image.o lut.o histogram.o conversion.o
DIRNAME = $(shell basename $$PWD)
BIN = ./bin/minigimp
RM = rm -f
BACKUP = $(shell date + `basename $$PWD`-%m.%d.%H.%M.zip)
STDNAME = $(DIRNAME).zip

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(BIN)
	@echo "COMPIL OK"


image.o: ./src/image.c ./src/image.h ./src/pixel.h
	$(CC) $(CFLAGS) -c $<
	@echo "Compil image ok"

lut.o : ./src/lut.c ./src/lut.h
	$(CC) $(CFLAGS) -c $<
	@echo "Compil LUT ok"

histogram.o : ./src/histogram.c ./src/histogram.h
	$(CC) $(CFLAGS) -c $<
	@echo "Compil histo ok"

conversion.o : ./src/conversion.c ./src/conversion.h
	$(CC) $(CFLAGS) -c $<
	@echo "Compil conversion LUT ok"

main.o: ./src/main.c image.o lut.o histogram.o
	$(CC) $(CFLAGS) -c $<
	@echo "Compil main ok"

clean:
	$(RM) *~ $(OBJ) $(BIN)
	@echo "Clean"

zip: clean
	@echo "ZIP"
	cd ..&& zip -r $(BACKUP) $(DIRNAME)