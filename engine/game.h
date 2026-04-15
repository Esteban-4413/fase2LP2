
#ifndef GAME_H
#define GAME_H
#include <ncurses.h>
#include "actions.h"
#include "prints.h" // É de onde a estrutura POINTERS vem

void init(POINTERS *janelas, JOGO *game);
void ativaNcurses();
void start_game(JOGO *game);
void inicializa_jogAtual(JOGO *game);
void inicializa_baralho(JOGO *game);
void inicializa_matriz(JOGO *game);

void loop_principal(JOGO *game, POINTERS *janelas, int jogando);




#endif