//
// Created by mathe on 5/9/2023.
//

#include "Estatistica.h"

/**
 * Zera os valores das estatísticas.
 *
 * @param estatistica Ponteiro para a estrutura de estatísticas.
 */
void zerarEstatistica(Estatistica* estatistica) {
    estatistica->transferencias = 0;
    estatistica->comparacoes = 0;
    estatistica->tempoInicio = clock();
}

/**
 * Finaliza a contagem do tempo de execução.
 *
 * @param estatistica Ponteiro para a estrutura de estatísticas.
 */
void finalizarEstatistica(Estatistica* estatistica) {
    estatistica->tempoFim = clock();
}

/**
 * Incrementa o contador de transferências.
 *
 * @param estatistica Ponteiro para a estrutura de estatísticas.
 */
void incTransf(Estatistica* estatistica) {
    estatistica->transferencias++;
}

/**
 * Incrementa o contador de comparações.
 *
 * @param estatistica Ponteiro para a estrutura de estatísticas.
 */
void incComp(Estatistica* estatistica){
    estatistica->comparacoes++;
}

/**
 * Calcula o tempo de execução em segundos.
 *
 * @param estatistica Ponteiro para a estrutura de estatísticas.
 * @return O tempo de execução em segundos.
 */
double calcularTempo(Estatistica* estatistica) {
    return (double)(estatistica->tempoFim - estatistica->tempoInicio) / CLOCKS_PER_SEC;
}
