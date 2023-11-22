#ifndef ACESSOSEQUENCIAL_H
#define ACESSOSEQUENCIAL_H
#define TAMPAG 4

#include "Registro.h"
#include "Estatistica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pesquisa(FILE *, int *, int , Registro *, int , Estatistica*);
void acessoSequencialIndexado(FILE *, int , Registro *, Estatistica*);

#endif