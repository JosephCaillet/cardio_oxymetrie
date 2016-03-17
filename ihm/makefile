FLAGS = -std=c99 -Wall -Wextra -g #-pedantic

carOxyIhm: main.o dataBuffer.o dataBuffer.o fenetre.o lecture.o
	gcc $(FLAGS) main.o dataBuffer.o fenetre.o lecture.o -o carOxyIhm.exe -lSDL -lSDL_ttf

main.o: main.c dataBuffer.h fenetre.h lecture.h
	gcc -c main.c $(FLAGS)

dataBuffer.o: dataBuffer.c dataBuffer.h fenetre.h
	gcc -c dataBuffer.c $(FLAGS)

fenetre.o: fenetre.c fenetre.h
	gcc -c fenetre.c $(FLAGS)

lecture.o: lecture.c lecture.h
	gcc -c lecture.c $(FLAGS)

clean:
	rm -rf *.o carOxyIhm.exe