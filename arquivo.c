#include "arquivo.h"

void abrir_arquivo(FILE **arquivo, char *caminho, char *modo){
	if ((*arquivo = fopen(caminho,modo)) == 0) {
		printf("Arquivo não pôde ser aberto.\n\n\n");
		exit(0);
	}
}

void fechar_arquivo(FILE **arquivo){
	if(fclose(*arquivo)==0){
		printf("Arquivo nao pode ser fechado.\n\n\n");
		exit(0);
	}
}

void salvar_fase(MAPA tcmapa)
{
    FILE *save_arquivo;
    int i,j;
    save_arquivo = fopen("fases/fase1.cen", "w" );
    
    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 32; j++)
        {
            fprintf(save_arquivo, "%d,", tcmapa.matriz[i][j]);
        }
    }
    fclose(save_arquivo);
}
