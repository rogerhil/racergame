#include "funcoes.h"

volatile long int fps = 0;

void inicializar_allegro(int criar_cen)
{
    allegro_init();
    install_keyboard();	
    install_timer();	
    install_mouse();	
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 520, 0, 0);	
    
    LOCK_VARIABLE(fps);	LOCK_FUNCTION(cont_fps);	
     
    install_int_ex(cont_fps, BPS_TO_TIMER(60));	
}

void cont_fps(){
    fps++;
    
}END_OF_FUNCTION(cont_fps);

void desenha_sprite(BITMAP *buffer2, BITMAP *dest, BITMAP *orig, int angulo)
{    
    //clear(dest);
    //get-pixmap();
    draw_sprite(dest, buffer2, -10, -10);
    rotate_sprite(dest, orig, 0, 0, itofix(angulo));
}

CONSTR_MENU define_menu(CONSTR_MENU menu)
{
    menu.objs[0] = 0;    //estrada
    menu.objs[1] = 50;   //mato
    
    menu.objs[2] = 11;   //lateral_sup
    menu.objs[3] = 12;   //lateral_dir
    menu.objs[4] = 13;   //lateral_inf
    menu.objs[5] = 14;   //lateral_esq
   
    menu.objs[6] = 21;   //curva_sup_dir
    menu.objs[7] = 22;   //curva_inf_dir
    menu.objs[8] = 23;   //curva_inf_esq
    menu.objs[9] = 24;   //curva_sup_esq
    
    menu.objs[10] = 31;  //curva_sup_dir_interna
    menu.objs[11] = 32;  //curva_inf_dir_interna
    menu.objs[12] = 33;  //curva_inf_esq_interna
    menu.objs[13] = 34;  //curva_sup_esq_interna
    
    menu.objs[14] = -2;  //save
    
    return menu;
}

BITMAP *desenha_constr_menu(BITMAP *buffer, CONSTR_MENU menu)
{

    BITMAP *spr_img;
    BITMAP *bmp;
    BITMAP *menu_buffer = create_bitmap(640, 40); 
    char *arquivo_img;
    arquivo_img = malloc (100);
    arquivo_img = strdup ("imagens/estrada.bmp");
    
    int i, j;
    
    for (i = 0; i < 15; i++)
    {
        arquivo_img = retorna_nome_arq_imagem(menu.objs[i]);
        spr_img = load_bitmap(arquivo_img, NULL);
        bmp = create_bitmap(spr_img->w, spr_img->h);
        desenha_sprite(bmp, bmp, spr_img, 0);
        draw_sprite(menu_buffer, bmp, i*30, 10);
    }
    
    return (menu_buffer);
    
}


char *retorna_nome_arq_imagem (int v)
{

    char *arquivo_img;
    arquivo_img = malloc (100);
    arquivo_img = strdup ("imagens/estrada.bmp");

    switch (v)
    {
        case 0:
        {
            arquivo_img = strdup("imagens/estrada.bmp");
            break;
        }
        case 50:
        {
            arquivo_img = strdup("imagens/mato.bmp");
            break;
        }
        case 11:
        {
            arquivo_img = strdup("imagens/lateral_sup.bmp");
            break;
        }
        case 12:
        {
            arquivo_img = strdup("imagens/lateral_dir.bmp");
            break;
        }
        case 13:
        {
            arquivo_img = strdup("imagens/lateral_inf.bmp");
            break;
        }
        case 14:
        {
            arquivo_img = strdup("imagens/lateral_esq.bmp");
            break;
        }

        case 21:
        {
            arquivo_img = strdup("imagens/curva_sup_dir.bmp");
            break;
        }
        case 22:
        {
            arquivo_img = strdup("imagens/curva_inf_dir.bmp");
            break;
        }
        case 23:
        {
            arquivo_img = strdup("imagens/curva_inf_esq.bmp");
            break;
        }
        case 24:
        {
            arquivo_img = strdup("imagens/curva_sup_esq.bmp");
            break;
        }
        
        case 31:
        {
            arquivo_img = strdup("imagens/curva_sup_dir_interna.bmp");
            break;
        }
        case 32:
        {
            arquivo_img = strdup("imagens/curva_inf_dir_interna.bmp");
            break;
        }
        case 33:
        {
            arquivo_img = strdup("imagens/curva_inf_esq_interna.bmp");
            break;
        }
        case 34:
        {
            arquivo_img = strdup("imagens/curva_sup_esq_interna.bmp");
            break;
        }

        case -2:
        {
            arquivo_img = strdup("imagens/save.bmp");
            break;
        }
                
        default:
        {
            arquivo_img = strdup("imagens/estrada.bmp");
        }
    }

    return(arquivo_img);
}

