#include "arvoreB.h"
#include "Registro.h"
#include "Estatistica.h"
#include "stdlib.h"

/**
 * Inicializa uma árvore B vazia.
 *
 * @param Arvore Ponteiro para a raiz da árvore B.
 */
void inicializaArvoreB (TipoApontador *Arvore)
{
    *Arvore = NULL;
}

/**
 * Constrói uma árvore B a partir de um arquivo e realiza uma busca por uma chave específica.
 *
 * @param arq   Ponteiro para o arquivo de onde serão lidos os registros.
 * @param chave A chave a ser buscada.
 * @param est   Ponteiro para o objeto de estatísticas para rastrear comparações e transferências.
 */
void arvoreB(FILE *arq, int chave, Estatistica *est)
{
    TipoApontador Ap;
    Registro item;
    
    zerarEstatistica(est);
    Ap= (TipoApontador)malloc(sizeof(TipoPagina));
    inicializaArvoreB(&Ap);
    while (fread(&item, sizeof(Registro), 1, arq) == 1)
    {
        incTransf(est);
        insereArvoreB(item, &Ap, est);
    }
    item.chave=chave;
    finalizarEstatistica(est);
    printf("Estatisticas\n"
           "    Numero de transferencias: %d\n"
           "    Numero de comparacoes: %d\n"
           "    Tempo: %lfs\n",
           est->transferencias, est->comparacoes,
           calcularTempo(est));

    zerarEstatistica(est);
    pesquisaArvoreB(&item ,Ap, est);
}

/**
 * Realiza uma pesquisa por um registro com uma chave específica em uma árvore B.
 *
 * @param x   Ponteiro para o registro a ser buscado.
 * @param Ap  Ponteiro para o nó atual sendo pesquisado.
 * @param est Ponteiro para o objeto de estatísticas para rastrear comparações e transferências.
 * @return    1 se a chave foi encontrada, 0 caso contrário.
 */
int pesquisaArvoreB(Registro *x, TipoApontador Ap, Estatistica *est)
{
    long i = 1;
    
    if (Ap == NULL)
    {
        printf("Registro nao esta presente na arvore\n");
        return 0;
    }
    while (i < Ap->n && x->chave > Ap->r[i-1].chave)
    { 
        incComp(est);
        i++;
    }

    if (x->chave == Ap->r[i-1].chave)
    { 
        incComp(est);
        *x = Ap->r[i-1];
        printf("Chave encontrada!\n");
        printf("Chave: %d\n", x->chave);
        printf("   Dado1: %.2ld\n", x->dado1);
        printf("   Dado2: %s\n", x->dado2);
        return 1;
    }
    if (x->chave < Ap->r[i-1].chave)
    {
        incComp(est);
        pesquisaArvoreB(x, Ap->p[i - 1], est);
    }
    else
    {
        incComp(est);
        pesquisaArvoreB(x, Ap->p[i], est);
    }
return 0;
}

/**
 * Insere um registro em uma página da árvore B.
 *
 * @param Ap     Ponteiro para a página onde o registro será inserido.
 * @param Reg    O registro a ser inserido.
 * @param ApDir  Ponteiro para a página à direita do registro inserido.
 * @param est    Ponteiro para o objeto de estatísticas para rastrear comparações e transferências.
 */
void insereNaPaginaArvoreB(TipoApontador Ap, Registro Reg, TipoApontador ApDir, Estatistica *est)
{
    int k;
    int NaoAchouPosicao;

    k = Ap->n;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao)
    {
        if (Reg.chave >= Ap->r[k - 1].chave)
        {
            incComp(est);
            NaoAchouPosicao = 0;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1)
            NaoAchouPosicao = 0;
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

/**
 * Insere um registro em uma árvore B.
 *
 * @param Reg         O registro a ser inserido.
 * @param Ap          Ponteiro para o nó atual sendo percorrido.
 * @param Cresceu     Ponteiro para indicar se a árvore cresceu em altura.
 * @param RegRetorno  Ponteiro para o registro a ser retornado após a inserção.
 * @param ApRetorno   Ponteiro para o nó a ser retornado após a inserção.
 * @param est         Ponteiro para o objeto de estatísticas para rastrear comparações e transferências.
 */
void insArvoreB(Registro Reg, TipoApontador Ap, short *Cresceu, Registro *RegRetorno, TipoApontador *ApRetorno, Estatistica *est)
{
    TipoApontador ApTemp;
    long i=1, j;
    
    if (Ap == NULL)
    {
        incComp(est);
        *Cresceu = 1;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;

        return;
    }

    while (i < Ap->n && Reg.chave > Ap->r[i - 1].chave)
        i++;

    if (Reg.chave == Ap->r[i - 1].chave)
    {   
        incComp(est);
        //printf("O registro ja esta presente.\n");
        *Cresceu = 0;
        return;
    }

    if (Reg.chave < Ap->r[i - 1].chave)
    {
        incComp(est);
        i--;
    }
    insArvoreB(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno, est);
    if (!*Cresceu)
        return;
    if (Ap->n < MM)
    {
        incComp(est);
        //Pagina tem espaco 
        insereNaPaginaArvoreB(Ap, *RegRetorno, *ApRetorno, est);
        *Cresceu = 0;
        return;
    }
    // Overflow: Pagina tem que ser dividida 
    ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    if (i <= M + 1)
    {
        insereNaPaginaArvoreB(ApTemp, Ap->r[MM - 1], Ap->p[MM], est);
        Ap->n--;
        insereNaPaginaArvoreB(Ap, *RegRetorno, *ApRetorno, est);
    }
    else
        insereNaPaginaArvoreB(ApTemp, *RegRetorno, *ApRetorno, est);
    for (j = M + 2; j <= MM; j++)
        insereNaPaginaArvoreB(ApTemp, Ap->r[j - 1], Ap->p[j], est);
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

/**
 * Insere um registro em uma árvore B.
 *
 * @param Reg   O registro a ser inserido.
 * @param Ap    Ponteiro para o nó atual sendo percorrido.
 * @param est   Ponteiro para o objeto de estatísticas para rastrear comparações e transferências.
 */
void insereArvoreB(Registro Reg, TipoApontador *Ap, Estatistica *est)
{
    short Cresceu;
    Registro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    insArvoreB(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, est);

    if (Cresceu)   // Arvore cresce na altura pela raiz 
    {
        incComp(est);
        ApTemp=(TipoPagina*)malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = (*Ap);
        *Ap = ApTemp;
    }
 }
