all: haversine

haversine: haversine.o
	gcc haversine.o -o haversine -lm

haversine.o: haversine.c
	gcc -c haversine.c

clean:
	rm -f *.o haversine
