
#ifndef GAME_H
#define GAME_H
#include <ncurses.h>
#include "actions.h"
#include "prints.h" // É de onde a estrutura POINTERS vem


/**
 * @brief Função mestre de inicialização do jogo e da interface.
 * 
 * Chama as funções de inicialização de dados (baralho, matriz) e cria
 * as janelas visuais do ncurses, desenhando o estado inicial no ecrã.
 * 
 * @param janelas Ponteiro para a estrutura que armazena os endereços das janelas.
 * @param game Ponteiro para a estrutura principal do jogo.
 */
void init(POINTERS *janelas, JOGO *game);

/**
 * @brief Inicializa e configura a biblioteca ncurses.
 * Prepara o terminal para o jogo: ativa a leitura do rato, TO-DO
 * desativa o eco das teclas (noecho) e inicializa as cores (start_color).
 */
void ativaNcurses();

/**
 * @brief Configura o estado inicial da partida.
 * 
 * Prepara a estrutura JOGO para uma nova partida, repondo pontuações,
 * limpando o histórico de jogadas e preparando as variáveis base.
 * 
 * @param game Ponteiro para a estrutura principal do jogo onde o baralho está guardado.
 */
void start_game(JOGO *game);

/**
 * @brief Inicializa o array dos foundations a zero em todas as posições. 
 * 
 * @param game Ponteiro para a estrutura principal do jogo onde o baralho está guardado.
 */
void inicilaiza_foundations(JOGO *game);

/**
 * @brief Função Auxiliar da start_game.
 * Inicializa a struct Hint. 
 * 
 * @param game Ponteiro para a estrutura principal do jogo onde o baralho está guardado.
 */
void inicializa_hint(JOGO *game);

/**
 * @brief Função Auxiliar da start_game
 * Responsável por inicializar os naipes 
 * C - Copas  
 * E - Espadas  
 * O - Ouros  
 * P - Paus
 * 
 * @param game Ponteiro para a estrutura principal do jogo onde o baralho está guardado.
 */
void inicializa_naipes(JOGO *game);

/**
 * @brief Função Auxiliar da start_game
 * Inicializa os valores da Jogada Atual para valores predefinidos, 
 * de modo a não causar conflito posteriormente quando esses valores forem alterados.  
 * 
 * @param game Ponteiro para a estrutura principal do jogo onde o baralho está guardado.
 */
void inicializa_jogAtual(JOGO *game);

/**
 * @brief Cria e baralha as cartas no baralho principal.
 * 
 * Preenche o array do baralho com as 52 cartas (13 valores x 4 naipes)
 * e realiza o processo de baralhar aleatoriamente as posições.
 * 
 * @param game Ponteiro para a estrutura principal do jogo onde o baralho está guardado.
 */
void inicializa_baralho(JOGO *game);

/**
 * @brief Distribui as cartas do baralho para as pilhas na mesa (matriz).
 * 
 * Retira as cartas do baralho já baralhado e coloca-as nas respetivas
 * coordenadas da matriz para iniciar a partida visual.
 * 
 * @param game Ponteiro para a estrutura principal do jogo.
 */
void inicializa_matriz(JOGO *game);

/**
 * @brief Função Auxiliar da inicializa_matriz.
 * Calcula o máximo de cartas que cada pilha vai ter quando 
 * o jogo começa. 
 * Sendo as 3 primeiras com 8 cartas, cada, e as restantes descresce de 7 a 1. 
 * 
 * @param max_pilha Pointer da variável, onde deve ser guardado o valor do máximo.
 * @param i Índice da pilha que queremos descobrir o seu máximo de cartas.
 */
void define_maxdaPilha(int *max_pilha, int i);

/**
 * @brief O ciclo principal (loop) de execução do jogo.
 * 
 * Mantém o jogo a correr de forma contínua, à espera de input do utilizador
 * (cliques ou teclas), atualizando o ecrã sempre que uma ação é validada.
 * 
 * @param game Ponteiro para a estrutura principal do jogo.
 * @param janelas Ponteiro para a estrutura que contém as janelas ncurses.
 * @param jogando Variável de controlo (flag) que mantém o loop ativo (ex: 1 para jogar, 0 para sair).
 */
void loop_principal(JOGO *game, POINTERS *janelas, int jogando);

/**
 * @brief Processa os cliques do rato feitos pelo utilizador.
 * 
 * Analisa as coordenadas de onde o utilizador clicou, determina se foi numa 
 * pilha, no baralho ou num botão, e invoca a ação correspondente.
 * 
 * @param game Ponteiro para a estrutura principal do jogo.
 * @param p Ponteiro para a estrutura que guarda todas as janelas (POINTERS).
 */
