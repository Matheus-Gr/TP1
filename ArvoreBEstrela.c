#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include "ArvoreBEstrela.h"
#include "Estatistica.h"

int pesquisaBEstrela(TipoRegistroBE *x, TipoApontadorBE *Ap, Estatistica *est, int *Condicao)
{
    int i = 1;
    TipoApontadorBE PageAtual;
    PageAtual = *Ap;

    if ((*Ap)->Pt == Interna)
    {
        while (i < PageAtual->UU.U0.ni && x->chave > PageAtual->UU.U0.ri[i - 1].chave)
        {
            i++;
            incComp(est);
        }

        if (x->chave <= PageAtual->UU.U0.ri[i - 1].chave)
        {
            incComp(est);
            pesquisaBEstrela(x, &PageAtual->UU.U0.pi[i - 1], est, Condicao);
        }
        else
        {
            incComp(est);
            pesquisaBEstrela(x, &PageAtual->UU.U0.pi[i], est, Condicao);
        }
         return  Condicao ? 1 : 0 ;
    }


        i = 1;

        while (i <= PageAtual->UU.U1.ne && x->chave > PageAtual->UU.U1.re[i - 1].chave)
        {
            incComp(est);
            // printf("Valor do i %d ", i);
            // printf("valor da chave %d\n", (*Ap)->UU.U1.re[i-1].chave);
            i++;
        }

        if (x->chave == PageAtual->UU.U1.re[i - 1].chave)
        {
            (*x) = PageAtual->UU.U1.re[i - 1];
            incComp(est);
            (*Condicao) = 1;
            return 1;
        }
        else
        {

            incComp(est);
            // printf("Não achou nada\n");
            (*Condicao) = 0;
            return 0;
        }
      
}

void arvBE_main(int chave, FILE *arq, int qtd_limite, Estatistica *est, double* tempocriacao){
    TipoApontadorBE arvore;
    TipoRegistroBE reg;
    TipoRegistroBE item;
    item.chave = chave;
    //Estatistica a;
    int Condicao = 0;
    


    zerarEstatistica(est);
    InicializaBE(&arvore);

    for (int i = 0; i < qtd_limite; i++)
    {
        fread(&reg, sizeof(TipoRegistroBE), 1, arq);
        InsereNaPagina(&arvore, reg, est);
        incTransf(est);
        
    }
    
  
    finalizarEstatistica(est);
    *tempocriacao = calcularTempo(est);
    
    zerarEstatistica(est);
    if(pesquisaBEstrela(&item, &arvore, est, &Condicao)){
        printf("Registro %d\n"
                    "    Dado 1:%ld\n"
                    "    Dado 2:%s\n",
                    item.chave, item.dado1, item.dado2);
            
    }else{
        printf("\nNao encontrado o item de chave %d\n", item.chave);
    }

    finalizarEstatistica(est);
}

void InicializaBE(TipoApontadorBE *arvore){
    (*arvore) = NULL;
}


void insereInterna(TipoApontadorBE Ap, TipoChaveBS Chave, TipoApontadorBE ApDir, Estatistica *est){
    int i;
    i = Ap->UU.U0.ni;
    int TemEspaco;
    TemEspaco = (i > 0);

    while(TemEspaco){
        if(Chave >= Ap->UU.U0.ri[i-1].chave){
            incComp(est);
            TemEspaco = 0;
            break;
        }

        Ap->UU.U0.ri[i].chave = Ap->UU.U0.ri[i-1].chave;
        Ap->UU.U0.pi[i+1] = Ap->UU.U0.pi[i];
        i--;
        if(i < 1) TemEspaco = 0;
    }

    //printf("CHAVE INSERIDA INTERNA  \n Chave: %d\n", Chave);

    Ap->UU.U0.ri[i].chave = Chave;
    Ap->UU.U0.pi[i+1] = ApDir;
    Ap->UU.U0.ni++;
}

void InserenaFolha(TipoRegistroBE reg, TipoApontadorBE Ap, Estatistica *est) {
    int i;
    i = Ap->UU.U1.ne;
    int TemEspaco;
    TemEspaco = (i > 0);

    while(TemEspaco){
        if(reg.chave >= Ap->UU.U1.re[i - 1].chave){
            incComp(est);
            TemEspaco = 0;
            break;
        }
        
        Ap->UU.U1.re[i] = Ap->UU.U1.re[i-1];
        i--;
        if(i < 1) TemEspaco = 0;
    }  

    //printf("VALORES INSERIDOS NA FOLHA \n Chave: %d\n Dado1: %ld\n Dado2: %s\n", reg->chave, reg->dado1, reg->dado2);

    Ap->UU.U1.re[i] = reg;
    Ap->UU.U1.ne++;
}

