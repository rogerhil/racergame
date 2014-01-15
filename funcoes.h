#ifndef funcoes_h
#define funcoes_h

#include "estruturas.h"
#include "arquivo.h"

void inicializar_allegro(int);
void cont_fps();
void desenha_sprite(BITMAP*, BITMAP*, BITMAP*, int);
BITMAP *desenha_mapa(MAPA, BITMAP*);
BITMAP *desenha_constr_menu(BITMAP*, CONSTR_MENU);
char *retorna_nome_arq_imagem (int);
MAPA zerar_matriz_mapa(MAPA);
MAPA define_mapa_padrao();
MAPA define_mapa();
int deseja_salvar();
CONSTR_MENU define_menu(CONSTR_MENU);

#endif
