

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "actions.h"
#include "prints.h"
#include "click.h"
#include <locale.h>
#include "game.h"


int main(){
    JOGO game; 

    // ponteiros que guardam os endereços das janelas 
    POINTERS janelas;
    init(&janelas, &game);

   
    // ---------- JOGO ----------

    // 1 quando o jogo esta ativo e 0 quando acabou, i.e, nao existem jogadas possiveis e o baralho não tem cartas 
    int jogando = 1;
    loop_principal(&game, &janelas, jogando);

    endwin(); // Encerra o ncurses
    return 0;
} 