void bstar_Ins(TipoRegistroBE reg, TipoApontadorBE Ap, short *Cresceu, TipoRegistroBE *RegRetorno, TipoApontadorBE *ApRetorno, Estatistica *est) {
    long i = 1;
    long j;
    TipoApontadorBE ApTemp;
    //TipoApontadorBE new = NULL;
    //TipoRegistroBE Aux;

    if (Ap == NULL) {
        (*Cresceu) = 1;     
        (*RegRetorno) = reg;
        (*ApRetorno) = NULL;

        return;
    }
   
    if(Ap->Pt == Interna){

        while(i < Ap->UU.U0.ni && reg.chave > Ap->UU.U0.ri[i-1].chave){
            incComp(est);
            i++;
        }

        if(reg.chave < Ap->UU.U0.ri[i-1].chave){
            incComp(est);
            i--;
        }

        bstar_Ins(reg, Ap->UU.U0.pi[i], Cresceu, RegRetorno, ApRetorno, est);

       // printf("Resultado não cresceu %d\n", !(*Cresceu));
        if(!*Cresceu){
            return;
        }

        if(Ap->UU.U0.ni < MM2Est){
            incComp(est);
            //printf("Entrou aqui 3\n");
            insereInterna(Ap, RegRetorno->chave, *ApRetorno, est);
            (*Cresceu) = 0;
            return;
        }

        //Overflow: Pagina a ser dividida

        ApTemp = (TipoApontadorBE)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 0;
        ApTemp->UU.U0.pi[0] = NULL;

        if(i < MMEst+1){
            insereInterna(ApTemp, Ap->UU.U0.ri[MM2Est-1].chave, Ap->UU.U0.pi[MM2Est], est);
            Ap->UU.U0.ni--;
            insereInterna(Ap, RegRetorno->chave, *ApRetorno, est);
        }else {
            insereInterna(ApTemp, RegRetorno->chave, *ApRetorno, est);
        }

        for(j = MMEst + 2; j <= MMEst; j++){
            insereInterna(ApTemp, Ap->UU.U0.ri[j-1].chave, Ap->UU.U0.pi[j], est);
        }

        Ap->UU.U0.ni = MMEst;
        ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MMEst+1];
        (*RegRetorno).chave = Ap->UU.U0.ri[MMEst].chave;
        (*ApRetorno) = ApTemp;

        return;
    }
    else{
        (*RegRetorno)  = reg;

        while(i < Ap->UU.U1.ne && reg.chave > Ap->UU.U1.re[i-1].chave){ 
            incComp(est);
            i++;
        }

        if(reg.chave == Ap->UU.U1.re[i-1].chave && Ap->UU.U1.ne != 0){
            incComp(est);
            //printf("Erro: Registro ja esta presente\n");
            (*Cresceu) = 0;
            return;
        }

        if(!*Cresceu){
            return;
        }

        if(Ap->UU.U1.ne < MM2Est){
            incComp(est);
            InserenaFolha(*RegRetorno, Ap, est);
           (*Cresceu) = 0;
            return;
        }


        //criando nova página Overflow
        ApTemp = (TipoApontadorBE)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 0;
        
        //Se o registro for menor ficará na página que já existe
        //Se não irá ir para a nova página criada

        if(i < MMEst+1){
            InserenaFolha(Ap->UU.U1.re[MM2Est-1], ApTemp, est);
            Ap->UU.U1.ne--;
            InserenaFolha(*RegRetorno, Ap, est);
        }else {
            InserenaFolha(*RegRetorno, ApTemp, est);
        }


        for(j = MMEst+2; j <= MM2Est; j++){
            InserenaFolha(Ap->UU.U1.re[j-1], ApTemp, est);
        }

        Ap->UU.U1.ne = MMEst + 1;
        
        
        (*RegRetorno) = Ap->UU.U1.re[MMEst];
        (*ApRetorno) = ApTemp;
    }
}


void InsereNaPagina(TipoApontadorBE *Ap, TipoRegistroBE Reg, Estatistica *est) {
    TipoPaginaBE *ApTemp;
    TipoPaginaBE *apRetorno;
    short cresceu;
    cresceu = 1;
    TipoRegistroBE RegRetorno;

    if(*Ap == NULL){
        ApTemp = (TipoPaginaBE*)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 0;
        ApTemp->UU.U1.re[0] = Reg;
        *Ap = ApTemp;
    }

    bstar_Ins(Reg, *Ap, &cresceu, &RegRetorno, &apRetorno, est);

    if(cresceu){
        ApTemp = (TipoPaginaBE*)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 1;
        ApTemp->UU.U0.ri[0].chave = RegRetorno.chave;
        ApTemp->UU.U0.pi[1] = apRetorno;
        ApTemp->UU.U0.pi[0] = *Ap;
        *Ap = ApTemp;
    }
}

void imprimeExterna(TipoApontadorBE arv){
    while (arv->UU.U1.re->chave != 80)
    {
        if(arv->Pt != Externa){
            printf("Interno:\n");

            for(int i = 0; i < arv->UU.U1.ne; i++){
                printf("%d ", arv->UU.U0.ri[i].chave);
            }
            printf("--\n");

            for(int i = 0; i < arv->UU.U0.ni+1; i++){ 
                imprimeExterna(arv->UU.U0.pi[i]);
                
            }
            return;
        }
        else{
            printf("Externo:\n");

            for(int i = 0; i < arv->UU.U1.ne; i++){
                printf("%d ", arv->UU.U1.re[i].chave);
            }
            printf("\n");
            return;
        }
        /* code */
    }
    
}