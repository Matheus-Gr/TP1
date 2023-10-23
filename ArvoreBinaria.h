//
// Created by mathe on 5/30/2023.
//

#ifndef TP1_ARVOREBINARIA_H
#define TP1_ARVOREBINARIA_H

#include "Registro.h"
#include <stdlib.h>
#include <stdio.h>
#include "Estatistica.h"

typedef struct {
    int esquerda;
    int direita;
    Registro registro;
    int posicao;
} NodeBinario;

void criarArvoreBinaria(FILE *arquivo, int quantidade);
Registro buscaArvoreBinaria(FILE *arvore_binaria, int chave, Estatistica* est);

#endif //TP1_ARVOREBINARIA_H
