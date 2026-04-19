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

    setup_test_cases(game); 

    // Inicialização do baralho com as 52 cartas regulares
    inicializa_baralho(game);

    // Inicialização das colunas de cartas com cartas do baralho
    //inicializa_matriz(game);

    
    
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

    init_pair(5, COLOR_GREEN, COLOR_WHITE);
    init_pair(4, COLOR_YELLOW, COLOR_WHITE);

    // Ativa o leitor de eventos do Mouse 
    mousemask(ALL_MOUSE_EVENTS, NULL);

    cbreak();
}

void setup_test_cases(JOGO *game) {
    // 1. Reset total
    for(int i = 0; i < 10; i++) game->tamanho_pilha[i] = 0;
    for(int i = 0; i < 4; i++) game->foundations[i] = 0;

    char naipes_teste[4] = {'C', 'E', 'O', 'P'}; 

    // Preencher Pilhas 1, 2, 3 e 4 (índices 0, 1, 2, 3)
    for (int p = 0; p < 4; p++) {
        // Colocar do REI (13) no fundo até ao ÁS (1) perto do topo
        for (int v = 0; v < 13; v++) {
            game->matriz[p][v].valor = 13 - v; // Começa em 13, termina em 1
            game->matriz[p][v].naipe = naipes_teste[p];
        }
        
        // 2. A carta OBSTÁCULO (índice 13)
        // Colocamos um 7 de Paus que "tapa" a sequência
        game->matriz[p][13].valor = 7;
        game->matriz[p][13].naipe = 'P';
        
        game->tamanho_pilha[p] = 14; 
    }

    // 3. Pilha 5 (Índice 4) - O "porto seguro" para mover os 7s
    // Colocamos um 8 de Paus na base para podermos mover o 7 para lá
    game->matriz[4][0].valor = 8;
    game->matriz[4][0].naipe = 'P';
    game->tamanho_pilha[4] = 1;

    // Limpar o resto (6 a 10)
    for (int i = 5; i < 10; i++) game->tamanho_pilha[i] = 0;
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

    // Inicialização dos naipes
    inicializa_naipes(game);
   // Inicializa a Jogada Atual
    inicializa_jogAtual(game);
    // Inicializa o Hint
    inicializa_hint(game);
    // Inicializa os foundations
    inicilaiza_foundations(game);


}

void inicilaiza_foundations(JOGO *game){
    for (int i = 0; i < 4; i++){
        game->foundations[i] = 0;
    }
}

void inicializa_hint(JOGO *game){
    game->hint.flag = 0; // flag inicia a 0 (indica que está vazio o Hint)
    for(int i = 0; i < 10; i++) {
        game->hint.p_flags[i] = 0; 
        for(int j = 0; j < 17; j++) game->hint.m_flags[i][j] = 0;
    }

}

