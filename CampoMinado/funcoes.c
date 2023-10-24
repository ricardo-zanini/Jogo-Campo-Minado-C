

void mudaStatusCampoMinado(elemento_campo matriz[L][C], char status){
    for(int linha=0; linha<L; linha++){
        for(int coluna=0; coluna<C; coluna++){
            matriz[linha][coluna].status = status;
        }
    }
}

void zeraCampoMinado(elemento_campo matriz[L][C]){
     for(int linha=0; linha<L; linha++){
        for(int coluna=0; coluna<C; coluna++){
            matriz[linha][coluna].conteudo = VAZIO;
        }
    }
}

void zeraHoverCampoMinado(elemento_campo matriz[L][C]){
     for(int linha=0; linha<L; linha++){
        for(int coluna=0; coluna<C; coluna++){
            matriz[linha][coluna].hover = 0;
        }
    }
}


void geraCampoMinado(elemento_campo matriz[L][C]){
    int x_aleatorio;
    int y_aleatorio;

    for(int i = 0; i < NUMERO_BOMBAS; i++){
        do{
            x_aleatorio = rand() % C;
            y_aleatorio = rand() % L;

        }while(matriz[y_aleatorio][x_aleatorio].conteudo == -1);
        matriz[y_aleatorio][x_aleatorio].conteudo = -1;
    }

    geraNumeracaoBombas(matriz);
}


void desenhaMatriz(elemento_campo matriz[L][C], elemento_textura texturas[NUMERO_TEXTURAS][MAXIMO_DE_SPRITES]){

    Texture2D sprite_atual;
    int contador_sprite = 0;

    for(int linha=0; linha <= L + 1; linha++){
        contador_sprite++;
        for(int coluna=0; coluna <= C +1; coluna++){

            // DESENHA LATERAL MATRIZ
            if((linha == 0 || linha == L + 1) || (coluna == 0 || coluna == C + 1)){
                if(contador_sprite >= 4){
                    contador_sprite = 0;
                }

                DrawTexture(
                    texturas[SPRITE_LATERAL_MATRIZ][contador_sprite].textura,
                    (MARGEM_WIDTH_CENTER) - texturas[SPRITE_LATERAL_MATRIZ][contador_sprite].imagem.width + (linha * LADO),
                    (MARGEM_HEIGHT_CENTER) - texturas[SPRITE_LATERAL_MATRIZ][contador_sprite].imagem.height + (coluna * LADO),
                    WHITE
                );
                contador_sprite++;
            }

            if(linha < L && coluna < C){

                // Se a textura for hover, será retornado 1, que por sua vez é o índice da textura para hover na matriz de texturas
                int texturaHover = matriz[linha][coluna].hover;

                // VERIFICA STATUS DA MATRIZ
                if(matriz[linha][coluna].status == 'C'){
                    sprite_atual = texturas[SPRITE_FUNDO][texturaHover].textura;

                }else if(matriz[linha][coluna].status == 'B'){
                    sprite_atual = texturas[SPRITE_BANDEIRA][texturaHover].textura;

                }else{
                    // Se a casa for do tipo 1 a 8 (numero de bombas em volta) então procura textura nesse índice - 1
                    if(matriz[linha][coluna].conteudo >=1 || matriz[linha][coluna].conteudo <=8){
                        sprite_atual = texturas[NUMEROS_SPRITES][matriz[linha][coluna].conteudo - 1].textura;
                    }

                    if(matriz[linha][coluna].conteudo == VAZIO){
                        sprite_atual = texturas[SPRITE_VAZIO][0].textura;
                    }

                    if(matriz[linha][coluna].conteudo == BOMBA){
                        sprite_atual = texturas[SPRITE_BOMBA][0].textura;
                    }

                    if(matriz[linha][coluna].conteudo == BOMBA_RISCADA){
                        sprite_atual = texturas[SPRITE_BOMBA_RISCADA][0].textura;
                    }

                    if(matriz[linha][coluna].conteudo == BOMBA_VERMELHA){
                        sprite_atual = texturas[SPRITE_BOMBA_VERMELHA][0].textura;
                    }

                }

                DrawTexture(sprite_atual, MARGEM_WIDTH_CENTER+coluna*LADO, MARGEM_HEIGHT_CENTER+linha*LADO, WHITE);
            }
        }
    }
}



