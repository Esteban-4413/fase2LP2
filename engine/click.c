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

int verifica_click (POINTERS *janelas) {
    MEVENT event;
    if (getmouse(&event) == OK) {
        return eclickValido(event.x, event.y, janelas);
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