
CC = gcc

FILE_SRC = genics/icsexport genics/global genics/boot genics/other genics/dateop genics/fop genics/proc genics/clk genics/analyzer genics/output
FILE_H = genics/defs.h

build: $(addprefix src/, $(addsuffix .c, $(FILE_SRC))) $(addprefix src/, $(FILE_H))
	$(CC) -o $(addprefix bin/, icsexport.exe) $(addprefix src/, $(addsuffix .c, $(FILE_SRC)))

build-debug: $(addprefix src/, $(addsuffix .c, $(FILE_SRC))) $(addprefix src/, $(FILE_H))
	$(CC) -g -o $(addprefix bin/, icsexport.exe) $(addprefix src/, $(addsuffix .c, $(FILE_SRC)))