void geraNumeracaoBombas(elemento_campo matriz[L][C]){
    // For por toda a matriz
    for(int linha=0; linha<L; linha++){
        for(int coluna=0; coluna<C; coluna++){

            // Verifica se a posição atual não é uma bomba
            if(matriz[linha][coluna].conteudo != -1){
                int contador_bombas = 0;

                // For por laterais para contar bombas
                for(int linha_busca = linha - 1; linha_busca <= linha + 1; linha_busca++){
                    for(int coluna_busca = coluna - 1; coluna_busca <= coluna + 1; coluna_busca++){
                        if(matriz[linha_busca][coluna_busca].conteudo == -1
                           && (linha_busca) < L && (linha_busca) >= 0
                           && (coluna_busca) < L && (coluna_busca) >= 0) contador_bombas++;
                    }
                }

                matriz[linha][coluna].conteudo = contador_bombas;

            }
        }
     }
}
void geraFontes(Font fontes[NUMERO_FONTES]){
    fontes[0] = LoadFont("Fonts/alagard.png");
}

void abreCamposRecursiva(int linha_atual, int coluna_atual, elemento_campo matriz[L][C]){

    matriz[linha_atual][coluna_atual].status = 'A';

    for(int i=-1; i<=1; i++){

        for(int j=-1; j<=1; j++){
            if(
               (i != 0 || j != 0)
               && matriz[linha_atual + i][coluna_atual + j].conteudo >= 1
            ){
                if(linha_atual + i < L && linha_atual + i >= 0 && coluna_atual + j < C && coluna_atual + j >= 0 ){
                    matriz[linha_atual + i][coluna_atual + j].status = 'A';
                }
            }
        }
    }


    if(linha_atual - 1 >= 0 && matriz[linha_atual - 1][coluna_atual].conteudo == VAZIO && matriz[linha_atual - 1][coluna_atual].status == 'C'){
        abreCamposRecursiva(linha_atual - 1, coluna_atual, matriz);
    }

    if(linha_atual + 1 < L && matriz[linha_atual + 1][coluna_atual].conteudo == VAZIO && matriz[linha_atual + 1][coluna_atual].status == 'C'){
        abreCamposRecursiva(linha_atual + 1, coluna_atual, matriz);
    }

    if(coluna_atual - 1 >= 0 && matriz[linha_atual][coluna_atual - 1].conteudo == VAZIO && matriz[linha_atual][coluna_atual - 1].status == 'C'){
        abreCamposRecursiva(linha_atual, coluna_atual - 1, matriz);
    }

    if(coluna_atual + 1 < C && matriz[linha_atual][coluna_atual + 1].conteudo == VAZIO && matriz[linha_atual][coluna_atual + 1].status == 'C'){
        abreCamposRecursiva(linha_atual, coluna_atual + 1, matriz);
    }

}

void campoMinadoDerrota(elemento_campo matriz[L][C]){
    for(int linha=0; linha<L; linha++){
        for(int coluna=0; coluna<C; coluna++){
            if(matriz[linha][coluna].conteudo == BOMBA && matriz[linha][coluna].status != 'B'){
                matriz[linha][coluna].status = 'A';
            }
            if(matriz[linha][coluna].conteudo != BOMBA && matriz[linha][coluna].status == 'B'){
                matriz[linha][coluna].status = 'A';
                matriz[linha][coluna].conteudo = BOMBA_RISCADA;
            }
        }
    }
};

