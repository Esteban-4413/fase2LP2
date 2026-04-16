#include "actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Função que altera as posições da carta ou sequência de cartas de acordo com
 * as coordenadas que recebe
*/
void joga(int y, int x, int y2, int x2, JOGO *game){
    /** As cartas da sequência na pilha y vão sendo adicionadas à pilha y2*/
    for(x, x2; x < game->tamanho_pilha[y]; x++, x2++){
        game->matriz[y2][x2] = game->matriz[y][x]; 
        game->tamanho_pilha[y2]++; /**< O tamanho da pilha y2 vai incrementando por 1 */
        game->tamanho_pilha[y]--;/**< O tamanho da pilha y vai decrementando por 1 */
    }

}

int valida_jogada_origem(int y, int x, JOGO *game){
    
    /** Se a pilha está vazia, a jogada é imediatamente inválida.
     * nota: penso que nao seja preciso esta parte, já que neste jogo
     * os cliques sao em cartas e nao em pilhas (nunca podes clicar numa carta que nao esta la)
     */
    if (game->tamanho_pilha[y] <= 0) {
        return 0; 
    }

    /** Se a carta escolhida for a última da coluna ou está numa sequência que vai até ao fim da coluna,
     * a jogada é válida
     */
    if ((x == game->tamanho_pilha[y] - 1)
        || ((tamanho_sequencia(x, y, game) == game->tamanho_pilha[y] - x)))
        return 1;
    return 0;

}

int valida_jogada_destino(int y, int x, int y2, int x2, JOGO *game){
    /* Verificar que a cabeca da sequencia é valida em cima da ultima carta da pilha*/
    if (game->matriz[y2][x2].valor == game->matriz[y][x].valor - 1
        && game->matriz[y2][x2].naipe == game->matriz[y][x].naipe
        && game->tamanho_pilha[y] + tamanho_sequencia(x2, y2, game) <= 17)
        return 1;
    return 0;
}

/*
  Função que calcula, dada uma carta em uma pilha, qual o tamanho da sequência/combo
  que podem ser movidos com a carta. 

*/
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