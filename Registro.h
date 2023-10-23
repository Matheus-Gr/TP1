//
// Created by mathe on 5/9/2023.
//

#ifndef TP1_REGISTRO_H
#define TP1_REGISTRO_H

typedef struct {
    int chave;
    long int dado1;
    char dado2[5000];
} Registro;

void criarArquivoBinario(int quantidade, char* caminho, int ordem);
void lerArquivoBinario(char* caminho);

#endif //TP1_REGISTRO_H