void processa_rato(JOGO *game, POINTERS *p);

/**
 * @brief Lógica intermédia para processar o próximo passo do jogador.
 * 
 * Avalia o contexto da jogada após um clique numa pilha e decide o que
 * deve acontecer a seguir (ex: se o movimento avança para validação).
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas, 11 - Hint, 12 - Undo e 13 - New Game).
 * @param num_carta Linha onde foi feito o click (posição, no caso de ser uma carta, da carta na matriz).
 * @param game Ponteiro para a estrutura principal do jogo.
 * @param p Ponteiro para as janelas da interface gráfica.
 */
void next_step (int r, int num_carta, JOGO *game, POINTERS *p);

/**
 * @brief Função Auxiliar da next_step
 * A partir da informação que o click foi em uma das pilhas, inicia o 
 * processo de construir e preencher a Jogada Atual com as informações 
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas, 11 - Hint, 12 - Undo e 13 - New Game).
 * @param num_carta Linha onde foi feito o click (posição, no caso de ser uma carta, da carta na matriz).
 * @param game Ponteiro para a estrutura principal do jogo.
 * @param p Ponteiro para as janelas da interface gráfica.
 */
void naPilha(int r, int num_carta, JOGO *game, POINTERS *p);

/**
 * @brief Função que passa a flag do hint para 1, e chama a função 
 * redesenha_pilhasHint, para voltar as cartas para a cor padrão.
 * 
 * @param game Ponteiro para a estrutura principal do jogo.
 * @param p Ponteiro para as janelas da interface gráfica.
 */
void desativa_hint(JOGO *game, POINTERS *p);

/**
 * @brief Preenche a Jogada Atual.
 * Onde a flag da jog_Atual indica em que estado está a jogada.
 * (Se a flag for -2, a jogada acabou de ser inicializada,
 *  se for 0, já recebeu o primeiro click e está a espera do segundo,
 *  se for 1, já recebeu o segundo click e a jogada é válida
 *  e, por fim, se for -1, a jogada é inválida). 
 * + Primeiro click  corresponde ao click de onde queremos remover a(s) carta(s) 
 *  enquanto o segundo click corresponde a pilha para onde queremos mover essa(s) carta(s).
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas, 11 - Hint, 12 - Undo e 13 - New Game).
 * @param num_carta Linha onde foi feito o click (posição, no caso de ser uma carta, da carta na matriz).
 * @param game Ponteiro para a estrutura principal do jogo.
 */
void define_jogAtual(int r, int num_carta,  JOGO *game);

/**
 * @brief Função Auxiliar da define_jogAtual.
 * Define no caso da jog_atual está com a flag= 0, ou seja acabou de receber o 2º click
 * Preenche o parâmetro da jog_atual chamado chegada, com a pilha que foi detetado o click
 * e depois busca verificar se a jogada é possível, passando a atribuir a devida flag a jogada. 
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas, 11 - Hint, 12 - Undo e 13 - New Game).
 * @param game Ponteiro para a estrutura principal do jogo.
 */
void jogAtual_segClick(int r, JOGO *game);

/**
 * @brief Função Auxiliar da define_jogAtual, responsável por chamar a função que calcula o tamanho da sequência (tamanho_sequencia)
 * e com isso, já verifica se existem cartas consecutivas do mesmo naipe empilhadas e quantas são, e se a carta clicada é inválida
 * i.e. é uma carta que não está no topo, logo não pode ser movida. 
 * 
 * @param game Ponteiro para a estrutura principal do jogo.
 * @return int Bool 
 */
int evalida_tamanhoSeq(JOGO *game);

/**
 * @brief Função que percorre o array dos foundations, 
 * e retorna 1 se todas as posições do array têm 1(true), caso 
 * contrário, retorna 0 (false).
 * 
 * @param game Ponteiro para a estrutura principal do jogo.
 * @return int (Bool).
 */
int ganhou_jogo(JOGO *game);

/**
 * @brief Verifica com auxílio da verifica_sequencia_inteira, se existe 
 * uma sequência de Reis a Ás do mesmo naipe, e se sim, preenche a posição 
 * do naipe específico no array foundations, nesse caso entrega 1. Se não houve
 * nenhum foundation preenchido, entrega 0. 
 * 
 * @param game Ponteiro para a estrutura principal do jogo.
 * @return int (Bool).
 */
int verifica_foudations(JOGO *game);

#endif