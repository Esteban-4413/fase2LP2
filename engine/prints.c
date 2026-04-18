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

// ----- ATUALIZA Foundations -----
/*
Foundations vão ser, nesta ordem:
 0 - Copas  
 1 - Espadas  
 2 - Ouros  
 3 - Paus
*/
void atualizaFoundations(JOGO *game, POINTERS *p){
        CARTAS c; 
        for(int i = 0 ; i < 4; i++){
                defineCarta(&c, i);
                if (game->foundations[i]) atualizaF(p->end_foundations, c, i);
        }
} 

void  defineCarta(CARTAS *c, int i){
        c->valor = 1;
        if(i == 0) c->naipe = 'C';
        else if (i == 1) c->naipe = 'E';
        else if (i == 2) c->naipe = 'O';
        else if (i == 3) c->naipe = 'P';

}

void atualizaF(WINDOW *janela_foundations[], CARTAS c, int i){
        werase(janela_foundations[i]);
        mvwprintw(janela_foundations[i], 1, 1, "Foundation %d", i+1);
        wprint_cartaInt(1, janela_foundations[i], 3,3, c);
        wrefresh(janela_foundations[i]);
}


// ----- ATUALIZA PILHAS DO HINT  -----

void redesenha_pilhasHint(int f, JOGO *game, POINTERS *p){
       if (f == (-1)) {
                for (int i = 0; i < 10; i++){
                        if (game->hint.p_flags[i] == 1) alteraCor_pilha(i, game->tamanho_pilha[i], p->end_pilhas, game);
                }
               
       }
       else if (f == 1){
             reset_pilhaHint(game, p);   
       }
       
       
        
}

void reset_pilhaHint(JOGO *game, POINTERS *p){
        for (int i = 0; i <10; i++){
                     int x_local = 4;
                     int y_local = 3;
                     int ultCarta = game->tamanho_pilha[i] - 1;
                     if (game->hint.p_flags[i] == 1 && ultCarta >=0) desenha_pilha(p->end_pilhas, game->matriz, x_local, y_local, i, ultCarta);   
                     
                }
}

void alteraCor_pilha(int pilha, int tamanho_pilha, WINDOW *janela_pilha[], JOGO *game){
        werase(janela_pilha[pilha]);

        print_nomePilha(janela_pilha, pilha);
        int y_local = 3; 
        int x_local = 4;
        int ultCarta = tamanho_pilha -1;
        alteraCor_carta(pilha, y_local, x_local, ultCarta, janela_pilha,tamanho_pilha, game);
        
        wrefresh(janela_pilha[pilha]);

}

void alteraCor_carta(int pilha, int y_local, int x_local, int ultCarta, WINDOW *janela_pilha[], int tamanho_pilha, JOGO *game){
        for (int j = 0; j < tamanho_pilha; j++){
                if(game->hint.m_flags[pilha][j] == 1){
                        wattron(janela_pilha[pilha], COLOR_PAIR(5)); 
                        aux_alteraCorCarta(0,pilha, j,  y_local, x_local, ultCarta, janela_pilha, game);
                }
                else if (game->hint.m_flags[pilha][j] == 2){
                        wattron(janela_pilha[pilha], COLOR_PAIR(4)); 
                        aux_alteraCorCarta(0,pilha, j,  y_local, x_local, ultCarta, janela_pilha, game);
                }
                else {
                        aux_alteraCorCarta(1 ,pilha, j,  y_local, x_local, ultCarta, janela_pilha, game);
 
                }
                wattroff(janela_pilha[pilha], COLOR_PAIR(5));
                wattroff(janela_pilha[pilha], COLOR_PAIR(4));

                x_local+=2; 
                
        }
}

void aux_alteraCorCarta(int f, int pilha, int j, int y_local, int x_local, int ultCarta, WINDOW *janela_pilha[], JOGO *game){
        if (j == ultCarta) 
                wprint_cartaInt(f, janela_pilha[pilha], y_local, x_local, game->matriz[pilha][j]);
        else 
                wprint_cartaTop(f, janela_pilha[pilha], y_local, x_local, game->matriz[pilha][j]);
       
}

// ----- ATUALIZA PILHAS DA JOGADA  -----

