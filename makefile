
# wsf = 工作区根目录

build: $(wsf)\src\icsexport.c
	gcc $(wsf)\src\icsexport.c -o $(wsf)\bin\icsexport.exe
