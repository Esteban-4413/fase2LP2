/**
 * @file prints.c
 * @author Esteban Yepez (a116272), Fernanda Cidrim (a116274), Martim Sousa (a113572)
 * @brief Implementação das funções que desenham a parte gráfica do jogo (ncurses).
 * @version 0.1
 * @date 2026-03-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <stdio.h>
#include <ncurses.h>			  
#include <string.h> // usamos o strcpy
#include <locale.h> // para suportar o UTF-8
#include "prints.h"
#include "actions.h"


//  ----- PRINCIPAIS PRINTS + DEFINIÇÃO DAS JANELAS/BOTÕES -----


void define_TodasJanelas (POINTERS *p, JOGO *game){ 
    
    // PILHAS 
    definePilhas(game->matriz, game->tamanho_pilha, p->end_pilhas);
    
    // BARALHO & DESCARTE
    p->end_baralho = defineBaralho(game->tamanho_baralho);
    p->end_foundations = defineFoundations; 
    
    // BOTÕES 
    p->end_undo = defineButtonUndo();
    p->end_hint = defineButtonHint();
    p->end_ngame = defineButtonNgame();
 
}


// -- BOTÕES --
WINDOW* defineButtonHint(){
        WINDOW *janela_hint;
        janela_hint = newwin(3, 10, 2, 10);
        box(janela_hint, 0, 0);
        wattron(janela_hint, COLOR_PAIR(3));
        mvwprintw(janela_hint, 1, 1, "  HINT");
        wrefresh(janela_hint);
        wattroff(janela_hint, COLOR_PAIR(3));

        return janela_hint;

}

WINDOW* defineButtonUndo(){ 
        WINDOW *janela_undo;
        janela_undo = newwin(3, 10, 2, 20);
        box(janela_undo, 0, 0);
        wattron(janela_undo, COLOR_PAIR(3));
        mvwprintw(janela_undo, 1, 1, "  UNDO");
        wrefresh(janela_undo);
        wattroff(janela_undo, COLOR_PAIR(3));

        return janela_undo; 

}

WINDOW* defineButtonNgame(){
        WINDOW *janela_ngame;
        janela_ngame = newwin(3, 10, 2, 30);
        box(janela_ngame, 0, 0);
        wattron(janela_ngame, COLOR_PAIR(3));
        mvwprintw(janela_ngame, 1, 1, "NEW GAME");
        wrefresh(janela_ngame);
        wattroff(janela_ngame, COLOR_PAIR(3));
        return janela_ngame;

}

// -- BARALHO  
void defineFoundations(WINDOW *janela_foundations[]){ 
        // Define a carta que vai ser mostrada 
        CARTAS c;
        c.naipe = '?';
        c.valor = 0;

        int x = 2;
        int y = 50; 

        // Cria as 4 janelas das foundations 
        for(int i = 0; i < 4; i++){
                janela_foundations[i] = newwin(10, 15, x, y);
                box(janela_foundations[i], 0, 0);
                mvwprintw(janela_baralho, 1, 1, "Baralho: %d", tamanho_baralho);
                x += 12;
                y += 18; 

                wrefresh(janela_foundations[i]); 

        }

}

// -- PILHAS -- 

void definePilhas(CARTAS matriz[10][25], int tamanho_pilha[10], WINDOW *janela_pilha[]) {
    int i;
    int y = 10;
    int x = 10;

    for(i = 0; i < 10; i++) {
        janela_pilha[i] = newwin(18, 15, y, x);
        print_nomePilha(janela_pilha, i); 
        

        int y_local = 3; 
        int x_local = 4;
        int ultCarta = tamanho_pilha[i] - 1; 
        desenha_pilha(janela_pilha,matriz, x_local, y_local, i, ultCarta); 
        x += 20;

        wrefresh(janela_pilha[i]);
    }
}

// AUXILIARES (definePilhas)

void print_nomePilha (WINDOW *janela_pilha[], int i){
        wattron(janela_pilha[i], COLOR_PAIR(3));
        mvwprintw(janela_pilha[i], 2, 2, "  PILHA %d  ", i+1);
        wattroff(janela_pilha[i], COLOR_PAIR(3));

}


void desenha_pilha (WINDOW *janela_pilha[],CARTAS matriz[7][5],  int x_local, int y_local, int i, int ultCarta){
        for(int j = 0; j <= ultCarta; j++) {
            if (j == ultCarta) wprint_cartaInt(janela_pilha[i], y_local, x_local, matriz[i][j]);
            else wprint_cartaTop(janela_pilha[i], y_local, x_local, matriz[i][j]);
            x_local += 2; // Ajusta conforme a lógica de empilhamento
        }
}


// --- PRINT CARTAS (window) --- 


void wprint_cartaInt(WINDOW *win, int x, int y, CARTAS c){ 
        const char *s = traduzsimbolo(c.naipe);

        // guarda o valor da carta 
        char valor[3]; 
        traduzvalor(valor, c.valor); // arrays ja sao pointers por natureza portanto fazer '&valor' da o ponteiro de outro ponteiro 


        // Ativa as cores específicas de cada carta
        if (c.naipe == 'C' || c.naipe == 'O')
        wattron(win, COLOR_PAIR(1));
        else
        wattron(win, COLOR_PAIR(2));

        // Faz o print da carta na janela
        print_carta(win, x, y, s, valor);
       

        refresh();

        // Desativa o atributo das cores
        wattroff(win, COLOR_PAIR(1));
        wattroff(win, COLOR_PAIR(2));



}


void wprint_cartaTop(WINDOW *win, int x, int y, CARTAS c){

        char valor[3]; // guarda o valor da carta 
        traduzvalor(valor, c.valor);

        // Ativa as cores específicas de cada carta
        if (c.naipe == 'C' || c.naipe == 'O')
        wattron(win, COLOR_PAIR(1));
        else
        wattron(win, COLOR_PAIR(2));


        mvwprintw(win, y,   x, "+ ----- +");
        mvwprintw(win, y+1, x, "| %-2s    |", valor);

        refresh();

        // Desativa o atributo das cores
        wattroff(win, COLOR_PAIR(1));
        wattroff(win, COLOR_PAIR(2));



}

// --- AUXILIARES (Prints cartas) --- 




const char* traduzsimbolo(char naipe) {
    switch(naipe) {

        case 'C': return "\xE2\x99\xA5"; // Copas (Retorna o endereco na memoria)
        case 'O': return "\xE2\x99\xA6"; // Ouros
        case 'P': return "\xE2\x99\xA3"; // Paus
        case 'E': return "\xE2\x99\xA0"; // Espadas
        default:  return "?";
        /*
        case 'C': return ""; // Retorna o endereço da string na memória
        case 'O': return "";
        case 'P': return "";
        case 'E': return "";
        default:  return "";
      */
    }
}


void traduzvalor(char *valor, char v){
        switch(v){
                case 1:  strcpy(valor, "A"); return;
                case 11: strcpy(valor, "J"); return;
                case 12: strcpy(valor, "Q"); return;
                case 13: strcpy(valor, "K"); return;
                case 0 : strcpy(valor, "?"); return;
                default:
                sprintf(valor, "%d", v); return;
        }
        
}

void print_carta(WINDOW *win, int x, int y, const char *s, char valor[3]){
        mvwprintw(win, y,   x, "+ ----- +");
        mvwprintw(win, y+1, x, "| %-2s    |", valor);
        mvwprintw(win, y+2, x, "|   %s   |", s);
        mvwprintw(win, y+3, x, "|     %2s|", valor);
        mvwprintw(win, y+4, x, "+ ----- +");
}
