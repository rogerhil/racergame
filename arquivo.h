#ifndef arquivo_h
#define arquivo_h

#include "estruturas.h"

#define LER                  "r"
#define ESCREVER             "w"
#define ANEXAR               "a"

void abrir_arquivo(FILE**, char*, char*);
void fechar_arquivo(FILE**);
void salvar_fase(MAPA);

#endif
