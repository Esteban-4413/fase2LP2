/**
 * @file prints.h
 * @author Esteban Yepez (a116272), Fernanda Cidrim (a116274), Martim Sousa (a113572)
 * @brief Declarações das funções e estruturas que tratam da parte gráfica do jogo (ncurses).
 * @version 0.1
 * @date 2026-03-22
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "actions.h"
#ifndef PRINTS_H
#define PRINTS_H
#include <ncurses.h>


// Typedef que guardará todos os endereços das janelas 

/**
 * @brief Struct construida para guardar os endereços de todas as janelas 
 * e tornar mais fácil o seu manuseio ao ultilizar o bloco como argumento 
 *  das funções, no lugar de cada um dos pointers individualmente. 
 */
typedef struct {
    WINDOW *end_pilhas[10];     /**< Array com os endereços das janelas das 10 pilhas da mesa. */
    WINDOW *end_foundations[4]; /**< Endereço das janelas do faundations  */
    WINDOW *end_hint;           /**< Endereço da janela do botão Hint. */
    WINDOW *end_undo;           /**< Endereço da janela do botão Undo. */
    WINDOW *end_ngame;          /**< Endereço da janela do botão New Game. */

} POINTERS ; 

/**
 * @brief Recebe da definição da carta, o seu naipe, ou seja um char 
 * e atribui o devido simbólo a esse char. 
 *  
 * 
 * @param naipe 
 * @return const char* endereço da memória onde fica guadado , apenas para leitura, o símbolo
 */
const char* traduzsimbolo(char naipe);

/**
 * @brief "Traduz" o valor da carta 
 * Para os casos mais éspecíficos, onde as cartas acima de 10 passam para J, Q e K 
 * e as cartas de valor 1, passam para A. 
 * 
 * @param valor endereço onde fica guardado o novo valor - um char
 * @param v valor int que vem da definição das cartas 
 */
void traduzvalor(char *valor, char v); 

/**
 * @brief Faz print na tela de uma carta inteira
 * Auxiliar da wprint_cartaInt.
 * 
 * @param win Endereço da janela onde o print será feito o print
 * @param x Coluna de onde se iniciam os prints
 * @param y Linha de onde se iniam os prints
 * @param s Simbolo da carta (já traduzido)
 * @param valor Valor da carta (já traduzido)
 */
void print_carta(WINDOW *win, int x, int y, const char *s, char valor[3]); // Auxiliar só da wprint_cartaInt

/**
 * @brief Função geral que faz print de uma crta inteira numa janela 
 * Dada a carta, chama as funções traduz_valor e traduz_simbolo, e com as informações
 * fornecidas por essas chama a print_carta. 
 * 
 * @param int f Flag que se tiver a 0 seguimos o padão de cores normal - se não podemos usar as cores do hint.
 * @param win Endereço da janela onde o print será feito o print.
 * @param x Coluna de onde se iniciam os prints.
 * @param y Linha de onde se iniam os print.
 * @param c Carta a ser mostrada no ecrã.
 */
void wprint_cartaInt(int f, WINDOW *win, int x, int y, CARTAS c);

/**
 * @brief Função geral que faz print de uma crta inteira numa janela 
 * Dada a carta, chama as funções traduz_valor e com a informação fornacida por essa 
 * faz print da carta na janela. 
 * Usada para as cartas da pilha. 
 * 
 * @param int f Flag que se tiver a 0 seguimos o padão de cores normal - se não podemos usar as cores do hint.
 * @param win Endereço da janela onde o print será feito o prin
 * @param x Coluna de onde se iniciam os print
 * @param y Linha de onde se iniam os prin
 * @param c Carta a ser mostrada no ecr
 */
void wprint_cartaTop(int f, WINDOW *win, int x, int y, CARTAS c);

/**
 * @brief Define a janela de cada uma das pilhas e já desenha as cartas
 * 
 * Cria a janela de cada uma das pilhas, e logo a seguir chama a print_nomePilha 
 * e a desenha_pilha. 
 * 
 * @param matriz matriz onde estão organizadas as cartas 
 * @param tamanho_pilha array onde é guardado o tamanho de cada uma das 10 pilhas
 * @param janela_pilha array onde estão guadados os endereços de cada uma das 10 pilhas 
 */
void definePilhas(CARTAS matriz[10][17], int tamanho_pilha[10], WINDOW *janela_pilha[]);