// MODIFICA A MATRIZ DO CAMPO MINADO DE ACORDO COM O CLIQUE DO USUÁRIO
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
){
    int status_aux = VITORIA;
    int foi_clicado = 0;

    if(botao_pressionado == BOTAO_ESQUERDO){
        *bandeiras_certas = 0;
        *bandeiras_erradas = 0;
        *bandeiras_escondidas = 0;
    }

    for(int linha=0; linha<L; linha++){
        for(int coluna=0; coluna<C; coluna++){
            if(matriz[linha][coluna].status != 'B' && matriz[linha][coluna].conteudo == BOMBA){
                status_aux = NORMAL;
            }
            if(
               mouse_x > (MARGEM_WIDTH_CENTER + coluna * LADO)
               && mouse_x <= (MARGEM_WIDTH_CENTER + ((coluna + 1) * LADO))
               && mouse_y > (MARGEM_HEIGHT_CENTER + linha * LADO)
               && mouse_y <= (MARGEM_HEIGHT_CENTER + ((linha + 1) * LADO))
            ){
                if(botao_pressionado == MOUSE_HOVER){
                    matriz[linha][coluna].hover = 1;

                }else if(botao_pressionado == BOTAO_ESQUERDO){
                    foi_clicado = 1;

                    if(matriz[linha][coluna].status == 'C'){

                        if(matriz[linha][coluna].conteudo == VAZIO){
                            abreCamposRecursiva(linha, coluna, matriz);

                        }else if(matriz[linha][coluna].conteudo == BOMBA){

                            matriz[linha][coluna].conteudo = BOMBA_VERMELHA;
                            matriz[linha][coluna].status = 'A';

                            status_aux = DERROTA;
                            *tela_anterior_jogo = TITLE;
                            *tela_atual_jogo = TELA_DERROTA;

                        }else{

                            matriz[linha][coluna].status = 'A';

                        }
                    }else if(matriz[linha][coluna].conteudo >= 1 && matriz[linha][coluna].status == 'A'){

                        int contador_bandeiras = 0;
                        for(int l_quadrado = -1; l_quadrado <= 1; l_quadrado++){
                            for(int c_quadrado = -1; c_quadrado <= 1; c_quadrado++){
                                if(matriz[linha + l_quadrado][coluna + c_quadrado].status == 'B'){
                                    contador_bandeiras++;
                                }
                            }
                        }

                        if(contador_bandeiras == matriz[linha][coluna].conteudo){
                            for(int l_quadrado = -1; l_quadrado <= 1; l_quadrado++){
                                for(int c_quadrado = -1; c_quadrado <= 1; c_quadrado++){
                                    if(matriz[linha + l_quadrado][coluna + c_quadrado].status != 'B' && (l_quadrado != 0 || c_quadrado != 0)){
                                        if(matriz[linha + l_quadrado][coluna + c_quadrado].conteudo == BOMBA){
                                            acaoNoCampoMinado(mouse_x + (c_quadrado * LADO), mouse_y + (l_quadrado * LADO), matriz, botao_pressionado, tela_atual_jogo, tela_anterior_jogo, status_atual_jogo, numero_bandeiras, bandeiras_certas, bandeiras_erradas, bandeiras_escondidas);
                                        }
                                        else matriz[linha + l_quadrado][coluna + c_quadrado].status = 'A';

                                    }
                                }
                            }
                        }

                    }
                }
                else if(botao_pressionado == BOTAO_DIREITO &&  matriz[linha][coluna].status != 'A'){

                    if(matriz[linha][coluna].status == 'B' && *numero_bandeiras > 0){
                        matriz[linha][coluna].status = 'C';
                        *numero_bandeiras = *numero_bandeiras - 1;

                    }else if(*numero_bandeiras < NUMERO_BOMBAS){
                        matriz[linha][coluna].status = 'B';
                        *numero_bandeiras = *numero_bandeiras + 1;
                    }

                }
            }
            // CALCULO DE VARIAVEIS DE INFORMACOES
            if(botao_pressionado == BOTAO_ESQUERDO){
                if(matriz[linha][coluna].status == 'B' && matriz[linha][coluna].conteudo == BOMBA){
                    *bandeiras_certas = *bandeiras_certas + 1;
                }
                if(matriz[linha][coluna].status == 'B' && matriz[linha][coluna].conteudo != BOMBA){
                    *bandeiras_erradas = *bandeiras_erradas + 1;
                }
                if(matriz[linha][coluna].status != 'B' && (matriz[linha][coluna].conteudo == BOMBA ||  matriz[linha][coluna].conteudo == BOMBA_VERMELHA)){
                    *bandeiras_escondidas = *bandeiras_escondidas + 1;
                }
            }
        }
    }

    if(status_aux == VITORIA && foi_clicado == 1){
        *tela_anterior_jogo = TITLE;
        *tela_atual_jogo = MENU;
    }
    *status_atual_jogo = status_aux;

}

