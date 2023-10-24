// ============== || BIBLIOTECAS || ==============

#include "raylib.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// ============== || CONSTANTES GLOBAIS || ==============

const char ARQUIVO_SALVAMENTO[23] = "arquivo_salvamento.txt";

#define C 20
#define L C

#define KEY_ESC 256

#define NUMERO_BOMBAS 40

#define LADO 40

#define SCREEN_HEIGHT GetScreenHeight()
#define SCREEN_WIDTH GetScreenWidth()

#define MARGEM_WIDTH_CENTER round((SCREEN_WIDTH - (C * LADO))/ 2)
#define MARGEM_HEIGHT_CENTER round((SCREEN_HEIGHT - (L * LADO)) / 2)

#define BOTAO_ESQUERDO 0
#define BOTAO_DIREITO  1
#define MOUSE_HOVER    2

// ============== || DEFINICAO DE CORES ||
// Quanto menor o número, mais escuro

#define COR_CINZA_1 (Color) {43, 43, 43, 255}
#define COR_CINZA_2 (Color) {61, 61, 61, 255}
#define COR_VERMELHO_3 (Color) {222, 71, 71, 255}

// ============== || DEFINICAO DOS SPRITES || ==============

#define MAXIMO_DE_SPRITES          20

#define NUMEROS_SPRITES            0
#define SPRITE_BANDEIRA            1
#define SPRITE_BOMBA               2
#define SPRITE_BOMBA_VERMELHA      3
#define SPRITE_BOMBA_RISCADA       4
#define SPRITE_FUNDO               5
#define SPRITE_VAZIO               6

#define SPRITE_MURO_CANTO          7
#define SPRITE_MURO_LATERAL        8

#define SPRITE_LATERAL_MATRIZ      9

#define SPRITE_SCORE_TEMPO         10
#define SPRITE_SCORE_TROFEU        11
#define SPRITE_SCORE_BOMBA         12
#define SPRITE_SCORE_BANDEIRA      13

#define SPRITE_ESPADAS             14

#define SPRITE_JANELA              15

#define IMAGEM_BACKGROUND          16

#define NUMERO_TEXTURAS 17

// ============== || CAMPO MINADO EM SÍ || ==============

// ESTRUTURA DE CADA ELEMENTO DA MATRIZ
// CONTEÚDO: -2 A 8 (-3 É A BOMBA CLICADA PARA DERROTA, -2 É A BOMBA RISCADA, -1 É A BOMBA, 0 É VAZIO)
// STATUS: C (COBERTA), A (ABERTA), B (BANDEIRA)
// HOVER: 1 PARA TRUE E 0 PARA FALSE (IDENTIFICA SE O MOUSE ESTA SOBRE O ELEMENTO)

#define BOMBA_VERMELHA  -3
#define BOMBA_RISCADA   -2
#define BOMBA           -1
#define VAZIO           0

typedef struct
{
    int conteudo;
    char status;
    int hover;
} elemento_campo;

// MATRIZ
elemento_campo matriz [L][C];


// ============== || MATRIZ DE TEXTURAS || ==============

// O PRIMEIRO ÍNDICE DA MATRIZ DIZ QUAL O SPRITE ATUAL, E O SEGUNDO SE REFERE AS VARIACOES DE UM MESMO SPRITE
// (Usado principalmente em animacoes)

typedef struct
{
    Texture2D   textura;
    Image       imagem;
} elemento_textura;

elemento_textura texturas[NUMERO_TEXTURAS][MAXIMO_DE_SPRITES];

// ============== || MATRIZ DE FONTES|| ==============

#define NUMERO_FONTES 1
Font fontes[NUMERO_FONTES];

// ============== || STRUCT DE TEXTOS || ==============

// Os atributos "align_x" e "align_y" podem ser declarados como -1, 0 e 1
// Os atributos "pos_x" e "pos_y" sao usados para adicionar ou remover pixels no espacamento ja setado com o attr align
// Exemplo: Se declar o align como 0, 0 e um pos_x de -100.0f, o texto deve aparecer no centro da tela, 100 pixels à esquerda

typedef struct
{
    char        texto[100];
    int         align_x;
    int         align_y;
    float       pos_x;
    float       pos_y;
    float       tamanho;
    Color       cor;
} elemento_texto_criacao ;

