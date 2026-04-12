/**
 * @file prints.h
 * @author Esteban Yepez (a116272), Fernanda Cidrim (a116274), Martim Sousa (a113572)
 * @brief Declarações das funções e estruturas que tratam da parte gráfica do jogo (ncurses).
 * @version 0.1
 * @date 2026-03-22
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "actions.h"
#ifndef PRINTS_H
#define PRINTS_H
#include <ncurses.h>


// Typedef que guardará todos os endereços das janelas 

/**
 * @brief Struct construida para guardar os endereços de todas as janelas 
 * e tornar mais fácil o seu manuseio ao ultilizar o bloco como argumento 
 *  das funções, no lugar de cada um dos pointers individualmente. 
 */
typedef struct {
    WINDOW *end_pilhas[7];  /**< Array com os endereços das janelas das 7 pilhas da mesa. */
    WINDOW *end_descarte;   /**< Endereço da janela do monte de descarte. */
    WINDOW *end_baralho;    /**< Endereço da janela do baralho principal (bisca). */
    WINDOW *end_hint;       /**< Endereço da janela do botão Hint. */
    WINDOW *end_undo;       /**< Endereço da janela do botão Undo. */
    WINDOW *end_ngame;      /**< Endereço da janela do botão New Game. */

} POINTERS ; 

/**
 * @brief Recebe da definição da carta, o seu naipe, ou seja um char 
 * e atribui o devido simbólo a esse char. 
 *  
 * 
 * @param naipe 
 * @return const char* endereço da memória onde fica guadado , apenas para leitura, o símbolo
 */
const char* traduzsimbolo(char naipe);

/**
 * @brief "Traduz" o valor da carta 
 * Para os casos mais éspecíficos, onde as cartas acima de 10 passam para J, Q e K 
 * e as cartas de valor 1, passam para A. 
 * 
 * @param valor endereço onde fica guardado o novo valor - um char
 * @param v valor int que vem da definição das cartas 
 */
void traduzvalor(char *valor, char v); 

/**
 * @brief Faz print na tela de uma carta inteira
 * Auxiliar da wprint_cartaInt.
 * 
 * @param win Endereço da janela onde o print será feito o print
 * @param x Coluna de onde se iniciam os prints
 * @param y Linha de onde se iniam os prints
 * @param s Simbolo da carta (já traduzido)
 * @param valor Valor da carta (já traduzido)
 */
void print_carta(WINDOW *win, int x, int y, const char *s, char valor[3]); // Auxiliar só da wprint_cartaInt

/**
 * @brief Função geral que faz print de uma crta inteira numa janela 
 * Dada a carta, chama as funções traduz_valor e traduz_simbolo, e com as informações
 * fornecidas por essas chama a print_carta. 
 * 
 * 
 * @param win Endereço da janela onde o print será feito o print
 * @param x Coluna de onde se iniciam os prints
 * @param y Linha de onde se iniam os print
 * @param c Carta a ser mostrada no ecrã
 */
void wprint_cartaInt(WINDOW *win, int x, int y, CARTAS c);

/**
 * @brief Função geral que faz print de uma crta inteira numa janela 
 * Dada a carta, chama as funções traduz_valor e com a informação fornacida por essa 
 * faz print da carta na janela. 
 * Usada para as cartas da pilha. 
 * 
 * @param win Endereço da janela onde o print será feito o prin
 * @param x Coluna de onde se iniciam os print
 * @param y Linha de onde se iniam os prin
 * @param c Carta a ser mostrada no ecr
 */
void wprint_cartaTop(WINDOW *win, int x, int y, CARTAS c);

/**
 * @brief Define a janela de cada uma das pilhas e já desenha as cartas
 * 
 * Cria a janela de cada uma das pilhas, e logo a seguir chama a print_nomePilha 
 * e a desenha_pilha. 
 * 
 * @param matriz matriz onde estão organizadas as cartas nas 7 pilhas de 5 cartas
 * @param tamanho_pilha array onde é guardado o tamanho de cada uma das 7 pilhas
 * @param janela_pilha array onde estão guadados os endereços de cada um adas 7 pilhas 
 */
