
CC = gcc

FILE_SRC = icsexport global
FILE_H = defs.h

build: $(addprefix obj/, $(addsuffix .o, $(FILE_SRC)))
	$(CC) -o $(addprefix bin/, icsexport.exe) $(addprefix obj/, $(addsuffix .o, $(FILE_SRC)))

build-debug: $(addprefix obj/, $(addsuffix .o, $(FILE_SRC)))
	$(CC) -g -o $(addprefix bin/, icsexport.exe) $(addprefix obj/, $(addsuffix .o, $(FILE_SRC)))

$(addprefix obj/, $(addsuffix .o, $(FILE_SRC))): $(addprefix src/, $(addsuffix .c, $(FILE_SRC))) $(addprefix src/, $(FILE_H))
	$(foreach name, $(FILE_SRC), $(CC) -c $(addprefix src/, $(addsuffix .c, $(name))) -o $(addprefix obj/, $(addsuffix .o, $(name))))

.PHONY: clean
clean:
	-del $(addprefix obj/, $(addsuffix .o, $(FILE_SRC)))
