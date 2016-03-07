FLAGS=-Wall -Wextra -pedantic

carOxyAcq: main.o firPB.o irrPH.o lecture.o mesure.o affichage.o dataBuffer.o
	gcc main.o firPB.o irrPH.o lecture.o mesure.o affichage.o dataBuffer.o -o carOxyAcq.exe

main.o: main.c firPB.h irrPH.h lecture.h mesure.h affichage.h dataBuffer.h
	gcc -c main.c -o main.o $(FLAGS)

firPB.o: firPB.c firPB.h irrPH.h lecture.h mesure.h affichage.h dataBuffer.h
	gcc -c firPB.c -o firPB.o $(FLAGS)

irrPH.o: irrPH.c firPB.h irrPH.h lecture.h mesure.h affichage.h dataBuffer.h
	gcc -c irrPH.c -o irrPH.o $(FLAGS)

lecture.o: lecture.c firPB.h irrPH.h lecture.h mesure.h affichage.h dataBuffer.h
	gcc -c lecture.c -o lecture.o $(FLAGS)

mesure.o: mesure.c firPB.h irrPH.h lecture.h mesure.h affichage.h dataBuffer.h
	gcc -c mesure.c -o mesure.o $(FLAGS)

affichage.o: affichage.c firPB.h irrPH.h lecture.h mesure.h affichage.h dataBuffer.h
	gcc -c affichage.c -o affichage.o $(FLAGS)

dataBuffer.o: dataBuffer.c firPB.h irrPH.h lecture.h mesure.h affichage.h dataBuffer.h
	gcc -c dataBuffer.c -o dataBuffer.o $(FLAGS)

clean:
	rm -rf *.o carOxyAcq.exe