// ============== || VARIAVEIS DE SELECAO DE TELA|| ==============

typedef enum tela_jogo { LOGO = 0, TITLE, GAMEPLAY, MENU, TELA_DERROTA} tela_jogo;

tela_jogo tela_atual_jogo = LOGO;
tela_jogo tela_anterior_jogo = LOGO;

// ============== || VETOR DE TODOS OS TEXTOS || ==============

#define TEXTO_TAM_50 50

typedef struct
{
    char    texto[TEXTO_TAM_50];
    int     hover
} elemento_todos_textos ;

elemento_todos_textos matriz_todos_textos;

// ============== || VETOR DE TEXTOS EM TELA || ==============

typedef struct
{
    elemento_texto_criacao          tipo_texto;
    float                   pos_x0;
    float                   pos_x;
    float                   pos_y0;
    float                   pos_y;
} elemento_texto_interacao ;

#define MAXIMO_TEXTOS 6

elemento_texto_interacao vetor_texto_interacao[MAXIMO_TEXTOS];

// ============== || STATUS DO JOGO || ==============

typedef enum status_jogo { NORMAL = 0, VITORIA, DERROTA} status_jogo;



// ============== || INCLUDE DAS FUNCOES|| ==============

// DECLARAÇÃO DOS PROTÓTIPOS

void geraTexturas(elemento_textura texturas[NUMERO_TEXTURAS][MAXIMO_DE_SPRITES])

#include "texturas.c"

// DECLARAÇÃO DOS PROTÓTIPOS

void mudaStatusCampoMinado(elemento_campo matriz[L][C], char status);

void zeraCampoMinado(elemento_campo matriz[L][C]);

void zeraHoverCampoMinado(elemento_campo matriz[L][C]);

void geraCampoMinado(elemento_campo matriz[L][C]);

void desenhaMatriz(elemento_campo matriz[L][C], elemento_textura texturas[NUMERO_TEXTURAS][MAXIMO_DE_SPRITES]);

void geraNumeracaoBombas(elemento_campo matriz[L][C]);

void geraFontes(Font fontes[NUMERO_FONTES]);

void abreCamposRecursiva(int linha_atual, int coluna_atual, elemento_campo matriz[L][C]);

void campoMinadoDerrota(elemento_campo matriz[L][C]);

void acaoNoCampoMinado(
            int mouse_x,
            int mouse_y,
            elemento_campo matriz[L][C],
            int botao_pressionado,
            tela_jogo *tela_atual_jogo,
            tela_jogo *tela_anterior_jogo,
            status_jogo *status_atual_jogo,
            int *numero_bandeiras,
            int *bandeiras_certas,
            int *bandeiras_erradas,
            int *bandeiras_escondidas
);

void limpaVetorTextoInteracao( elemento_texto_interacao vetor_texto_interacao[MAXIMO_TEXTOS]);

void cliqueEmTextos(
        int mouse_x,
        int mouse_y,
        elemento_texto_interacao vetor_texto_interacao[MAXIMO_TEXTOS],
        tela_jogo *tela_atual_jogo,
        elemento_campo matriz[L][C],
        tela_jogo tela_anterior_jogo,
        int botao_pressionado,
        time_t *hora_inicial,
        int *numero_bandeiras,
        char texto_hover[TEXTO_TAM_50]
);

void salvarJogo(elemento_campo matriz[L][C]);

void carregarJogo(elemento_campo matriz[L][C]);

void desenhaTexto(elemento_texto_criacao texto, Font fontes[NUMERO_FONTES], elemento_texto_interacao vetor_texto_interacao[MAXIMO_TEXTOS], char texto_hover[TEXTO_TAM_50]);

void desenhaTexturasGerais(
        elemento_textura texturas[NUMERO_TEXTURAS][MAXIMO_DE_SPRITES],
        tela_jogo tela_atual_jogo,
        Font fontes[NUMERO_FONTES],
        elemento_texto_interacao vetor_texto_interacao[MAXIMO_TEXTOS],
        time_t *hora_inicial,
        time_t *hora_atual,
        int *numero_bandeiras,
        int bandeiras_certas,
        int bandeiras_erradas,
        int bandeiras_escondidas,
        status_jogo status_atual_jogo,
        char texto_hover[TEXTO_TAM_50],
        int *frames_animacao
);

#include "funcoes.c"


