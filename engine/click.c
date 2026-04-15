/**
 * @file click.c
 * @author Esteban Yepez (a116272), Fernanda Cidrim (a116274), Martim Sousa (a113572)
 * @brief Ficheiro onde estão definidas todas as funções relacionadas com o reconhecimento do click no ecrã.
 * @version 0.1
 * @date 2026-03-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <stdio.h>
#include <ncurses.h>
#include "click.h"
#include "prints.h"

int verifica_click (JOGO *game, POINTERS *janelas, int *num_carta) {
    MEVENT event;
    if (getmouse(&event) == OK) {
        int r = eclickValido(event.x, event.y, janelas);
        if(r >= 0 && r < 11) *num_carta = coords_para_carta(event.y, r, game);
        return r;
    }
    return -1;
}


int eclickValido(int x, int y, POINTERS *janelas) {
    if (eJanela(janelas->end_hint, x, y)) return 11;
    else if (eJanela(janelas->end_undo, x, y)) return (12);
    else if (eJanela(janelas->end_ngame, x, y)) return (13);
    else return eclicknaPilha(x, y, janelas->end_pilhas); 
        // Verifica as pilhas 
        /* 
        Vai passar a dar de 0 a 10 correpondendo ao número da pilha 
        */

    return -1;

}



int eclicknaPilha(int x, int y, WINDOW *janela_pilha[]){
    for (int i = 0; i < 10; i++) {
        if (eJanela(janela_pilha[i], x, y)) {
            return i; 
            }
        }
    return -1;
}


int eJanela(WINDOW *win, int x, int y) {
    int xmin, xmax, ymin, ymax;
    tamanhojanela(win, &xmin, &xmax, &ymin, &ymax);
    
    // x tem de estar ENTRE o min e o max
    if ((x >= xmin) && (x <= xmax) && (y >= ymin) && (y <= ymax)) return 1;
    return 0;
}


void tamanhojanela(WINDOW *win, int *xmin, int *xmax, int *ymin, int *ymax) {
    int altura, largura;

    // guarda no x e no y as coordenadas onde se encontra o ponto superior esquerdo da janela
    getbegyx(win, *ymin, *xmin); 

    //guarda no x e no y as dimensões da janela
    getmaxyx(win, altura, largura); 

    *ymax = *ymin + altura - 1; // -1 porque as coordenadas são inclusivas
    *xmax = *xmin + largura - 1; 
}

int coords_para_carta(int x, int pilha, JOGO *game){
    const int offset = 314;
    const int comprimento_cabeca_carta = 314;
    const int comprimento_carta = 314;

    if (x < offset) return -1; /*< Clique fora da pilha (em cima dela)*/
    
    int idx = (x - offset) / comprimento_cabeca_carta;
    
    if (idx >= game->tamanho_pilha[pilha] - 1){
        int cabeca_ultima_carta = offset + comprimento_cabeca_carta*(game->tamanho_pilha[pilha]-1);
        int pes_ultima_carta = cabeca_ultima_carta + comprimento_carta;
        if (x > pes_ultima_carta){
            return -1;
        }
    }
    return idx;
}