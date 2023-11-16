#ifndef ARVOREB_H
#define ARVOREB_H


#include <stddef.h>
#include <stdio.h>
#include "Registro.h"
#include "Estatistica.h"

#define M 10
#define MM 20
#define FALSE 0
#define TRUE 1


typedef struct TipoPagina * TipoApontador;

typedef struct TipoPagina {
    short n;
    Registro r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;

void arvoreB(FILE *arq, int chave, Estatistica* est);
void inicializaArvoreB(TipoApontador *Arvore);
int pesquisaArvoreB(Registro *x, TipoApontador Ap, Estatistica *est);
void insArvoreB(Registro Reg, TipoApontador Ap, short *Cresceu, Registro *RegRetorno, TipoApontador *ApRetorno, Estatistica *est);
void insereNaPaginaArvoreB(TipoApontador Ap, Registro Reg, TipoApontador ApDir, Estatistica *est);
void insereArvoreB(Registro Reg, TipoApontador *Ap, Estatistica *est);

#endif