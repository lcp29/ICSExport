
CC = gcc

FILE_SRC = icsexport global boot other dateop fop proc clk analyzer output
FILE_H = defs.h

build: $(addprefix src/, $(addsuffix .c, $(FILE_SRC))) $(addprefix src/, $(FILE_H))
	$(CC) -o $(addprefix bin/, icsexport.exe) $(addprefix src/, $(addsuffix .c, $(FILE_SRC)))

build-debug: $(addprefix src/, $(addsuffix .c, $(FILE_SRC))) $(addprefix src/, $(FILE_H))
	$(CC) -g -o $(addprefix bin/, icsexport.exe) $(addprefix src/, $(addsuffix .c, $(FILE_SRC)))