void update_pilha(JOGO *game, POINTERS *p){
        if (game->jog_atual.flag == 0 && game->jog_atual.pilha != (-1)) pilha_negrito(game, p);
        else if (game->jog_atual.flag == 1 && game->jog_atual.coluna != (-1)){
                redesenha_pilha(game->jog_atual.pilha, game->matriz, p->end_pilhas, game->tamanho_pilha); // SAIDA
                redesenha_pilha(game->jog_atual.chegada, game->matriz, p->end_pilhas, game->tamanho_pilha); // CHEGADA
               
        }
        else redesenha_pilha(game->jog_atual.pilha, game->matriz, p->end_pilhas, game->tamanho_pilha); // TIRA O QUE TAVA EM NEGRITO - jogada inválida
}

// Função que faz o print das cartas da pilha x
void redesenha_pilha(int pilha, CARTAS matriz[10][17], WINDOW *janela_pilha[], int tamanho_pilha[]){
        werase(janela_pilha[pilha]);

        print_nomePilha(janela_pilha, pilha); 

        int y_local = 3; 
        int x_local = 4;
        int ultCarta = tamanho_pilha[pilha] - 1; 
        if(ultCarta >= 0)
                desenha_pilha(janela_pilha, matriz, x_local, y_local, pilha, ultCarta); 

        wrefresh(janela_pilha[pilha]);
}

// Função que principal que faz o print em NEGRITO 
void pilha_negrito(JOGO*game, POINTERS * p){
        int pilha = game->jog_atual.pilha ;
        int coluna = game ->jog_atual.coluna;
        werase(p->end_pilhas[pilha]);

        print_nomePilha(p->end_pilhas, pilha); 
        
        int y_local = 3; 
        int x_local = 4;
        int lim = coluna; 
        int ultCarta = game->tamanho_pilha[pilha] - 1; 
        if (ultCarta >= 0)
                print_pilha(p->end_pilhas[pilha],game->matriz, x_local, y_local, pilha, lim, ultCarta); 

        wrefresh(p->end_pilhas[pilha]);
}

// Função AUXILIAR que faz o print em negrito 
void print_pilha(WINDOW *janela, CARTAS matriz[10][17], int x_local, int y_local, int i, int lim, int ultCarta){
    for(int j = 0; j <= ultCarta; j++) {
        // Se a carta atual (j) for igual ou maior que o limite clicado, ativa o destaque
        if (j >= lim) { 
            wattron(janela, A_BOLD | A_BLINK);
        }

        if (j == ultCarta) 
            wprint_cartaInt(1,janela, y_local, x_local, matriz[i][j]);
        else 
            wprint_cartaTop(1, janela, y_local, x_local, matriz[i][j]);

        // Desliga IMEDIATAMENTE após imprimir a carta para não pintar o fundo da janela
        wattroff(janela, A_BOLD | A_BLINK);
        
        x_local += 2; // EMPILHAMENTO VERTICAL 
    }
}

//  ----- PRINCIPAIS PRINTS + DEFINIÇÃO DAS JANELAS/BOTÕES -----

void define_TodasJanelas (POINTERS *p, JOGO *game){ 
    
    // PILHAS 
    definePilhas(game->matriz, game->tamanho_pilha, p->end_pilhas);
    
    // BARALHO & DESCARTE
    defineFoundations(p->end_foundations); 
    
    // BOTÕES 
    p->end_undo = defineButtonUndo();
    p->end_hint = defineButtonHint();
    p->end_ngame = defineButtonNgame();
 
}

// -- BOTÕES --
WINDOW* defineButtonHint(){
        WINDOW *janela_hint;
        janela_hint = newwin(3, 10, 2, 20);
        box(janela_hint, 0, 0);
        wattron(janela_hint, COLOR_PAIR(3));
        mvwprintw(janela_hint, 1, 1, "  HINT");
        wrefresh(janela_hint);
        wattroff(janela_hint, COLOR_PAIR(3));

        return janela_hint;

}

WINDOW* defineButtonUndo(){ 
        WINDOW *janela_undo;
        janela_undo = newwin(3, 10, 2, 30);
        box(janela_undo, 0, 0);
        wattron(janela_undo, COLOR_PAIR(3));
        mvwprintw(janela_undo, 1, 1, "  UNDO");
        wrefresh(janela_undo);
        wattroff(janela_undo, COLOR_PAIR(3));

        return janela_undo; 

}

