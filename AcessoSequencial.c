#include "AcessoSequencial.h"
#include "Registro.h"
#include "Estatistica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void pesquisa(FILE *arquivo, int *tabela, int tam, Registro *registroPesquisa, int tamanhoArquivo,Estatistica* est) {
  Registro pagina[TAMPAG];
  int i, quantidadeItems;
  long desloc;
  
 calcularTempo(est);
  i = 0;

  //Procura a página do item desejado
  while (i < tam && tabela[i] <= registroPesquisa->chave) {
    i++;
    incComp(est);
  }
  incComp(est);

  if(i == 0) return ;

  //Verifica a quantidade de itens na página
  if(i < tam) quantidadeItems = TAMPAG;
  else {
    quantidadeItems = tamanhoArquivo % TAMPAG;
    if(quantidadeItems == 0) quantidadeItems = TAMPAG;
  }

  //Carregando a página para a memória principal
  desloc = (i - 1) * TAMPAG * sizeof(Registro);
  fseek(arquivo, desloc, SEEK_SET);
  fread(&pagina, sizeof(Registro), quantidadeItems, arquivo);
  incTransf(est);

  //Varredura na página para encontrar o item
  for(i = 0; i < quantidadeItems; i++) {
    incComp(est);
    if(pagina[i].chave == registroPesquisa->chave) {
      *registroPesquisa = pagina[i];   
      break;
    }
  }

  return ;
}

void acessoSequencialIndexado(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa,Estatistica* est) {
  //zerarEstatistica(&est);
  incTransf(est);
  int tamanhoTabela = tamanhoArquivo / TAMPAG;
  if(tamanhoTabela < ((double) tamanhoArquivo / (double) TAMPAG)) {
    tamanhoTabela++;
  }

  int *tabela = malloc(sizeof(int) * (tamanhoTabela));

  int posicao = 0;
  Registro registro;

  //Leitura e armazenamento do menor item da página
  while (posicao < tamanhoTabela) {
    fread(&registro, sizeof(registro), 1, arquivo);
    incTransf(est);

    fseek(arquivo, (sizeof(registro) * (TAMPAG - 1)), SEEK_CUR);

    tabela[posicao] = registro.chave;
    posicao++;
    
  }
  fflush(stdout);

  pesquisa(arquivo, tabela, tamanhoTabela, registroPesquisa, tamanhoArquivo, est);
  
  free(tabela);
  return ;
}