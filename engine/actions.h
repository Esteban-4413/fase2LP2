
#ifndef ACTIONS_H
#define ACTIONS_H

/** @brief Número máximo de cartas por pilha . */
#define NUM_LINHAS 17

/** @brief Número de pilhas (colunas) distribuídas na mesa. */
#define NUM_COLUNAS 10

/** @brief Número máximo de jogadas que ficam guardadas no histórico para o Undo. */
#define MAX_UNDO 5

/**
 * @brief Estrutura que representa uma única carta do baralho.
 * 
 */
typedef struct {
    int valor; /**< Valor numérico da carta (ex: 1 para Ás, 11 para Valete, 12 para Dama, 13 para Rei). */
    char naipe; /**< Carácter que representa o naipe da carta (ex: 'P' paus, 'O' ouros, 'C' copas, 'E' espadas). */
} CARTAS;

/**
 * @brief Estrutura que regista os detalhes de uma jogada efetuada.
 * Utilizada para o sistema de histórico e "Desfazer" (Undo).
 *
 */
struct JOGADA {
    int pilha;    /**< Indice da pilha de onde a carta saiu. */
    int coluna;   /**< O índice da posição da carta dentro da pilha de saida. */
    int n;        /**< Número de cartas na sequência que vão ser movidas. */
    int chegada;  /**< O índice da pilha de onde a carta vai passar. */
    int flag;     /**< Inicializada a 0; -1 se a jogada não for possível */
    CARTAS carta; /**< A carta exata que foi movida durante esta jogada. */
};

/**
 * @brief Estrutura que vai guardar as informações do Hint 
 * 
 */
struct HINT{
    int flag;                             /**< Flag que indica se (-1) é que está pronto para ser usado, (1) já foi usado, e 0 vazio. */
    int m_flags[NUM_COLUNAS][NUM_LINHAS]; /**< Array de ints que corresponde a cada carta da matriz e tem 1 se carta fica azul e 2 se amarela, e por fim 0 se fica normal. */
    int p_flags[NUM_COLUNAS];             /**< Array de ints que indica para cada pilha, 0 se não tem cartas jogáveis na pilha, e 1 se tem cartas jogávis na pilha. */
} ;

/**
 * @brief Estrutura principal que guarda todo o estado atual da partida.
 * 
 */
typedef struct {
    char naipes[4];                         /**< Array com os caracteres dos 4 naipes possíveis. */
    CARTAS baralho[52];                     /**< O baralho principal (monte de onde se tiram cartas). */
    int tamanho_baralho;                    /**< Número de cartas que ainda restam no baralho principal. */
    CARTAS matriz[NUM_COLUNAS][NUM_LINHAS]; /**< A matriz que representa as cartas espalhadas na mesa. */
    int tamanho_pilha[NUM_COLUNAS];         /**< Array que guarda o número atual de cartas em cada uma das 10 pilhas. */
    int foundations[4];                     /**< Array de flags, que indicam se as foundations já foram preenchidas */
    struct JOGADA jog_atual;
    struct JOGADA historial[MAX_UNDO];      /**< Array que guarda as últimas jogadas feitas para o sistema de Undo. */
    int jogadas_historial;                 /**< Número atual de jogadas guardadas no histórico. */
    struct HINT hint;                      /**< Informações sobre o Hint.*/
} JOGO;


/**
 * @brief Verifica se a carta selecionada é possível de ser movida
 * 
 * @param r O identificador numérico da zona clicada (0-10 para as pilhas).
 * @param game Ponteiro para o estado atual do jogo.
 * @return int Retorna 1 se a jogada for válida, ou 0 se for inválida.
 */
int valida_jogada_origem(int y, int x, JOGO *game);


/**
 * @brief Valida se o movimento selecionado pelo jogador é possível.
 * Verificando se a carta no topo da pilha para o qual queremos mover é
 * um valor acima da que vamos por na pilha. 
 * 
 * @param game Ponteiro para o estado atual do jogo.
 * @return int (Bool).
 */
int valida_jogada_destino(JOGO *game);