void definePilhas(CARTAS matriz[7][5], int tamanho_pilha[7], WINDOW *janela_pilha[]);

/**
 * @brief Faz print do nome da pilha 
 * !!Lembrando que quando faz print temos i+1, pois no jogo não é muito usual ter uma pilha 0!!
 * 
 * @param janela_pilha array onde estão guadados os endereços de cada um adas 7 pilhas 
 * @param i indice da pilha no array
 */
void print_nomePilha (WINDOW *janela_pilha[], int i);

/**
 * @brief Print das cartas de uma pilha 
 * verifica o tamanho da pilha, e sempre faz wprint_cartaTop para todas execeto a que está 
 * no topo da pilha, a esta é feito wprint_cartaInt.
 * 
 * @param janela_pilha array onde estão guadados os endereços de cada um adas 7 pilha
 * @param matriz matriz onde estão organizadas as cartas nas 7 pilhas de 5 carta
 * @param x_local coluna definida da DefinePilhas
 * @param y_local linha definida da DefinePilhas 
 * @param i       indice da pilha no array 
 * @param ult_carta 
 */
void desenha_pilha (WINDOW *janela_pilha[],CARTAS matriz[7][5],  int x_local, int y_local, int i, int ult_carta);

/**
 * @brief define a janela, e faz print da carta 
 * Com o auxilio do tamanho_pilha_descarte verifica, se temos alguma carta no descarte 
 * e fazemos print da que está no topo. 
 * 
 * @param pilha_descarte Array do descarte 
 * @param tamanho_pilha_descarte Int que guada o tamanho do descarte 
 * @return WINDOW* Endereço da janela da pilha de descarte 
 */
WINDOW* defineDescarte(CARTAS pilha_descarte[52], int tamanho_pilha_descarte);

/**
 * @brief Define a janela do baralho, e faz print da carta virada 
 * Com auxilio do tamanho_baralho, verificamos se ainda há cartas no baralho, se houver, 
 * é feito print de uma carta definida nesta função, apenas para ilustrar a parte de trás da carta. 
 *  Para além de fazer print do número de cartas que ainda há no baralho. 
 * 
 * @param tamanho_baralho IInt que guarda o tamanho do baralho
 * @return WINDOW* Endereço da janela do baralho
 */
WINDOW* defineBaralho(int tamanho_baralho); // a funcao na linha 82 de prints.c recebe como argumento o tamanho do baralho

/**
 * @brief Define a janela do botão hint 
 * É criada a janela,e depois feito print do nome do botão. 
 * 
 * @return WINDOW* Endereço da janela do botão hint
 */
WINDOW* defineButtonHint();

/**
 * @brief Define a janela do botão undo 
 * É criada a janela,e depois feito print do nome do botão. 
 * 
 * @return WINDOW* Endereço da janela do botão
 */
WINDOW* defineButtonUndo();

/**
 * @brief Define a janela do botão new game
 * É criada a janela,e depois feito print do nome do botão. 
 * 
 * @return WINDOW* Endereço da janela do botão
 */
WINDOW* defineButtonNgame();

/**
 * @brief Função que define todas as janelas para inicialização do jogo 
 * 
 * atribui a cada um dos parâmetros do struct p, criado no main, o endereço que lá ficará
 * guardado, chamando as funções: 
 * definePilhas, defineDescarte, defineBaralho, defineButtonUndo, defineButtonHint e defineButtonNgame
 * 
 * @param p recebe do main o poiter de onde seram guadados todos os endereços das janelas 
 * @param game recebe o game ("bloco" onde é guadado o baralho, o descarte, a matriz...)
 */
void define_TodasJanelas (POINTERS *p, JOGO *game);

#endif