BITMAP *desenha_mapa(MAPA mapa, BITMAP *buffer)
{
    int i, j, x, y;
    BITMAP *spr_img;
    BITMAP *bmp;
    BITMAP *mapa_buffer = create_bitmap(640, 480); 
    char *arquivo_img;
    arquivo_img = malloc (100);
    arquivo_img = strdup ("imagens/estrada.bmp");
   
    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 32; j++)
        {
            arquivo_img = retorna_nome_arq_imagem(mapa.matriz[i][j]);
            spr_img = load_bitmap(arquivo_img, NULL); 
            bmp = create_bitmap(spr_img->w, spr_img->h);
            desenha_sprite(bmp, bmp, spr_img, 0);
            draw_sprite(mapa_buffer, bmp, j*20, i*20);
        }
    }
    return (mapa_buffer);
}

MAPA zerar_matriz_mapa(MAPA mapa)
{
    int i,j;
    
    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 32; j++)
        {
            mapa.matriz[i][j] = 0;
        }
    }
    return mapa;
}

MAPA define_mapa()
{

    MAPA mapa;
    FILE *arquivo;
    int i,j, k, m = -1;
    
    char *ent, *nomearq;
    ent = malloc (10);
    nomearq = malloc (50);
    nomearq = strdup("fases/fase1.cen");
    
    abrir_arquivo(&arquivo, nomearq, LER);
    
    zerar_matriz_mapa(mapa);
    
    ent = strdup("");


    
    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 32; j++)
        {
            for (k = 0; k < 3; k++)
            {
                m++;
                fscanf(arquivo, "%c", &ent[k]);
                if (ent[k] == ',')
                {
                    ent[k] = ' ';
                    mapa.matriz[i][j] = atoi(ent);
                    ent = strdup("");
                    break;
                }

            }
        }
        
    }
    
    return mapa;
}

int deseja_salvar()
{
    BITMAP *buf_tras = create_bitmap(400, 30);
    int bool = 1;
    
    blit(screen, buf_tras, 120, 220, 0, 0, 400, 30);
    textprintf(screen, font, 120, 220, makecol(255,255,255), "Tem certeza que deseja salvar e começar o jogo?");
    textprintf(screen, font, 200, 240, makecol(255,255,255), "<SIM>");
    textprintf(screen, font, 360, 240, makecol(255,255,255), "<NAO>");
    //draw_sprite(screen, buf_perg, 120, 220);
    
    while(!key[KEY_ESC])
    {
        if (mouse_y > 235 && mouse_y < 255)
        {
            if (mouse_x > 200 && mouse_x < 230  && mouse_b == 1)
            {
                bool = 1;
                draw_sprite(screen, buf_tras, 120, 220);
                break;
            }

            if (mouse_x > 360 && mouse_x < 390 && mouse_b == 1)
            {
                bool = 0;
                draw_sprite(screen, buf_tras, 120, 220);
                break;
            }            
        }
    }
    
    return bool;    
}

MAPA define_mapa_padrao() 
{    
    MAPA mapa;
    int i,j;
    zerar_matriz_mapa(mapa);
    
    for (i = 0; i < 24; i++)
    {
        mapa.matriz[i][0] = 50;

    }

    for (i = 0; i < 24; i++)
    {
        mapa.matriz[i][31] = 50;
    }

    for (j = 0; j < 32; j++)
    {
        mapa.matriz[0][j] = 50;
    }

    for (j = 0; j < 32; j++)
    {
        mapa.matriz[23][j] = 50;
    }

    
    
    for (i = 1; i < 23; i++)
    {
        mapa.matriz[i][1] = 14;
    }

    for (i = 1; i < 23; i++)
    {
        mapa.matriz[i][30] = 12;
    }

    for (j = 1; j < 31; j++)
    {
        mapa.matriz[1][j] = 11;
    }

    for (j = 1; j < 31; j++)
    {
        mapa.matriz[22][j] = 13;
    }

    

    for (i = 6; i < 18; i++)
    {
        mapa.matriz[i][6] = 12;
    }

    for (i = 6; i < 18; i++)
    {
        mapa.matriz[i][25] = 14;
    }

    for (j = 6; j < 26; j++)
    {
        mapa.matriz[6][j] = 13;
    }

    for (j = 6; j < 26; j++)
    {
        mapa.matriz[17][j] = 11;
    }
    
     

    for (i = 7; i < 17; i++)
    {
        for (j = 7; j < 25; j++)
        {
            mapa.matriz[i][j] = 50;
        }
    }
    
    
    mapa.matriz[1][1] = 24;
    mapa.matriz[1][30] = 21;
    mapa.matriz[22][1] = 23;
    mapa.matriz[22][30] = 22;

    mapa.matriz[6][6] = 34;
    mapa.matriz[6][25] = 31;
    mapa.matriz[17][6] = 33;
    mapa.matriz[17][25] = 32;
       
    return mapa;
}