/**
 * @brief Retira a(s) cartas da pilha de origem para 
 * o fim da pilha de chegada, na matriz. 
 * 
 * @param y Índice da pilha de origem. 
 * @param x Posição da carta /ou da primeira carta na pilha de origem.
 * @param y2 Índice da pilha de chegada. 
 * @param x2 Primeira posição vazia nap pilha de chegada. 
 * @param game Ponteiro para o estado atual do jogo.
 */
void joga(int y, int x, int y2, int x2, JOGO *game);


/**
 * @brief Função que a partir de um y(pilha) e um x (cposição de uma carta
 * específica na pilha) verifica o tamanho da sequência de cartas abaixo dela
 * que podem ser movidas como um combo, ou seja, quantas cartas abaixo dessa tem 
 * o mesmo naipe e o seu valor decresce um da anterio. 
 * 
 * @param x Posição da carta /ou da primeira carta na pilha de origem.
 * @param y Índice da pilha de origem. 
 * @param game Ponteiro para o estado atual do jogo.
 * @return int Tamanho da sequência (retorna 1 quando não há sequência). 
 */
int tamanho_sequencia(int x, int y, JOGO *game);

/**
 * @brief Verifica se existe em alguma das pilhas uma sequencia completa
 * (Uma sequancia de Rei a Ás do mesmo naipe), e também se essa sequência 
 * chega ao fim da pilha. 
 * 
 * @param game Ponteiro para o estado atual do jogo.
 * @return int Pilha onde existe a sequência ou (-1) se não existir nenhuma pilha com uma sequência completa.  
 */
int verifica_sequencia_inteira(JOGO *game); 

/**
 * @brief Fornece uma dica (hint) ao jogador.
 * Analisa a mesa para encontrar uma carta que possa ser validamente movida
 * para o descarte e destaca-a visualmente.
 * 
 * @param game Ponteiro para o estado atual do jogo.
 */
void hint(JOGO *game);

/**
 * @brief Auxiliar da hint. 
 * Percorre para cada carta a procura, nas outra pilhas se existe uma carta no topo,
 * um valor acima desta. No caso de ser do mesmo naipe coloca a flag, na carta para 1 
 * que indica que a carta será mostrada a verde. E se a carta de destino encontrada 
 * for de um naipe diferente, coloca a flag da carta de origem a 2, que indica que 
 * ficará amarela. 
 * 
 * @param y Índice da pilha a ser verificada.
 * @param x Índice da carta na pilha y. 
 * @param game Ponteiro para o estado atual do jogo.
 * @param flag Indica se existe alguma jogada possível na pilha. 
 */
void procura_destino(int y, int x, JOGO *game, int *flag); 

/**
 * @brief Função que verifica se existe alguma jogada possível 
 * para ser mostrada no hint, ao percorrer o array p_flags e verificar 
 * se em alguma posição está um 1, que indica que existe carta para
 * para ser movida na pilha. 
 * 
 * @param game Ponteiro para o estado atual do jogo.
 * @return int Bool
 */
int temHint(JOGO *game);


/**
 * @brief Regista uma jogada no histórico para permitir o "Desfazer" (Undo).
 * 
 * @param game Ponteiro para o estado atual do jogo.
 */
void registar_jogada(JOGO *game);

/**
 * @brief Desfaz a última jogada realizada pelo jogador.
 * Verifica se é possível voltar atrás a jogada- se não retorna uma mensagem, 
 * e se for possível chama a aux_undo que faz toda a parte de devolver as cartas
 * de onde vieram.
 * 
 * @param game Ponteiro para o estado atual do jogo.
 */
void undo(JOGO *game);

/**
 * @brief Auxiliar do undo
 * Onde está a lógica do undo, para o caso de ser possível retroceder uma jogada, 
 * Lê a última() entrada do histórico e reverte o movimento da(s) carta(s),
 * devolvendo-a à sua posição original.
 * 
 * @param game 
 */
void aux_undo(JOGO *game);

/**
 * @brief Reinicia a partida e prepara um novo jogo.
 * Baralha as cartas, limpa o histórico, redefine os montes e
 * distribui as cartas novamente pela matriz da mesa.
 * 
 * @param game Ponteiro para o estado atual do jogo.
 */
void novo_jogo(JOGO *game);


#endif

