#include <CUnit/CUnit.h>
#include "../engine/actions.h"
#include "../engine/game.h"

// Testa se o histórico de Undo regista a informação corretamente
void testar_registar_jogada(void) {
    JOGO game;
    game.jogadas_historial = 0;
    
    game.jog_atual.pilha = 1;
    game.jog_atual.coluna = 2;
    game.jog_atual.chegada = 3;
    game.jog_atual.n = 1;

    registar_jogada(&game);

    CU_ASSERT_EQUAL(game.jogadas_historial, 1);
    CU_ASSERT_EQUAL(game.historial[0].pilha, 1);
}