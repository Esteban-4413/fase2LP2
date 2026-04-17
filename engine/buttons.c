
#include "actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prints.h"
#include "game.h"

// Limite de jogadas guardadas no histórico
#define MAX_UNDO 5 


/*
void hint(JOGO *game){
    
    // Pega na carta do topo do descarte
    CARTAS carta_descarte = game->pilha_descarte[game->tamanho_pilha_descarte-1];
    
    // Procura uma jogada possível na mesa
    int find = auxiliar_hint(game, carta_descarte);
    
    // Se não encontrar jogadas, avisa o jogador
    if (!find) mvprintw(0, 2, "não ha jogadas na mesa                                         ");
    refresh();

}

int auxiliar_hint(JOGO *game, CARTAS carta_descarte){

    // Percorre as 7 pilhas
    for (int i = 0; i < 7; i ++) 
    {   
        int c = game->tamanho_pilha[i] -1; 
        if ( c > 0 ) { // Se a pilha não estiver vazia
            int valor_carta = game->matriz[i][c].valor;

            // Verifica se a diferença de valores é exatamente 1
            if (c > 0 && valor_carta != 0 && abs(valor_carta - carta_descarte.valor) == 1){
                mvprintw(0, 2, "HINT: Carta na pilha  %d                                        ", i + 1);
                refresh(); 
                return 1; // encontrou jogada jogada válida
            }
        }

    
    }
    return 0; // Não encontrou nenhuma jogada válida
}

*/

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
