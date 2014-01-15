#include "main.h"

CARRO carro;

int main(void){	

    double r = 0;
    double t = 0;
    double aceleracao = 2;
    double c_desac = 1;
    double natural_desac = .5;
    double v_max = 1.0;
    double torque = 1.5;
    int ang = 0, ttt = 0;
    
    MAPA mapa;
    MAPA tcmapa;
    
    int criar_cenario = 0;
    
    mapa = zerar_matriz_mapa(mapa);
    tcmapa = zerar_matriz_mapa(tcmapa);

    inicializar_allegro(criar_cenario);
     
    BITMAP *buffer = create_bitmap(71, 58);	
    BITMAP *buffer2 = create_bitmap(71, 58); 
    BITMAP *mapa_buffer = create_bitmap(640, 480); 
    BITMAP *menu_buffer = create_bitmap(640, 40); 
    CONSTR_MENU menu;
    menu = define_menu(menu);
    menu_buffer = desenha_constr_menu(menu_buffer, menu);

    
    BITMAP *intro_bmp = load_bitmap("imagens/intro_logo.bmp", NULL);  
    
    draw_sprite(screen, intro_bmp, 40, 150);
    textprintf(screen, font, 200, 300, makecol(255,255,255), "PRESSIONE ENTER PARA COMECAR");
    textprintf(screen, font, 190, 340, makecol(255,255,255), "PRESSIONE TAB PARA EDITAR FASE");
    
    while(!key[KEY_ENTER])
    {
        if (key[KEY_TAB]){
            criar_cenario = 1;
            break;
        }
    }
   
    
    if (criar_cenario)
    {
        mapa = zerar_matriz_mapa(mapa);
    }
    else
    {
        mapa = define_mapa();
    }
    //mapa = define_mapa_padrao();  

            
    BITMAP *spr_carro = load_bitmap("imagens/carro.bmp", NULL);	//inicia carro	
    
    BITMAP *spr_img;
    BITMAP *bmp;
   
    BITMAP *setinha = load_bitmap("imagens/setinha.bmp", NULL); 
    
    BITMAP *limp_setinhas = create_bitmap(640, 10);
    BITMAP *limp_menu = create_bitmap(640, 40);
    
    carro.x = 240;	
    carro.y = 40;	
     
    carro.largura = spr_carro->w;	
    carro.altura = spr_carro->h;	
    carro.angulo = 0;	
    carro.spr = create_bitmap(carro.largura, carro.altura);	

    mapa_buffer = desenha_mapa(mapa, buffer);
    
    draw_sprite(screen, mapa_buffer, 0, 0);
    draw_sprite(screen, menu_buffer, 0, 480);
    blit(screen, buffer2, carro.x, carro.y, 0, 0, 71, 58);
    draw_sprite(buffer, buffer2, 0, 0);
    
    int cmx, cmy, ma_x, ma_y, mmx, mmy, rmx, rmy, menux;
    int obj_selec = 0, i, j; 
    int smodx = 0;
    int smody = 0;
    char *arquivo_img;
    arquivo_img = malloc (100);
    arquivo_img = strdup ("imagens/estrada.bmp");
    
    char *img_cursor;
    img_cursor = malloc (100);
    img_cursor = strdup ("imagens/cursor.bmp");
    
    ma_x = mouse_x;
    ma_y = mouse_y;
    
    BITMAP *cursor_bmp = load_bitmap(img_cursor, NULL);  
    
    set_mouse_sprite(cursor_bmp);
    set_mouse_sprite_focus(0,0);
    show_mouse(screen);
       
    if (criar_cenario)
    {
        while(!key[KEY_ESC])
        {
            if (mouse_y > 0 && mouse_y < 480)
            {
                if (mouse_b)
                {
                    mmx = mouse_x / 20;
                    mmy = mouse_y / 20;
                    rmx = mouse_x % 20;
                    rmy = mouse_y % 20;
                    
                    tcmapa.matriz[mmy][mmx] = obj_selec;
                    arquivo_img = retorna_nome_arq_imagem (obj_selec);
                    spr_img = load_bitmap(arquivo_img, NULL);
                    bmp = create_bitmap(spr_img->w, spr_img->h);
                    draw_sprite(bmp, spr_img, 0, 0);
                    scare_mouse();
                    draw_sprite(screen, bmp, mouse_x - rmx, mouse_y - rmy);
                    unscare_mouse();
                    mouse_b = 0;
                }            

            }
            
            if (mouse_y > 490 && mouse_y < 510)
            {
                menux = mouse_x / 30;
                if (mouse_b)
                {
                    obj_selec = menu.objs[menux];
                    smodx = mouse_x % 30;
                    smody = 20 - (mouse_y % 20);
                    draw_sprite(screen, limp_setinhas, 0, 510);
                    draw_sprite(screen, setinha, mouse_x - smodx, mouse_y + smody +  10);
                    if (obj_selec == -2)
                    {
                        obj_selec = 0;
                        if (deseja_salvar())
                        {
                            salvar_fase(tcmapa);
                            mapa = define_mapa();
                            criar_cenario = 0;
                            break;
                        }
                    }
                    
                }
            }

            ma_x = mouse_x;
            ma_y = mouse_y;
        }
    }
    
    if (!criar_cenario)
    {
        draw_sprite(screen, limp_menu, 0, 480);
        while(!key[KEY_ESC]){
                   
            ttt++;
            
            if (ttt > 40)
            {
            
                if (key[KEY_RIGHT]){
                    carro.angulo+=torque;
                                
                }	
                if (key[KEY_LEFT]){
                    carro.angulo-=torque;		
                }
                
                
                blit(buffer2, screen, 0, 0, carro.x, carro.y, 640, 480);
                if (key[KEY_UP]){
                    ang = carro.angulo;
                    
                    t+=.05;
                }
                ang = carro.angulo;
                r = aceleracao*t*t;
                if (r > v_max)
                {
                    t -= .1;
                    r = v_max;
                }
                
                cmy = (int)(carro.y + 35 + (int)(r * sin((ang*(3.1416))/128)))/20;
                cmx = (int)(carro.x + 29 + (int)(r * cos((ang*(3.1416))/128)))/20;
                if (mapa.matriz[cmy][cmx] != 0)
                {
                    t -= .2;
                    r -= 4;
                }
                
                if (t < 0)
                {
                    t = 0;
                }
        
                if (key[KEY_DOWN])	{
                    ang = carro.angulo;
                    t-=c_desac;
                }
        
                t-= natural_desac;
                carro.x+= (int)(r * cos((ang*(3.1416))/128));
                carro.y+= (int)(r * sin((ang*(3.1416))/128));
                ttt = 0;
                blit(screen, buffer2, carro.x, carro.y, 0, 0, 71, 58);
                draw_sprite(buffer, buffer2, 0, 0);
                
            }
            desenha_sprite(buffer2, carro.spr, spr_carro, carro.angulo);		
            draw_sprite(buffer, carro.spr, 10, 10);
            
            blit(buffer, screen, 0, 0, carro.x, carro.y, 640, 480);
    
        }
    }
    return(0);
    
}END_OF_MAIN();