/**
 * @brief Faz print do nome da pilha 
 * !!Lembrando que quando faz print temos i+1, pois no jogo não é muito usual ter uma pilha 0!!
 * 
 * @param janela_pilha array onde estão guadados os endereços de cada uma das 10 pilhas 
 * @param i indice da pilha no array
 */
void print_nomePilha (WINDOW *janela_pilha[], int i);

/**
 * @brief Print das cartas de uma pilha 
 * verifica o tamanho da pilha, e sempre faz wprint_cartaTop para todas execeto a que está 
 * no topo da pilha, a esta é feito wprint_cartaInt.
 * 
 * @param janela_pilha array onde estão guadados os endereços de cada um adas 10 pilha
 * @param matriz matriz onde estão organizadas as cartas 
 * @param x_local coluna definida da DefinePilhas
 * @param y_local linha definida da DefinePilhas 
 * @param i       indice da pilha no array 
 * @param ult_carta 
 */
void desenha_pilha (WINDOW *janela_pilha[],CARTAS matriz[10][17],  int x_local, int y_local, int i, int ult_carta);


/**
 * @brief Função que cria a janela dos foundations e faz print 
 * de uma carta sem valor para representar que ainda não foi ocupado.
 * 
 * @param janela_foundations Array onde estão guardados os endereços das foundations.
 */
void defineFoundations(WINDOW *janela_foundations[
    
]); // a funcao na linha 82 de prints.c recebe como argumento o tamanho do baralho

/**
 * @brief Define a janela do botão hint 
 * É criada a janela,e depois feito print do nome do botão. 
 * 
 * @return WINDOW* Endereço da janela do botão hint
 */
WINDOW* defineButtonHint();

/**
 * @brief Define a janela do botão undo 
 * É criada a janela,e depois feito print do nome do botão. 
 * 
 * @return WINDOW* Endereço da janela do botão
 */
WINDOW* defineButtonUndo();

/**
 * @brief Define a janela do botão new game
 * É criada a janela,e depois feito print do nome do botão. 
 * 
 * @return WINDOW* Endereço da janela do botão.
 */
WINDOW* defineButtonNgame();

/**
 * @brief Função que define todas as janelas para inicialização do jogo 
 * 
 * atribui a cada um dos parâmetros do struct p, criado no main, o endereço que lá ficará
 * guardado, chamando as funções: 
 * definePilhas, defineFoundations, defineButtonUndo, defineButtonHint e defineButtonNgame.
 * 
 * @param p Pointer onde estão guadados os endereços das janelas. 
 * @param game Ponteiro para o estado atual do jogo.
 */
void define_TodasJanelas (POINTERS *p, JOGO *game);


// ----------------- HINT -----------------

/**
 * @brief  Verifica a flag do struct hint, e verifica se temos lá um hint para ser mostrado
 * e chama a função que o vai mostar (alteraCor_pilha), ou se já foi mostrado, 
 * chama a função que vai por as pilhas de volta a cor normal (desenha_pilha).
 * 
 * @param f Flag do hint que indica se o hint vai ser usado, ou já foi usado.
 * @param game Ponteiro para o estado atual do jogo.
 * @param p Pointer onde estão guadados os endereços das janelas. 
 */
void redesenha_pilhasHint(int f, JOGO *game, POINTERS *p);

/**
 * @brief Função auxiliar da redesenha_pilhasHint. 
 * Limpa o print que já havia na janela, e volta a escrever o nome da pilha, 
 * e depois chama a alteraCor_carta para fazer o print das cartas daquela pilha. 
 * 
 * 
 * @param pilha Pilha indeficada através do p_flags, de que há um hint nesta pilha.
 * @param tamanho_pilha Tamanho da pilha que queremos mudar a cor.
 * @param janela_pilha Array onde estão guardados os endereços das janelas das pilhas.
 * @param game Ponteiro para o estado atual do jogo.
 */
void alteraCor_pilha(int pilha, int tamanho_pilha, WINDOW *janela_pilha[], JOGO *game);

/**
 * @brief Função Auxiliar da alteraCor_pilha.
 * Vai verificar com auxilio do m_flags (array/matriz que está guradado no hint, dentro do game)
 * as cartas que devem ser destacadas de uma cor diferente, sendo o valor nessa linha e coluna 
 * o indicativo da cor que a carta deve ter. 
 * Se a m_flag, na posição correspondente a carta tiver com o valor 1, a carta fica verde, que indica 
 * que a carta pode ser movida para se unir a uma carta do seu mesmo naipe, se o valor for 2, ela fica
 * amarela e significa que a carta pode ser movida, mas a carta de "destino" não tem o mesmo naipe, e
 * se estiver a zero, permanece com as cores padrão. 
 * 
 * @param pilha Pilha identificada através do p_flags, de que há um hint nesta pilha.
 * @param y_local Indica a linha dentro da janela para o print ser feito. 
 * @param x_local Indica a coluna dentro da janela para o print ser feito. 
 * @param ultCarta Índice da última carta da pilha.
 * @param janela_pilha Array onde estão guardados os endereços das janelas das pilhas.
 * @param tamanho_pilha Tamanho da pilha que queremos mudar a cor.
 * @param game Ponteiro para o estado atual do jogo.
 */