void limpaVetorTextoInteracao( elemento_texto_interacao vetor_texto_interacao[MAXIMO_TEXTOS]){
    for(int i = 0; i < MAXIMO_TEXTOS; i++){
        strcpy(vetor_texto_interacao[i].tipo_texto.texto, "");
        vetor_texto_interacao[i].pos_x0         = 0;
        vetor_texto_interacao[i].pos_x          = 0;
        vetor_texto_interacao[i].pos_y0         = 0;
        vetor_texto_interacao[i].pos_y          = 0;
    }
}


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
){

    // LOOP POR TEXTOS GERADOS EM TELA
    for(int i = 0; i < MAXIMO_TEXTOS; i++){

        // SE ENCONTRAR POSICAO DE TEXTO VAZIO PARAR O LOOP
        if(strcmp(vetor_texto_interacao[i].tipo_texto.texto, "") == 0) break;
        if(
           vetor_texto_interacao[i].pos_x0   <= mouse_x
           && vetor_texto_interacao[i].pos_x    >= mouse_x
           && vetor_texto_interacao[i].pos_y0   <= mouse_y
           && vetor_texto_interacao[i].pos_y    >= mouse_y
        ){
            if(botao_pressionado == BOTAO_ESQUERDO){
                switch(*tela_atual_jogo){
                    case LOGO:
                    {

                    } break;
                    case TITLE:
                    {
                         if(strcmp(vetor_texto_interacao[i].tipo_texto.texto, "Sair") == 0){
                            CloseWindow();
                        }
                    } break;
                    case GAMEPLAY:
                    {

                    } break;
                    case MENU:
                    {
                        if(strcmp(vetor_texto_interacao[i].tipo_texto.texto, "Voltar") == 0){
                            *tela_atual_jogo = tela_anterior_jogo;
                        }
                        if(strcmp(vetor_texto_interacao[i].tipo_texto.texto, "Tela Inicial") == 0){
                            *tela_atual_jogo = TITLE;
                        }
                    } break;
                    default: break;
                }


                if(strcmp(vetor_texto_interacao[i].tipo_texto.texto, "Novo Jogo") == 0){
                    time(hora_inicial);

                    mudaStatusCampoMinado(matriz, 'C');
                    zeraCampoMinado(matriz);
                    geraCampoMinado(matriz);

                    *numero_bandeiras = 0;

                    *tela_atual_jogo = GAMEPLAY;
                }
                if(strcmp(vetor_texto_interacao[i].tipo_texto.texto, "Salvar Jogo") == 0){
                    salvarJogo(matriz);
                }
                if(strcmp(vetor_texto_interacao[i].tipo_texto.texto, "Carregar Jogo") == 0){
                    time(hora_inicial);

                    mudaStatusCampoMinado(matriz, 'C');
                    carregarJogo(matriz);

                    *numero_bandeiras = 0;
                    *tela_atual_jogo = GAMEPLAY;
                }
            }else if(botao_pressionado == MOUSE_HOVER){
                strcpy(texto_hover, vetor_texto_interacao[i].tipo_texto.texto);
            }
        }
    }
    limpaVetorTextoInteracao(vetor_texto_interacao);
}

void salvarJogo(elemento_campo matriz[L][C]){
    FILE *arq;
    arq = fopen(ARQUIVO_SALVAMENTO, "w");
    char separador;

    if (arq == NULL){
        CloseWindow();
        printf("\n\n --->> Erro na abertura do arquivo ");
    }else{
        for(int linha=0; linha<L; linha++){
            for(int coluna=0; coluna<C; coluna++){
                if(coluna < C-1)    separador = ';';
                else                separador = '\0';

                fprintf(arq, "%d%c", matriz[linha][coluna].conteudo, separador);
            }
            fprintf(arq, "\n");
        }
    }
}

void carregarJogo(elemento_campo matriz[L][C]){
    FILE *arq;
    arq = fopen(ARQUIVO_SALVAMENTO, "r");
    char linha_atual[C * 3];
    char *coluna_atual;
    int n_linha     = 0;
    int n_coluna    = 0;

    if (arq == NULL){
        CloseWindow();
        printf("\n\n --->> Erro na abertura do arquivo ");
    }else{

        while(!feof(arq))
        {
            if(fgets(linha_atual, sizeof(linha_atual), arq) != NULL){

                n_coluna = 0;
                coluna_atual = strtok(linha_atual,";");

                while(coluna_atual != NULL){
                    matriz[n_linha][n_coluna].conteudo = atoi(coluna_atual);
                    coluna_atual = strtok(NULL,";");
                    n_coluna++;
                }
                n_linha++;
            }
        }
    }
}


