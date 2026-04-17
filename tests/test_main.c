#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Dizemos ao compilador que estas funções existem nos outros ficheiros
extern void testar_valida_jogada_origem(void);
extern void testar_tamanho_sequencia(void);
extern void testar_start_game(void);
extern void testar_inicializa_jogAtual(void);
extern void testar_registar_jogada(void);

int main() {
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
    CU_basic_set_mode(CU_BRM_VERBOSE);

    // 1. Suite Actions
    CU_pSuite pSuiteActions = CU_add_suite("Suite_Actions", NULL, NULL);
    if (pSuiteActions != NULL) {
        CU_add_test(pSuiteActions, "Valida Origem", testar_valida_jogada_origem);
        CU_add_test(pSuiteActions, "Tam. Sequencia", testar_tamanho_sequencia);
    }
    
    // 2. Suite Game
    CU_pSuite pSuiteGame = CU_add_suite("Suite_Game", NULL, NULL);
    if (pSuiteGame != NULL) {
        CU_add_test(pSuiteGame, "Start Game", testar_start_game);
        CU_add_test(pSuiteGame, "Limpa Jogada", testar_inicializa_jogAtual);
    }

    // 3. Suite Buttons
    CU_pSuite pSuiteButtons = CU_add_suite("Suite_Buttons", NULL, NULL);
    if (pSuiteButtons != NULL) {
        CU_add_test(pSuiteButtons, "Regista Jogada", testar_registar_jogada);
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}