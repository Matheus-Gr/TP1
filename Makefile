# Makefile para compilar o programa tp1.exe

# Compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -std=c99

# Arquivos fonte
SRCS = Estatistica.c main.c ArvoreBinaria.c Registro.c AcessoSequencial.c ArvoreB.c ArvoreBEstrela.c

# Nome do executável
TARGET = tp1.exe

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	del /Q $(OBJS) dados.bin $(TARGET)