void desenhaTexto(elemento_texto_criacao texto, Font fontes[NUMERO_FONTES], elemento_texto_interacao vetor_texto_interacao[MAXIMO_TEXTOS], char texto_hover[TEXTO_TAM_50]){
    float eixo_x, eixo_y, tamanho_fonte_aux = fontes[0].baseSize*texto.tamanho;
    Vector2 tamanho_string = MeasureTextEx(fontes[0], texto.texto, tamanho_fonte_aux, 1.0f);

    switch(texto.align_x)
    {
        case 1:
        {
            eixo_x = (float) SCREEN_WIDTH - tamanho_string.x;
        } break;
        case -1:
        {
            eixo_x = 0;
        } break;
        case 0:
        {
            eixo_x = (SCREEN_WIDTH - tamanho_string.x) / 2;
        } break;
        default: break;
    }

    switch(texto.align_y)
    {
        case 1:
        {
            eixo_y = (float) SCREEN_HEIGHT- tamanho_string.y;
        } break;
        case -1:
        {
            eixo_y = 0;
        } break;
        case 0:
        {
            eixo_y = (SCREEN_HEIGHT - tamanho_string.y) / 2;
        } break;
        default: break;
    }

    // Verifica se o Texto_hover é este texto
    if(strcmp(texto.texto, texto_hover) == 0 && texto.tamanho <= 3.0f){
        texto.cor.a = 150;
    }

    DrawTextEx(fontes[0], texto.texto, (Vector2) {eixo_x + texto.pos_x, eixo_y + texto.pos_y}, tamanho_fonte_aux, fontes[0].baseSize * 0.2f, texto.cor);

    // Adiciona texto criado na listagem de textos
    for(int i = 0; i < MAXIMO_TEXTOS; i++){
        if(strcmp(vetor_texto_interacao[i].tipo_texto.texto, "") == 0){
            strcpy(vetor_texto_interacao[i].tipo_texto.texto, texto.texto);
            vetor_texto_interacao[i].pos_x0         = eixo_x + texto.pos_x;
            vetor_texto_interacao[i].pos_x          = eixo_x + texto.pos_x + tamanho_string.x;
            vetor_texto_interacao[i].pos_y0         = eixo_y + texto.pos_y;
            vetor_texto_interacao[i].pos_y          = eixo_y + texto.pos_y + tamanho_string.y;

            break;
        }
    }
}

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
){
    int contador_sprite = 0;
    int aux_loop = 0;
    char string_aux[50];
    elemento_texto_criacao texto_aux;

    if(tela_atual_jogo != LOGO){
        DrawTexture(texturas[IMAGEM_BACKGROUND][0].textura, 0, 0, WHITE);

        for(int coluna = 0; coluna <= 1; coluna++){
            for(int linha = 0; linha <= 1; linha++){
                DrawTexture(
                    texturas[SPRITE_MURO_CANTO][contador_sprite].textura,
                    linha * (SCREEN_WIDTH - texturas[SPRITE_MURO_CANTO][contador_sprite].imagem.width),
                    coluna * (SCREEN_HEIGHT - texturas[SPRITE_MURO_CANTO][contador_sprite].imagem.height),
                    WHITE
                );
                contador_sprite++;
            }
        }

        DrawTexture(texturas[SPRITE_MURO_LATERAL][0].textura, 0, (SCREEN_HEIGHT - texturas[SPRITE_MURO_LATERAL][0].imagem.height) / 2, WHITE);
        DrawTexture(texturas[SPRITE_MURO_LATERAL][1].textura, SCREEN_WIDTH - texturas[SPRITE_MURO_LATERAL][1].imagem.width, (SCREEN_HEIGHT - texturas[SPRITE_MURO_LATERAL][1].imagem.height) / 2, WHITE);
    }

    switch(tela_atual_jogo)
    {
        case LOGO:
        {

            strcpy(texto_aux.texto, "- Desenvolvido por -");
            texto_aux.align_x       = 0;
            texto_aux.align_y       = 0;
            texto_aux.pos_x         = 0;
            texto_aux.pos_y         = -150.0f;
            texto_aux.tamanho       = 5.0f;
            texto_aux.cor           = (Color) {194, 194, 194, 255};

            desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

            char devs[2][100] = {"Ricardo Zanini De Costa", "Maria Julia Carlos da Cunha"};

            aux_loop = 0;
            for(int i = -1; i <= 1; i++){
                if(i != 0){
                    strcpy(texto_aux.texto, devs[aux_loop]);
                    texto_aux.align_x       = 0;
                    texto_aux.align_y       = 0;
                    texto_aux.pos_x         = (i * 350.0f);
                    texto_aux.pos_y         = 0.0f;
                    texto_aux.tamanho       = 3.0f;
                    texto_aux.cor           = (Color) {171, 171, 171, 255};

                    desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

                    aux_loop++;
                }
            }


        } break;
        case TITLE:
        {
            strcpy(texto_aux.texto, "- Campo Minado -");
            texto_aux.align_x       = 0;
            texto_aux.align_y       = 0;
            texto_aux.pos_x         = 0;
            texto_aux.pos_y         = -150.0f;
            texto_aux.tamanho       = 9.0f;
            texto_aux.cor           = (Color) {240, 240, 240, 210};

            desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

            char opcoes[3][30] = {"Novo Jogo", "Carregar Jogo", "Sair"};
            aux_loop = 0;
            for(int i = 0; i <= 2; i++){
                strcpy(texto_aux.texto, opcoes[aux_loop]);
                texto_aux.align_x       = 0;
                texto_aux.align_y       = 0;
                texto_aux.pos_x         = 0.0f;
                texto_aux.pos_y         = (i * 100.0f);
                texto_aux.tamanho       = 3.0f;
                texto_aux.cor           = (Color) {171, 171, 171, 255};

                desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

                aux_loop++;
            }

            strcpy(texto_aux.texto, "- Campo Minado -");
            texto_aux.align_x       = 0;
            texto_aux.align_y       = 0;
            texto_aux.pos_x         = 0;
            texto_aux.pos_y         = -150.0f;
            texto_aux.tamanho       = 9.0f;
            texto_aux.cor           = (Color) {240, 240, 240, 210};

            if(*frames_animacao >= 60) *frames_animacao = 0;


            DrawTexture(texturas[SPRITE_JANELA][(int)(*frames_animacao / 15)].textura, (SCREEN_WIDTH - texturas[SPRITE_JANELA][0].imagem.width) / 2 - 700.0f, (SCREEN_HEIGHT - texturas[SPRITE_JANELA][0].imagem.height) / 2, WHITE);
            DrawTexture(texturas[SPRITE_JANELA][(int)(*frames_animacao / 15)].textura, (SCREEN_WIDTH - texturas[SPRITE_JANELA][0].imagem.width) / 2 + 700.0f, (SCREEN_HEIGHT - texturas[SPRITE_JANELA][0].imagem.height) / 2, WHITE);

        } break;
        case MENU:
        {

            char titulo_menu[15];
            Color cor_titulo;

            if(status_atual_jogo == NORMAL){
                strcpy(titulo_menu, "- MENU -");
                cor_titulo = WHITE;

            }else if(status_atual_jogo == VITORIA){
                strcpy(titulo_menu, "- Vitoria -");
                cor_titulo = (Color) {122, 207, 129, 255};

            }else if(status_atual_jogo == DERROTA){
                strcpy(titulo_menu, "- Derrota -");
                cor_titulo = (Color) {189, 79, 79, 255};
            }

            strcpy(texto_aux.texto, titulo_menu);
            texto_aux.align_x       = 0;
            texto_aux.align_y       = 0;
            texto_aux.pos_x         = 0.0f;
            texto_aux.pos_y         = -250.0f;
            texto_aux.tamanho       = 8.0f;
            texto_aux.cor           = cor_titulo;

            desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);


            char opcoes_menu[5][15] = {"Novo Jogo", "Carregar Jogo", "Salvar Jogo", "Voltar", "Tela Inicial"};
            int aux_fim = 2;
            aux_loop = 0;


            for(int i = -2; i <= aux_fim; i++){
                if(
                   (strcmp(opcoes_menu[aux_loop], "Voltar") == 0 && status_atual_jogo == NORMAL)
                   || strcmp(opcoes_menu[aux_loop], "Voltar") != 0
                ){
                    strcpy(texto_aux.texto, opcoes_menu[aux_loop]);
                    texto_aux.align_x       = 0;
                    texto_aux.align_y       = 0;
                    texto_aux.pos_x         = 0.0f;
                    texto_aux.pos_y         = (i * 100.0f) + 100.0f;
                    texto_aux.tamanho       = 3.0f;
                    texto_aux.cor           = (Color) {171, 171, 171, 255};

                    desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

                }else{
                    i--;
                    aux_fim--;
                }
                aux_loop++;
            }
        } break;
        default: break;
    }

    if(tela_atual_jogo == GAMEPLAY || tela_atual_jogo == TELA_DERROTA || tela_atual_jogo == MENU){

        // ICONE TEMPO
        DrawTexture(
            texturas[SPRITE_SCORE_TEMPO][0].textura,
            80,
            (SCREEN_HEIGHT - texturas[SPRITE_SCORE_TEMPO][0].imagem.height) / 2 - 100,
            WHITE
        );

        // DESENHA TEMPO
        if(tela_atual_jogo == GAMEPLAY || (tela_atual_jogo == MENU && status_atual_jogo == NORMAL)) time(hora_atual);

        int tempo_seg = (*hora_atual - *hora_inicial);

        sprintf(string_aux, "%02d:%02d",
                 (int)(tempo_seg / 60),
                 (int)(tempo_seg % 60)
        );

        strcpy(texto_aux.texto, string_aux);
        texto_aux.align_x       = -1;
        texto_aux.align_y       = 0;
        texto_aux.pos_x         = 150.0f;
        texto_aux.pos_y         = -100.0f;
        texto_aux.tamanho       = 2.5;
        texto_aux.cor           = (Color) {194, 194, 194, 255};

        desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

    }
    if(tela_atual_jogo == GAMEPLAY || tela_atual_jogo == TELA_DERROTA){

        // ICONE BOMBAS
        DrawTexture(
            texturas[SPRITE_SCORE_BOMBA][0].textura,
            80,
            (SCREEN_HEIGHT - texturas[SPRITE_SCORE_BOMBA][0].imagem.height) / 2,
            WHITE
        );

        // DESENHA BOMBAS
        sprintf(string_aux, "%d", NUMERO_BOMBAS);

        strcpy(texto_aux.texto, string_aux);
        texto_aux.align_x       = -1;
        texto_aux.align_y       = 0;
        texto_aux.pos_x         = 150.0f;
        texto_aux.pos_y         = 0.0f;
        texto_aux.tamanho       = 2.5;
        texto_aux.cor           = (Color) {194, 194, 194, 255};

        desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

        // ICONE BANDEIRA
        DrawTexture(
            texturas[SPRITE_SCORE_BANDEIRA][0].textura,
            80,
            (SCREEN_HEIGHT - texturas[SPRITE_SCORE_BANDEIRA][0].imagem.height) / 2 + 100,
            WHITE
        );

        // DESENHA BANDEIRA SCORE
        sprintf(string_aux, "%d / %d", *numero_bandeiras, NUMERO_BOMBAS);

        strcpy(texto_aux.texto, string_aux);
        texto_aux.align_x       = -1;
        texto_aux.align_y       = 0;
        texto_aux.pos_x         = 150.0f;
        texto_aux.pos_y         = 100.0f;
        texto_aux.tamanho       = 2.5;
        texto_aux.cor           = (Color) {194, 194, 194, 255};

        desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);
    }
    if(tela_atual_jogo == MENU && (status_atual_jogo == DERROTA || status_atual_jogo == VITORIA)){

        sprintf(string_aux, "Bandeiras Corretas: %d", bandeiras_certas);
        strcpy(texto_aux.texto, string_aux);
        texto_aux.align_x       = -1;
        texto_aux.align_y       = 0;
        texto_aux.pos_x         = 90.0f;
        texto_aux.pos_y         = -30.0f;
        texto_aux.tamanho       = 1.7;
        texto_aux.cor           = (Color) {194, 194, 194, 255};
        desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

        sprintf(string_aux, "Bandeiras Erradas: %d", bandeiras_erradas);
        strcpy(texto_aux.texto, string_aux);
        texto_aux.align_x       = -1;
        texto_aux.align_y       = 0;
        texto_aux.pos_x         = 90.0f;
        texto_aux.pos_y         = 40.0f;
        texto_aux.tamanho       = 1.7;
        texto_aux.cor           = (Color) {194, 194, 194, 255};
        desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

        sprintf(string_aux, "Bombas Nao Descobertas: %d", bandeiras_escondidas);
        strcpy(texto_aux.texto, string_aux);
        texto_aux.align_x       = -1;
        texto_aux.align_y       = 0;
        texto_aux.pos_x         = 90.0f;
        texto_aux.pos_y         = 110.0f;
        texto_aux.tamanho       = 1.7;
        texto_aux.cor           = (Color) {194, 194, 194, 255};
        desenhaTexto(texto_aux, fontes, vetor_texto_interacao, texto_hover);

    }
}
