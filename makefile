FLAGS=-Wall -Wextra -pedantic

carOxyAcq: main.o firPB.o irrPH.o lecture.o mesure.o affichage.o dataBuffer.o
	gcc main.o firPB.o irrPH.o lecture.o mesure.o affichage.o dataBuffer.o -o carOxyAcq

main.o: main.c firPB.h irrPH.h lecture.h mesure.h affichage.h dataBuffer.h
	gcc -c main.c -o main.o $(FLAGS)