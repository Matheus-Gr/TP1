#ifndef ARVOREBESTRELA
#define ARVOREBESTRELA
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Estatistica.h"
#include <time.h>


#define MMEst 2
#define MM2Est 2*MMEst

typedef int TipoChaveBS;

typedef struct TipoRegistroBE{
    TipoChaveBS chave;
    long dado1;
    char dado2[5000]; 
} TipoRegistroBE;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPaginaBE* TipoApontadorBE;

typedef struct TipoPaginaBE {
    TipoIntExt Pt;
    union {
        struct {
            int ni;
            TipoRegistroBE ri[MM2Est];
            TipoApontadorBE pi[MM2Est + 1]; 
        }U0;
        struct {
            int ne;
            TipoRegistroBE re[MM2Est];
            TipoApontadorBE prox;
        }U1;
    }UU;
} TipoPaginaBE;

int pesquisaBEstrela(TipoRegistroBE *x, TipoApontadorBE *Ap, Estatistica *est,int *Condicao);
void arvBE_main(int chave, FILE *arq, int qtd_limite, Estatistica *analise);
void InicializaBE(TipoApontadorBE *arvore);
void bstar_Insere(TipoRegistroBE reg, TipoApontadorBE *Ap, Estatistica *est);
void bstar_Ins(TipoRegistroBE reg, TipoApontadorBE Ap, short *Cresceu, TipoRegistroBE* RegRetorno, TipoApontadorBE *ApRetorno, Estatistica *est);
void InsereNaPagina(TipoApontadorBE *Ap, TipoRegistroBE Reg, Estatistica *est);
void InserenaFolha(TipoRegistroBE reg, TipoApontadorBE Ap, Estatistica *est);
void imprimeExterna(TipoApontadorBE arv);

#endif