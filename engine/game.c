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
    for (int i = 0; i < 10; i++){
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

    inicializa_jogAtual(game);
}

void inicializa_jogAtual(JOGO *game){
    game->jog_atual.pilha = (-1);
    game->jog_atual.chegada = (-1);
    game->jog_atual.flag = -2; //número que não corresponde a nenhuma das condições definidas 
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
        } else {max_pilha -= 1;}
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


void loop_principal(JOGO *game, POINTERS *p, int jogando){
    while (jogando) {
        int ch = getch();  
        // if (ganhou_jogo(game)){ mvprintw(0,2,"Vitória!"); jogando = 0;}
        if (ch == 'q') jogando = 0; // Condição de saida do jogo, clicar no "q"
        else if (ch == KEY_MOUSE) processa_rato(game, p);
    }
}

void processa_rato(JOGO *game, POINTERS *p){
    int num_carta;
    // Verifica a existencia de um click
    int r = verifica_click(game, p, &num_carta);
    next_step(r, num_carta, game, p);
}


// Funções meio definidas da logica do jogo 


void next_step (int r, int num_carta, JOGO *game, POINTERS *p){      
    if (r >= 0 && r <= 10){
        if (game->jog_atual.flag  == 1){
            //add_historial 
            inicializa_jogAtual(game);
        }
        else if(game->jog_atual.flag  == -1){
            inicializa_jogAtual(game);
        }
        else {
            define_jogAtual(r, num_carta, game);
            int pilha = game->jog_atual.pilha;
            int chegada = game->jog_atual.chegada; 
            if (game->jog_atual.flag  == 1 && pilha != chegada) {
                joga(pilha, game->jog_atual.coluna, chegada, game->tamanho_pilha[chegada], game);
            } 
            updateWin(game,p);
        }
    }
    /*
    if (r == 11) {
        hint(game);
    }
    if (r == 12){
        undo(game);
        define_TodasJanelas(p, game); 
    }
    if(r == 13){
        novo_jogo(game);
        init(p, game);

    }
    */
}

void define_jogAtual(int r, int num_carta, JOGO *game){
    if(game->jog_atual.flag == -2){
        game->jog_atual.pilha = r;
        game->jog_atual.coluna = num_carta; 
        // game->jog_atual.n = com a função do Martim isso será desnecessário
        if (num_carta <0 ) game->jog_atual.flag = 0;
        else game->jog_atual.flag = -1;
        
    }
    else if (game->jog_atual.flag == 0) {
        game->jog_atual.chegada = r;
        if (r == game->jog_atual.pilha) game->jog_atual.flag = 1;
        // preciso que no caso da chegada = saída der 1 também. 
        //else if (valida_jogada(...)) game->jog_atual.flag = 1;
        //else { game->jog_atual.flag = -1; }
    }
    
}


/*

int ganhou_jogo(JOGO *game){}

for(int y = 0; y < sizeof(game->tamanho_pilha)/4; y++){
        if (tamanho_sequencia(0, y, game) == 13) return 1;
    }
    return 0;*/