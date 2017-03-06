echo off
cls
title Demarrage cardio oxymetrie
echo �������������������������������������������ͻ
echo � Demarrage cardio oxymetrie                �
echo � Copyright ISEN 2015/2016                  �
echo � Made by Joseph CAILLET and Thomas COUSSOT �
echo �������������������������������������������ͼ
echo.

if exist .verrouData (del .verrouData)
if exist .verrouData2 (del .verrouData2)

echo Modes disponibles:
echo 	fic : mode simulation, donnees lues depuis le fichier rec/record1.dat.
echo 	usb : mode usb, donnees lues depuis la carte via usb.
set /p mode= Mode choisi: 

if "%mode%" == "fic" (
	cd ihm
	start carOxyIhm.exe --hideACvalues
	cd ..
	call carOxyAcq.exe rec/record1.dat
) else (
	if "%mode%" == "usb" (
		cd ihm
		start carOxyIhm.exe --hideACvalues
		cd ..
		call carOxyAcq.exe
	) else (
		echo Saisie incorrecte: %mode% n'est pas un mode disponible.
	)
)

echo.
pause