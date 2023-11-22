//
// Created by mathe on 5/9/2023.
//

#include "Registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void criarArquivoBinario(int quantidade, char* caminho, int ordem) {
    Registro registro;

    printf("Nome do arquivo: %s\n", caminho);

    FILE *arquivo = fopen(caminho, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo binario!\n");
        exit(1);
    }

    // Definir a semente do gerador de números aleatórios
    srand(time(NULL));

    if (ordem == 1) {
        // Ordenação ascendente
        for (int i = 0; i < quantidade; i++) {
            registro.chave = i;
            registro.dado1 = i * 100;
            sprintf(registro.dado2, "Dado 2 do registro %d", i);
            fwrite(&registro, sizeof(Registro), 1, arquivo);
        }
    } else if (ordem == 2) {
        // Ordenação descendente
        for (int i = quantidade - 1; i >= 0; i--) {
            registro.chave = i;
            registro.dado1 = i * 100;
            sprintf(registro.dado2, "Dado 2 do registro %d", i);
            
            fwrite(&registro, sizeof(Registro), 1, arquivo);
        }
    } else if (ordem == 3) {
        // Embaralhamento aleatório
        int* chaves = malloc(quantidade * sizeof(int));
        for (int i = 0; i < quantidade; i++) {
            chaves[i] = i;
        }
        for (int i = quantidade - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = chaves[i];
            chaves[i] = chaves[j];
            chaves[j] = temp;
        }
        for (int i = 0; i < quantidade; i++) {
            registro.chave = chaves[i];
            registro.dado1 = chaves[i] * 100;
            sprintf(registro.dado2, "Dado 2 do registro %d", chaves[i]);
            fwrite(&registro, sizeof(Registro), 1, arquivo);
        }
        free(chaves);
    } else {
        printf("Opção inválida para ordem de criação do arquivo!\n");
        exit(1);
    }

    fclose(arquivo);
}

void lerArquivoBinario(char* caminho) {
    Registro registro;
    FILE *arquivo = fopen(caminho, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo binário!\n");
        exit(1);
    }
    while (fread(&registro, sizeof(Registro), 1, arquivo)) {
        printf("Chave: %d, Dado 1: %ld, Dado 2: %s\n",
               registro.chave, registro.dado1, registro.dado2);
    }
    fclose(arquivo);
}