void alteraCor_carta(int pilha, int y_local, int x_local, int ultCarta, WINDOW *janela_pilha[], int tamanho_pilha, JOGO *game);

/**
 * @brief Função Auxiliar da alteraCor_carta.
 * Responsável por chamar a wprint_cartaInt ou a wprint_cartaTop, com a flag
 * que indica para essas funções se deve seguir o padrão de cores ou seguirá um 
 * padrão de cores já definido(nesse caso está definido na alteraCor_carta). 
 * 
 * @param f Flag que indica o padrão de cor que será seguido.
 * @param pilha Pilha identificada através do p_flags, de que há um hint nesta pilha.
 * @param j   ìndice da carta na pilha. 
 * @param y_local Indica a linha dentro da janela para o print ser feito. 
 * @param x_local Indica a coluna dentro da janela para o print ser feito. 
 * @param ultCarta Índice da última carta da pilha.
 * @param janela_pilha Array onde estão guardados os endereços das janelas das pilhas.
 * @param game Ponteiro para o estado atual do jogo.
 */
void aux_alteraCorCarta(int f, int pilha, int j, int y_local, int x_local, int ultCarta, WINDOW *janela_pilha[], JOGO *game);

// ----------------- Atualiza as pilhas JOGADA -----------------

/**
 * @brief Função chamada após ser definida uma nova jogada
 * reponsável por chamar as funções, que vai por a piscar a selecionada a piscar 
 * ou fazer com que a mesma deixe de piscar. 
 * 
 * @param game Ponteiro para o estado atual do jogo.
 * @param p Pointer onde estão guadados os endereços das janelas.
 */
void update_pilha(JOGO *game, POINTERS *p);

/**
 * @brief Função auxiliar da update_pilha. 
 * Responsável por chamar a desenha_pilha para cada uma das pilhas
 * para fazer com que a(s) carta(s) deixem de piscar. 
 * 
 * @param pilha Pilha que vamos redesenhar.
 * @param matriz Matriz onde estão organizadas as cartas- corresponde as pilhas.
 * @param janela_pilha Array onde estão guardados os endereços das janelas das pilhas.
 * @param tamanho_pilha Tamanho da pilha que queremos mudar a cor.
 */
void redesenha_pilha(int pilha, CARTAS matriz[10][17], WINDOW *janela_pilha[], int tamanho_pilha[]);

/**
 * @brief Função auxiliar da update_pilha.
 * Determina o lim que é o índice até onde as cartas vão ser mostradas
 * sem piscar, para depois na função print_pilha, ser usado esse valor. 
 * 
 * @param game Ponteiro para o estado atual do jogo.
 * @param p Pointer onde estão guadados os endereços das janelas.
 */
void pilha_negrito(JOGO*game, POINTERS * p);

/**
 * @brief Função auxiliar da pilha_negrito.
 * Usando o lim, faz o print das cartas da pilha, das que ficam a piscar e as
 * que não ficam também. 
 * 
 * @param janela Endereço da janela onde está a pilha que vamos refazer o print.
 * @param matriz Matriz onde estão organizadas as cartas- corresponde as pilhas.
 * @param x_local Indica a coluna dentro da janela para o print ser feito. 
 * @param y_local Indica a linha dentro da janela para o print ser feito. 
 * @param i Pilha que vamos redesenhar.
 * @param lim Limite determinado pela pilha_negrito, de apartir desta carta todas ficam a piscar. 
 * @param ultCarta Índice da última carta da pilha.
 */
void print_pilha(WINDOW *janela, CARTAS matriz[10][17], int x_local, int y_local, int i, int lim, int ultCarta);

// ----------------- Atualiza FOUNDATIONS -----------------
void atualizaFoundations(JOGO *game, POINTERS *p);
void  defineCarta(CARTAS *c, int i);
void atualizaF(WINDOW *janela_foundations[], CARTAS c, int i);

#endif