void inicializa_naipes(JOGO *game){
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
void inicializa_jogAtual(JOGO *game){
    game->jog_atual.pilha = (-1);
    game->jog_atual.chegada = (-1);
    game->jog_atual.flag = -2; //número que não corresponde a nenhuma das condições definidas 
    game->jog_atual.n = -1;
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
        define_maxdaPilha(&max_pilha,i);
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

void define_maxdaPilha(int *max_pilha, int i){
        if(i<3){  // Três primeiras pilhas com 8 cartas, as outras com -1 da anterior; 
            *max_pilha = 8;
        } else { *max_pilha -= 1;}
}

void loop_principal(JOGO *game, POINTERS *p, int jogando){
    while (jogando) {
        int ch = getch(); 
        if (ganhou_jogo(game)){ mvprintw(0,60,"Vitória!"); jogando = 0;}
        if (ch == 'q') jogando = 0; // Condição de saida do jogo, clicar no "q"
        else if (ch == KEY_MOUSE) {
            processa_rato(game, p);
        }
    }
}

// Verifica se podemos preencher algum dos foundations
void foundations(JOGO *game, POINTERS *p){
    int i = verifica_foudations(game);
    if( i != (-1)) {

        atualizaFoundations(game, p);

        werase(p->end_pilhas[i]);
        print_nomePilha(p->end_pilhas, i); 

        int x_local = 4;
        int y_local = 3;
        int ultCarta = game->tamanho_pilha[i] - 1;
        if (ultCarta >= 0) 
            desenha_pilha(p->end_pilhas, game->matriz, x_local, y_local, i, ultCarta);
            
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
    // Click em alguma das pilhas 
    if (r >= 0 && r <= 10){
        desativa_hint(game,p);
        inicializa_hint(game);
        //print_hint(game->hint);
        naPilha(r, num_carta, game, p);
        
        
    }

    // Click nos botões 
     if(r == 13){
        start_game(game);
        init(p, game);

    }
    if (r == 12){
        undo(game);
        define_TodasJanelas(p, game); 
    }
    
    if (r == 11) {
        hint(game);
        //print_hint(game->hint);
        redesenha_pilhasHint(game->hint.flag, game, p);
        
    }   
    
}

void desativa_hint(JOGO *game, POINTERS *p){
    if(game->hint.flag == -1) {
            game->hint.flag = 1;
            redesenha_pilhasHint(1, game, p);
        }
}


void naPilha(int r, int num_carta, JOGO *game, POINTERS *p){
    if(game->jog_atual.flag == 1 || game->jog_atual.flag == -1){
            inicializa_jogAtual(game);
        }
    define_jogAtual(r, num_carta, game);
    int pilha = game->jog_atual.pilha;
    int chegada = game->jog_atual.chegada; 
    if (game->jog_atual.flag  == 1 && pilha != chegada) {
            joga(pilha, game->jog_atual.coluna, chegada, game->tamanho_pilha[chegada], game);
            foundations(game, p);
            registar_jogada(game);
                
        } 
            
    update_pilha(game,p);
  
    
    refresh();  
}



void define_jogAtual(int r, int num_carta, JOGO *game){
    if(game->jog_atual.flag == -2){
        game->jog_atual.pilha = r;
        game->jog_atual.coluna = num_carta; 
        //mvprintw(2, 60 , "COLUNA :  %d      .                                  ", num_carta);
        if (num_carta >= 0 && evalida_tamanhoSeq(game)) {
            game->jog_atual.flag = 0;
            game->jog_atual.n = tamanho_sequencia(game->jog_atual.coluna, game->jog_atual.pilha, game);
        } 
        else game->jog_atual.flag = -1;
        
    }
    else if (game->jog_atual.flag == 0) jogAtual_segClick(r, game);
    
}

void jogAtual_segClick(int r, JOGO *game){
    game->jog_atual.chegada = r;
    int v1 = valida_jogada_origem(game->jog_atual.pilha, game->jog_atual.coluna, game);
    int v2 = valida_jogada_destino(game);
    if (r == game->jog_atual.pilha) game->jog_atual.flag = 1;
    // preciso que no caso da chegada = saída de 1 também. 
    else if (v1 && v2) {
    game->jog_atual.flag = 1;
    } 
    else game->jog_atual.flag = -1; 
    
}

/*
  Função Auxiliar da define_jogAtual, responsável por chamar a função que calcula o tamanho da sequência (tamanho_sequencia)
  e com isso, já verifica se existem cartas consecutivas do mesmo naipe empilhadas e quantas são, e se a carta clicada é inválida
  i.e. é uma carta que não está no topo, logo não pode ser movida.  

  Bool - True(1) se a jogada é valida ;
  False (0) se a jogada é invalida - se a carta escolhida não é a topo da pilha e não faz parte de nenhuma sequência; 

*/
int evalida_tamanhoSeq(JOGO *game){
    int size = tamanho_sequencia(game->jog_atual.coluna, game->jog_atual.pilha, game);
    if(size == 1){
        if(game->jog_atual.coluna == game->tamanho_pilha[game->jog_atual.pilha] -1 ) {
            return 1;
        }
        else { return 0; }
    }
    return 1;  
}


// Se todos os foundations estão ocupados, então a pessoa ganhou o jogo; 
int ganhou_jogo(JOGO *game) {
    for (int i = 0; i < 4; i++) {
        if (game->foundations[i] == 0) return 0; 
    }

    return 1; 
}

/*
Retorna o numero da pilha, que indica se algum foundation passou a 1 - true
ou False se nenhum foundation passou a está ocupado. 
*/
int verifica_foudations(JOGO *game){
    int pilha = verifica_sequencia_inteira(game); 
    if (pilha != -1){
        if(game->matriz[pilha][game->tamanho_pilha[pilha]-1].naipe == 'C') game->foundations[0] = 1;
        else if (game->matriz[pilha][game->tamanho_pilha[pilha]-1].naipe == 'E') game->foundations[1] = 1;
        else if (game->matriz[pilha][game->tamanho_pilha[pilha]-1].naipe == 'O') game->foundations[2] = 1;
        else if (game->matriz[pilha][game->tamanho_pilha[pilha]-1].naipe == 'P') game->foundations[3] = 1;
        game->tamanho_pilha[pilha] -= 13; // Tira a sequência de 13 cartas da pilha;
        return pilha;
    }
    return -1;
}
