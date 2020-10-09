
all: icsexport.exe

icsexport.exe: icsexport.c
	gcc $(wsrf)\src\icsexport.c -o $(wsrf)\bin\icsexport.exe