WINDOW* defineButtonNgame(){
        WINDOW *janela_ngame;
        janela_ngame = newwin(3, 10, 2, 40);
        box(janela_ngame, 0, 0);
        wattron(janela_ngame, COLOR_PAIR(3));
        mvwprintw(janela_ngame, 1, 1, "NEW GAME");
        wrefresh(janela_ngame);
        wattroff(janela_ngame, COLOR_PAIR(3));
        return janela_ngame;

}

// -- FOUNDATIONS --
void defineFoundations(WINDOW *janela_foundations[]){ 
        // Define a carta que vai ser mostrada 
        CARTAS c;
        c.naipe = '?';
        c.valor = 0;

        int x = 1;
        int y = 120; 

        // Cria as 4 janelas das foundations 
        for(int i = 0; i < 4; i++){
                janela_foundations[i] = newwin(10, 15, x, y);
                
                mvwprintw(janela_foundations[i], 1, 1, "Foundation %d", i+1);
                wprint_cartaInt(1, janela_foundations[i], 3,3, c);
                y += 18; 

                wrefresh(janela_foundations[i]); 

        }

}

// -- PILHAS -- 
void definePilhas(CARTAS matriz[10][17], int tamanho_pilha[10], WINDOW *janela_pilha[]) {
    int i;
    int y = 10;
    int x = 10;

    for(i = 0; i < 10; i++) {
        janela_pilha[i] = newwin(42, 15, y, x);
        
        print_nomePilha(janela_pilha, i); 
        

        int y_local = 3; 
        int x_local = 4;
        int ultCarta = tamanho_pilha[i] - 1; 
        if(ultCarta >= 0){
                desenha_pilha(janela_pilha,matriz, x_local, y_local, i, ultCarta); 
                x += 20;
        }
                

        wrefresh(janela_pilha[i]);
    }
}

// AUXILIARES (definePilhas)
void print_nomePilha (WINDOW *janela_pilha[], int i){
        wattron(janela_pilha[i], COLOR_PAIR(3));
        mvwprintw(janela_pilha[i], 2, 2, "  PILHA %d  ", i+1);
        wattroff(janela_pilha[i], COLOR_PAIR(3));

}


void desenha_pilha (WINDOW *janela_pilha[],CARTAS matriz[10][17],  int x_local, int y_local, int i, int ultCarta){
        for(int j = 0; j <= ultCarta; j++) {
            if (j == ultCarta) wprint_cartaInt(1, janela_pilha[i], y_local, x_local, matriz[i][j]);
            else wprint_cartaTop(1, janela_pilha[i], y_local, x_local, matriz[i][j]);
            x_local += 2; // Ajusta conforme a lógica de empilhamento
        }
        wrefresh(janela_pilha[i]);
}


// --- PRINT CARTAS (window) --- 

void wprint_cartaInt(int f, WINDOW *win, int x, int y, CARTAS c){ 
        const char *s = traduzsimbolo(c.naipe);

        // guarda o valor da carta 
        char valor[3]; 
        traduzvalor(valor, c.valor); // arrays ja sao pointers por natureza portanto fazer '&valor' da o ponteiro de outro ponteiro 


        // Ativa as cores específicas de cada carta
        if (f){
                if (c.naipe == 'C' || c.naipe == 'O')
                wattron(win, COLOR_PAIR(1));
                else
                wattron(win, COLOR_PAIR(2));
        }

        // Faz o print da carta na janela
        print_carta(win, x, y, s, valor);
       

        refresh();

        // Desativa o atributo das cores
        wattroff(win, COLOR_PAIR(1));
        wattroff(win, COLOR_PAIR(2));



}


void wprint_cartaTop(int f, WINDOW *win, int x, int y,  CARTAS c){

        char valor[3]; // guarda o valor da carta 
        traduzvalor(valor, c.valor);

        const char *s = traduzsimbolo(c.naipe);

        // Ativa as cores específicas de cada carta
        if (f){
                if (c.naipe == 'C' || c.naipe == 'O')
                wattron(win, COLOR_PAIR(1));
                else
                wattron(win, COLOR_PAIR(2));
        }


        mvwprintw(win, y,   x, "+ ----- +");
        mvwprintw(win, y+1, x, "| %-2s%s   |", valor, s);

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
