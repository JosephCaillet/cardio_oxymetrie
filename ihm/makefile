FLAGS = -std=c99 -Wall -Wextra -g #-pedantic

carOxyIhm: main.o dataBuffer.o dataBuffer.o fenetre.o
	gcc $(FLAGS) main.o dataBuffer.o fenetre.o -o carOxyIhm.exe -lSDL

main.o: main.c dataBuffer.h fenetre.h
	gcc -c main.c $(FLAGS)

dataBuffer.o: dataBuffer.c dataBuffer.h
	gcc -c dataBuffer.c $(FLAGS)

fenetre.o: fenetre.c fenetre.h
	gcc -c fenetre.c $(FLAGS)

clean:
	rm -rf *.o carOxyIhm.exe