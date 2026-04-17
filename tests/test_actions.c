#include <CUnit/CUnit.h>
#include "../engine/actions.h"
#include "../engine/game.h"

// Testa se o jogo rejeita origens vazias e aceita cartas no topo
void testar_valida_jogada_origem(void) {
    JOGO game;
    game.tamanho_pilha[0] = 0; // Pilha vazia
    game.tamanho_pilha[1] = 3; // Pilha com 3 cartas

    CU_ASSERT_EQUAL(valida_jogada_origem(0, 0, &game), 0);
    CU_ASSERT_EQUAL(valida_jogada_origem(1, 2, &game), 1);
}

// Testa se a contagem do tamanho das sequências está correta
void testar_tamanho_sequencia(void) {
    JOGO game;
    game.tamanho_pilha[0] = 2;
    
    game.matriz[0][0].valor = 5; game.matriz[0][0].naipe = 'C';
    game.matriz[0][1].valor = 4; game.matriz[0][1].naipe = 'C';

    CU_ASSERT_EQUAL(tamanho_sequencia(0, 0, &game), 2);
    CU_ASSERT_EQUAL(tamanho_sequencia(1, 0, &game), 1);
}