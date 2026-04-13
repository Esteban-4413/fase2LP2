
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "actions.h"
#include "prints.h"
#include "click.h"
#include <locale.h>
#include "game.h"


void init(POINTERS *janelas, JOGO *game){
    
    // codificação de caracteres
    setlocale(LC_ALL, ""); 

    // Função do aux_main - ativa as configurações gerais do Ncurses 
    ativaNcurses(); 

    // Inicializa todas o jogo (variáveis)
    start_game(game);

    // Inicialização do baralho com as 52 cartas regulares
    inicializa_baralho(game);

    // Inicialização das colunas de cartas com cartas do baralho
    inicializa_matriz(game);

    
    
    // ---------- PRINTS DO JOGO ----------

    define_TodasJanelas(janelas, game);
}


void ativaNcurses(){

    // Inicia ncurses
    initscr(); 

    // o que o ultilizador digita não aparece no ecrã
    noecho();  

    // Ativa a leitura de teclas especiais
    keypad(stdscr, TRUE);


    // Ativa as cores 
    start_color(); 

    // Definindo os pares de cores 
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    //Alterei a cor do Cyan predefinida
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);

    // Ativa o leitor de eventos do Mouse 
    mousemask(ALL_MOUSE_EVENTS, NULL);

    cbreak();
}


void start_game(JOGO *game){
    
    // Número inicial de cartas no baralho 
    game->tamanho_baralho = 52; 

    int max_pilha = 8; //numero de cartas por pilha 
    // Inicializa cada pilha da mesa com o seu devido num de cartas 
    for (int i = 0; i < 7; i++){
        if (i < 3) max_pilha = 8;
        else max_pilha -= 1;
        // Número de cartas na pilha i 
        game->tamanho_pilha[i] = max_pilha; 
    }


    // Número de jogadas realizadas começa a 0
    game->jogadas_historial = 0; 

    /*
     Inicialização dos naipes
    
     C - Copas  
     E - Espadas  
     O - Ouros  
     P - Paus
     */
    game->naipes[0] = 'C';
    game->naipes[1] = 'E';
    game->naipes[2] = 'O';
    game->naipes[3] = 'P';
}


void inicializa_baralho(JOGO *game){
    int indice = 0;
    
    //Para cada naipe, percorre as cartas com valores de 1 a 13.
    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 13; j++){
            game->baralho[indice].valor = j;
            game->baralho[indice].naipe = game->naipes[i];
            indice++;
        }
    }
}


void inicializa_matriz(JOGO *game){
    srand(time(NULL));
    int indice_carta;
    int max_pilha = 8;
    for(int i = 0; i < 10; i++){
        if(i<3){  // Três primeiras pilhas com 8 cartas, as outras com -1 da anterior; 
            max_pilha = 8;
        } else {max_pilha -= 1}
        for(int j = 0; j < max_pilha; j++){

            // Seleciona uma carta aleatória 
            indice_carta = rand() % game->tamanho_baralho; 

            // Atribui a carta à matriz 
            game->matriz[i][j] = game->baralho[indice_carta]; 

            // Remove a carta do baralho, trocando-a com a última e diminuindo o tamanho
            game->baralho[indice_carta] = game->baralho[game->tamanho_baralho - 1];
            (game->tamanho_baralho)--;
        }
    }
}
