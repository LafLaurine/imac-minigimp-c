CC=gcc
CFLAGS=-Wall


mon_executable: main.o chargerImg.o lut.o
	$(CC) -o $@ $^

main.o: main.c chargerImg.h
	$(CC) -o $@ -c $< $(CFLAGS)

chargerImg.o: chargerImg.c chargerImg.h
	$(CC) -o $@ -c $< $(CFLAGS)

lut.o : lut.c lut.h
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -rf *.o
