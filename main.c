#include <stdio.h>
#include <stdlib.h>
#include "Estatistica.h"
#include "Registro.h"
#include <string.h>
#include "ArvoreBinaria.h"

int main(int argc, char *argv[]) {
    int metodo, quantidade, ordem, chave, mostrar_pesquisa = 0;
    if (argc < 5 || argc > 6) {
        printf("Uso: pesquisa <metodo> <quantidade> <ordem> <chave> [-P]\n");
        return 1;
    }
    metodo = atoi(argv[1]);
    quantidade = atoi(argv[2]);
    ordem = atoi(argv[3]);
    chave = atoi(argv[4]);
    if (argc == 6 && strcmp(argv[5], "-P") == 0) {
        mostrar_pesquisa = 1;
    }

    //Criação da chave que ser buscada
    Registro* reg = malloc(sizeof(Registro));
    reg->chave = chave;

    //Criação de estatistica
    Estatistica* est = malloc(sizeof(Estatistica));

    //Criação do arquivo que sera lido
    criarArquivoBinario(quantidade, "dados.bin", ordem);
    if(mostrar_pesquisa){
        lerArquivoBinario("dados.bin");
    }

    //abrindo arquivo a ser manipulado
    FILE* arquivo = fopen("dados.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    switch (metodo) {
        case 1:
            //Acesso sequencial indexado
            break;
        case 2:
            criarArvoreBinaria(arquivo,quantidade);
            FILE * arvore_binaria = fopen("arvorebin.bin", "rb");
            if (arvore_binaria == NULL) {
                printf("Erro ao abrir arvore binaria!\n");
                exit(1);
            }

            zerarEstatistica(est);
            *reg = buscaArvoreBinaria(arvore_binaria, chave,est);
            finalizarEstatistica(est);
            printf("Registro %d\n"
                   "    Dado 1:%ld\n"
                   "    Dado 2:%s\n",
                   reg->chave, reg->dado1, reg->dado2);
            break;
        case 3:
            //Arvore B
            break;
        case 4:
            //Arvore B*
            break;
        default:
            printf("Metodo invalido. Use um numero de 1 a 4.\n");
        return 1;
    }

   printf("Estatisticas\n"
          "    Numero de transferencias: %d\n"
          "    Numero de comparacoes: %d\n"
          "    Tempo: %fs\n",
          est->transferencias, est->comparacoes,
          calcularTempo(est));

    return 0;
}
