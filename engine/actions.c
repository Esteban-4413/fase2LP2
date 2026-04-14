#include "actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int valida_jogada(int y, int x, JOGO *game){
    
    /** Se a pilha está vazia, a jogada é imediatamente inválida.
     */
    if (game->tamanho_pilha[y] <= 0) {
        return 0; 
    }

    /** Se a carta escolhida não for a última da coluna, verificar se há
     * sequência até o fim
     */
    if ((x == game->tamanho_pilha[y] - 1) || ((tamanho_sequencia(x, y, game) == game->tamanho_pilha[y] - x))) return 1;
    return 0;

}

int tamanho_sequencia(int x, int y, JOGO *game){
    if (x == game->tamanho_pilha[y] - 1){
        return 1;
    }
    if ((game->matriz[y][x].valor == game->matriz[y][x+1].valor + 1)
        && game->matriz[y][x].naipe == game->matriz[y][x+1].naipe){
        return 1 + tamanho_sequencia(x+1, y, game);
    }
    return 1;
}