
#include "actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prints.h"
#include "game.h"

// Limite de jogadas guardadas no histórico
#define MAX_UNDO 5 



void hint(JOGO *game){

    int flag;
    for(int y = 0; y < 10; y++){ /* Por cada pilha */
        flag = 0;
        for(int x = 0; x < game->tamanho_pilha[y] && !flag; x++){ /* Por cada carta */
            /* Se há uma sequência que começa nessa mesma carta e vai
                até ao fundo da pilha, procurar destinos para esta carta */
            if (tamanho_sequencia(x, y, game) == game->tamanho_pilha[y] - x)
                procura_destino(y, x, game, &flag);
        }
        
        
    }
    
    if (temHint(game)) game->hint.flag = -1;
}

int temHint(JOGO *game){
    for(int i = 0; i < 10; i++){
        if (game->hint.p_flags[i] == 1) return 1; 
    }
    return 0; 
}

void procura_destino(int y, int x, JOGO *game, int *flag){
    for (int y2 = 0; y2 < 10; y2++){
        CARTAS carta_origem = game->matriz[y][x];
        CARTAS carta_destino = game->matriz[y2][game->tamanho_pilha[y2]-1];
        if (carta_origem.valor == carta_destino.valor - 1){ /* Se encontrar destino */
            *flag = 1;
            /* Decide de que cor piscar */
            if (carta_origem.naipe == carta_destino.naipe){
                game->hint.m_flags[y][x] = 1;
                game->hint.p_flags[y] = 1;
                 /*< Carta fica VERDE */
            }
            else{
                game->hint.m_flags[y][x] = 2;
                game->hint.p_flags[y] = 1;
                 /*< Carta fica AMARELA */
            }
        }
    }
}

void registar_jogada(JOGO *game){
   
    //para meter as jogadas mais recentes então empurramos as mais velhas fora do array (Se o histórico estiver cheio, apaga a jogada mais antiga)
    if (game->jogadas_historial == MAX_UNDO){
        for (int i = 0; i < MAX_UNDO - 1; i ++)
            game->historial[i] = game->historial[i + 1];
        (game->jogadas_historial)--;
    }
    
    // Guarda os dados da nova jogada
    int jogadas_historial = game->jogadas_historial;
    game->historial[jogadas_historial].pilha = game->jog_atual.pilha;
    game->historial[jogadas_historial].coluna = game->jog_atual.coluna;
    game->historial[jogadas_historial].chegada = game->jog_atual.chegada;
    game->historial[jogadas_historial].n = game->jog_atual.n;
    

    (game->jogadas_historial)++;
}


void undo(JOGO *game){

    // Verifica se há jogadas para desfazer
    if (game->jogadas_historial == 0){ 
        mvprintw(0, 2, "oh men para retroceder tanto no tempo é mais fácil comprar uma máquina do tempo.\n");
        return;
    }
    
    // Faz o undo 
    aux_undo(game);
    
}

void aux_undo(JOGO *game){
    // Acede à última jogada
    (game->jogadas_historial)--;
    struct JOGADA ultimo_mov = game->historial[game->jogadas_historial];

    int origem = ultimo_mov.pilha;
    int chegada = ultimo_mov.chegada;
    int n = ultimo_mov.n; 
    int pos_original = ultimo_mov.coluna; // Onde elas estavam na origem

    // Localiza as cartas na chegada
    int pos_atual_chegada = game->tamanho_pilha[chegada] - n;

    //O Loop de Devolução
    for (int i = 0; i < n; i++) {
        game->matriz[origem][pos_original + i] = game->matriz[chegada][pos_atual_chegada + i];
    }

    // Ajustar os contadores de tamanho
    game->tamanho_pilha[origem] += n;
    game->tamanho_pilha[chegada] -= n;
}
