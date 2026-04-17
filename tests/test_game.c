#include <CUnit/CUnit.h>
#include "../engine/actions.h"
#include "../engine/game.h"

// Testa se a inicialização de um novo jogo define os valores corretos
void testar_start_game(void) {
    JOGO game;
    start_game(&game);

    CU_ASSERT_EQUAL(game.tamanho_baralho, 52);
    CU_ASSERT_EQUAL(game.tamanho_pilha[0], 8);
    CU_ASSERT_EQUAL(game.tamanho_pilha[5], 7);
    CU_ASSERT_EQUAL(game.jogadas_historial, 0);
}

// Testa se o Reset da jogada atual limpa as variáveis do rato
void testar_inicializa_jogAtual(void) {
    JOGO game;
    inicializa_jogAtual(&game);

    CU_ASSERT_EQUAL(game.jog_atual.pilha, -1);
    CU_ASSERT_EQUAL(game.jog_atual.flag, -2);
}