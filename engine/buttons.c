#include "actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prints.h"
#include "game.h"

// Limite de jogadas guardadas no histórico
#define MAX_UNDO 5 



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


void registar_jogada(int tipo, int fila, int coluna, CARTAS carta_played, JOGO *game){
   
    //para meter as jogadas mais recentes então empurramos as mais velhas fora do array (Se o histórico estiver cheio, apaga a jogada mais antiga)
    if (game->jogadas_historial == MAX_UNDO){
        for (int i = 0; i < MAX_UNDO - 1; i ++)
            game->historial[i] = game->historial[i + 1];
        (game->jogadas_historial)--;
    }
    
    // Guarda os dados da nova jogada
    int jogadas_historial = game->jogadas_historial;
    game->historial[jogadas_historial].tipo = tipo;
    game->historial[jogadas_historial].fila = fila;
    game->historial[jogadas_historial].coluna = coluna;
    game->historial[jogadas_historial].carta = carta_played;

    (game->jogadas_historial)++;
}


void undo(JOGO *game){

    // Verifica se há jogadas para desfazer
    if (game->jogadas_historial == 0){ 
        mvprintw(0, 2, "oh men para retroceder tanto no tempo é mais fácil comprar uma máquina do tempo.\n");
        return;
    }

    // Acede à última jogada
    (game->jogadas_historial)--;
    struct JOGADA ultimo_mov = game->historial[game->jogadas_historial];

    // Remove a carta do descarte
    (game->tamanho_pilha_descarte) --;

    // calculamos daonde é que veio a carta

    // Devolve a carta à mesa
    if (ultimo_mov.tipo == 0){
        game->matriz[ultimo_mov.fila][ultimo_mov.coluna].valor = ultimo_mov.carta.valor;
        (game->tamanho_pilha[ultimo_mov.fila])++; 
        mvprintw(0, 2, "Undo: carta devolvida à mesa. Viagem no tempo sucedido");
    }

    // Devolve a carta ao baralho principal
    else if (ultimo_mov.tipo == 1) {
        game->baralho[game->tamanho_baralho] = ultimo_mov.carta;
        (game->tamanho_baralho)++;
        mvprintw(0,2,"Undo: carta devolvida ao baralho com repanpante sucesso");
    }
}


void novo_jogo(JOGO *game){
    // Reinicia os contadores principais
    game->tamanho_baralho = 52;
    game->tamanho_pilha_descarte = 0;
    
    // Reinicia o historial de jogadas para o undo a 0 (limpa o historial)
    game->jogadas_historial = 0;

    // Recria o baralho e distribui as cartas na mesa
    inicializa_baralho(game);
    inicializa_matriz(game);

    // Tira a primeira carta para o descarte
    bisca(game);
}
