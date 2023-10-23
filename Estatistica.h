//
// Created by mathe on 5/9/2023.
//

#ifndef TP1_ESTATISTICA_H
#define TP1_ESTATISTICA_H

#include <time.h>

typedef struct {
    int transferencias;
    int comparacoes;
    clock_t tempoInicio;
    clock_t tempoFim;
} Estatistica;

void zerarEstatistica(Estatistica* estatistica);
void finalizarEstatistica(Estatistica* estatistica);
void incTransf(Estatistica* estatistica);
void incComp(Estatistica* estatistica);
double calcularTempo(Estatistica* estatistica);

#endif //TP1_ESTATISTICA_H
