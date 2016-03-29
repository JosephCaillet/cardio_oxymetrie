FLAGS=-Wall -Wextra #-pedantic

carOxyAcq: main.o fir.o iir.o lecture.o mesure.o affichage.o dataBuffer.o
	gcc main.o fir.o iir.o lecture.o mesure.o affichage.o dataBuffer.o -o carOxyAcq.exe

main.o: main.c fir.h iir.h lecture.h mesure.h affichage.h dataBuffer.h define.h
	gcc -c main.c -o main.o $(FLAGS)

fir.o: fir.c fir.h iir.h lecture.h mesure.h affichage.h dataBuffer.h define.h
	gcc -c fir.c -o fir.o $(FLAGS)

iir.o: iir.c fir.h iir.h lecture.h mesure.h affichage.h dataBuffer.h define.h
	gcc -c iir.c -o iir.o $(FLAGS)

lecture.o: lecture.c fir.h iir.h lecture.h mesure.h affichage.h dataBuffer.h define.h
	gcc -c lecture.c -o lecture.o $(FLAGS)

mesure.o: mesure.c fir.h iir.h lecture.h mesure.h affichage.h dataBuffer.h define.h
	gcc -c mesure.c -o mesure.o $(FLAGS)

affichage.o: affichage.c fir.h iir.h lecture.h mesure.h affichage.h dataBuffer.h define.h
	gcc -c affichage.c -o affichage.o $(FLAGS)

dataBuffer.o: dataBuffer.c fir.h iir.h lecture.h mesure.h affichage.h dataBuffer.h define.h
	gcc -c dataBuffer.c -o dataBuffer.o $(FLAGS)

test: test.o fir.o iir.o lecture.o mesure.o affichage.o dataBuffer.o
	gcc test.o fir.o iir.o lecture.o mesure.o affichage.o dataBuffer.o -o test.exe

test.o: test.c fir.h iir.h lecture.h mesure.h affichage.h dataBuffer.h define.h
	gcc -c test.c -o test.o $(FLAGS)

clean:
	rm -rf *.o carOxyAcq.exe test.exe