
// ============== || FUNCOES || ==============

#include "funcoes.h"

// ============== || MAIN DO JOGO || ==============

int main(void)
{

    // MUSICA JOGO

    InitAudioDevice();              // Initialize audio device

    Music music = LoadMusicStream("Musicas/musicaFundo.mp3");

    PlayMusicStream(music);

    // TEMPO INICIAL E TEMPO ATUAL
    time_t hora_inicial, hora_atual;

    time(&hora_inicial);

    // SEED DE NUMERO ALEATORIO
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Campo Minado");
    SetTargetFPS(60);

    // SETA MONITOR PARA FULLSCREEN
    const int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    ToggleFullscreen();

    // GERA O VETOR DE TEXTURAS
    geraTexturas(texturas);

    // GERA O VETOR DE FONTES
    geraFontes(fontes);

    // SETA TODAS MINAS PARA STATUS C (COBERTO)
    mudaStatusCampoMinado(matriz, 'C');

    // SETA TODAS POSICOES PARA VAZIO
    zeraCampoMinado(matriz);
    zeraHoverCampoMinado(matriz);

    // GERA A MATRIZ ALEATORIA DO CAMPO
    geraCampoMinado(matriz);

    // FRAMES DA TELA DE LOGO
    int framesLogo = 0;
    int framesDerrota  = 0;

    // STATUS DO CAMPO MINADO
    status_jogo status_atual_jogo = NORMAL;

    // NUMERO BANDEIRAS
    int numero_bandeiras = 0;
    int bandeiras_certas = 0;
    int bandeiras_erradas = 0;
    int bandeiras_escondidas = 0;

    // TEXTO EM HOVER ATUAL
    char texto_hover[TEXTO_TAM_50];

    int frames_animacao = 0;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        // DESABILITA FECHAMENTO DA JANELA PELO ESC
        SetExitKey(KEY_NULL);

        // DESCOBRE QUAL EH A TELA DO JOGO
        switch(tela_atual_jogo)
        {
            case LOGO:
            {
                framesLogo++;
                if (framesLogo > (60 * 3.5)) tela_atual_jogo = TITLE;
            } break;
            case GAMEPLAY:
            {
                framesDerrota  = 0;
                if (IsKeyPressed(KEY_ESC) ){
                    tela_anterior_jogo = tela_atual_jogo;
                    tela_atual_jogo = MENU;
                }
            } break;
            case TELA_DERROTA:
            {
                framesDerrota++;
                if (framesDerrota > (60 * 5)) {
                    tela_atual_jogo = MENU;
                    status_atual_jogo = DERROTA;
                }
            } break;
            default: break;
        }
        frames_animacao++;

        // ZERA TEXTOS CLICADOS
        limpaVetorTextoInteracao(vetor_texto_interacao);

        BeginDrawing();

            ClearBackground(COR_CINZA_1);

            desenhaTexturasGerais(texturas, tela_atual_jogo, fontes, vetor_texto_interacao, &hora_inicial, &hora_atual, &numero_bandeiras, bandeiras_certas, bandeiras_erradas, bandeiras_escondidas, status_atual_jogo, texto_hover, &frames_animacao);

            // EXECUTA DIFERENTES ACOES DEPENDENDO DA TELA ATUAL
            switch(tela_atual_jogo)
            {
                case TITLE:
                {
                    mudaStatusCampoMinado(matriz, 'C');
                } break;
                case GAMEPLAY:
                {

                    // DESENHA As MATRIZ EM TELA
                    desenhaMatriz(matriz, texturas);

                    zeraHoverCampoMinado(matriz);

                    // AÇÕES DO USUÁRIO
                    if(IsMouseButtonPressed(BOTAO_ESQUERDO)){
                        acaoNoCampoMinado(GetMouseX(), GetMouseY(), matriz, BOTAO_ESQUERDO, &tela_atual_jogo, &tela_anterior_jogo, &status_atual_jogo, &numero_bandeiras, &bandeiras_certas, &bandeiras_erradas, &bandeiras_escondidas);
                    }else if(IsMouseButtonPressed(BOTAO_DIREITO)){
                        acaoNoCampoMinado(GetMouseX(), GetMouseY(), matriz, BOTAO_DIREITO, &tela_atual_jogo, &tela_anterior_jogo, &status_atual_jogo, &numero_bandeiras, &bandeiras_certas, &bandeiras_erradas, &bandeiras_escondidas);
                    }else{
                        acaoNoCampoMinado(GetMouseX(), GetMouseY(), matriz, MOUSE_HOVER, &tela_atual_jogo, &tela_anterior_jogo, &status_atual_jogo, &numero_bandeiras, &bandeiras_certas, &bandeiras_erradas, &bandeiras_escondidas);
                    }

                } break;
                case TELA_DERROTA:
                {
                    campoMinadoDerrota(matriz);
                    zeraHoverCampoMinado(matriz);
                    desenhaMatriz(matriz, texturas);

                } break;
                default: break;
            }

            // LIMPA TEXTO EM HOVER
            strcpy(texto_hover, "");

            // VERIFICA O CLIQUE EM TEXTOS
            if(IsMouseButtonPressed(BOTAO_ESQUERDO)){
                cliqueEmTextos(GetMouseX(), GetMouseY(), vetor_texto_interacao, &tela_atual_jogo, matriz, tela_anterior_jogo, BOTAO_ESQUERDO, &hora_inicial, &numero_bandeiras, texto_hover);
            }else{
                cliqueEmTextos(GetMouseX(), GetMouseY(), vetor_texto_interacao, &tela_atual_jogo, matriz, tela_anterior_jogo, MOUSE_HOVER, &hora_inicial, &numero_bandeiras, texto_hover);
            }

        EndDrawing();

    }

    CloseWindow();

    return 0;

}
