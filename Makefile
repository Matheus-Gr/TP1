CC = gcc
CFLAGS = -Wall -std=c99

SRC = Estatistica.c main.c ArvoreBinaria.c Registro.c ArvoreB.c
OBJ = $(SRC:.c=.o)

tp1.exe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f tp1.exe $(OBJ)
