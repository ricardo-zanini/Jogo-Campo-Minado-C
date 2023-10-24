void geraTexturas(elemento_textura texturas[NUMERO_TEXTURAS][MAXIMO_DE_SPRITES]){

    Image imagem_aux;
    int brilho_hover = 50;

    imagem_aux = LoadImage("Sprites/background.png");
    texturas[IMAGEM_BACKGROUND][0].imagem = imagem_aux;
    texturas[IMAGEM_BACKGROUND][0].textura = LoadTextureFromImage(imagem_aux);

    ImageColorContrast(&imagem_aux, -30);
    ImageColorBrightness(&imagem_aux, -30);
    texturas[IMAGEM_BACKGROUND][1].imagem = imagem_aux;
    texturas[IMAGEM_BACKGROUND][1].textura = LoadTextureFromImage(imagem_aux);

    // ============= SPRITES CAMPO =============

    imagem_aux = LoadImage("Sprites/bandeira.png");
    texturas[SPRITE_BANDEIRA][0].imagem = imagem_aux;
    texturas[SPRITE_BANDEIRA][0].textura = LoadTextureFromImage(imagem_aux);

    ImageColorBrightness(&imagem_aux, brilho_hover);
    texturas[SPRITE_BANDEIRA][1].imagem = imagem_aux;
    texturas[SPRITE_BANDEIRA][1].textura = LoadTextureFromImage(imagem_aux);


    imagem_aux = LoadImage("Sprites/bomba.png");
    texturas[SPRITE_BOMBA][0].imagem = imagem_aux;
    texturas[SPRITE_BOMBA][0].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/bomba_riscada.png");
    texturas[SPRITE_BOMBA_RISCADA][0].imagem = imagem_aux;
    texturas[SPRITE_BOMBA_RISCADA][0].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/bomba_vermelha.png");
    texturas[SPRITE_BOMBA_VERMELHA][0].imagem = imagem_aux;
    texturas[SPRITE_BOMBA_VERMELHA][0].textura = LoadTextureFromImage(imagem_aux);


    imagem_aux = LoadImage("Sprites/fundo.png");
    texturas[SPRITE_FUNDO][0].imagem = imagem_aux;
    texturas[SPRITE_FUNDO][0].textura = LoadTextureFromImage(imagem_aux);

    ImageColorBrightness(&imagem_aux, brilho_hover);
    texturas[SPRITE_FUNDO][1].imagem = imagem_aux;
    texturas[SPRITE_FUNDO][1].textura = LoadTextureFromImage(imagem_aux);



    imagem_aux = LoadImage("Sprites/vazio.png");
    texturas[SPRITE_VAZIO][0].imagem = imagem_aux;
    texturas[SPRITE_VAZIO][0].textura = LoadTextureFromImage(imagem_aux);

    ImageColorBrightness(&imagem_aux, brilho_hover);
    texturas[SPRITE_VAZIO][1].imagem = imagem_aux;
    texturas[SPRITE_VAZIO][1].textura = LoadTextureFromImage(imagem_aux);




    imagem_aux = LoadImage("Sprites/numero_1.png");
    texturas[NUMEROS_SPRITES][0].imagem = imagem_aux;
    texturas[NUMEROS_SPRITES][0].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/numero_2.png");
    texturas[NUMEROS_SPRITES][1].imagem = imagem_aux;
    texturas[NUMEROS_SPRITES][1].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/numero_3.png");
    texturas[NUMEROS_SPRITES][2].imagem = imagem_aux;
    texturas[NUMEROS_SPRITES][2].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/numero_4.png");
    texturas[NUMEROS_SPRITES][3].imagem = imagem_aux;
    texturas[NUMEROS_SPRITES][3].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/numero_5.png");
    texturas[NUMEROS_SPRITES][4].imagem = imagem_aux;
    texturas[NUMEROS_SPRITES][4].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/numero_6.png");
    texturas[NUMEROS_SPRITES][5].imagem = imagem_aux;
    texturas[NUMEROS_SPRITES][5].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/numero_7.png");
    texturas[NUMEROS_SPRITES][6].imagem = imagem_aux;
    texturas[NUMEROS_SPRITES][6].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/numero_8.png");
    texturas[NUMEROS_SPRITES][7].imagem = imagem_aux;
    texturas[NUMEROS_SPRITES][7].textura = LoadTextureFromImage(imagem_aux);

    // Canto esquerdo superior
    imagem_aux = LoadImage("Sprites/muro_canto.png");
    texturas[SPRITE_MURO_CANTO][0].imagem = imagem_aux;
    texturas[SPRITE_MURO_CANTO][0].textura = LoadTextureFromImage(imagem_aux);

    // Canto direito superior
    ImageFlipHorizontal(&imagem_aux);
    texturas[SPRITE_MURO_CANTO][1].imagem = imagem_aux;
    texturas[SPRITE_MURO_CANTO][1].textura = LoadTextureFromImage(imagem_aux);

    // Canto esquerdo inferior
    ImageFlipHorizontal(&imagem_aux);
    ImageFlipVertical(&imagem_aux);
    texturas[SPRITE_MURO_CANTO][2].imagem = imagem_aux;
    texturas[SPRITE_MURO_CANTO][2].textura = LoadTextureFromImage(imagem_aux);

    // Canto direito inferior
    ImageFlipHorizontal(&imagem_aux);
    texturas[SPRITE_MURO_CANTO][3].imagem = imagem_aux;
    texturas[SPRITE_MURO_CANTO][3].textura = LoadTextureFromImage(imagem_aux);


    imagem_aux = LoadImage("Sprites/muro_lateral.png");
    texturas[SPRITE_MURO_LATERAL][0].imagem = imagem_aux;
    texturas[SPRITE_MURO_LATERAL][0].textura = LoadTextureFromImage(imagem_aux);

    ImageFlipHorizontal(&imagem_aux);
    texturas[SPRITE_MURO_LATERAL][1].imagem = imagem_aux;
    texturas[SPRITE_MURO_LATERAL][1].textura = LoadTextureFromImage(imagem_aux);



    imagem_aux = LoadImage("Sprites/lateral_matriz_1.png");
    texturas[SPRITE_LATERAL_MATRIZ][0].imagem = imagem_aux;
    texturas[SPRITE_LATERAL_MATRIZ][0].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/lateral_matriz_2.png");
    texturas[SPRITE_LATERAL_MATRIZ][1].imagem = imagem_aux;
    texturas[SPRITE_LATERAL_MATRIZ][1].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/lateral_matriz_3.png");
    texturas[SPRITE_LATERAL_MATRIZ][2].imagem = imagem_aux;
    texturas[SPRITE_LATERAL_MATRIZ][2].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/lateral_matriz_4.png");
    texturas[SPRITE_LATERAL_MATRIZ][3].imagem = imagem_aux;
    texturas[SPRITE_LATERAL_MATRIZ][3].textura = LoadTextureFromImage(imagem_aux);



    imagem_aux = LoadImage("Sprites/score_trofeu.png");
    texturas[SPRITE_SCORE_TROFEU][0].imagem = imagem_aux;
    texturas[SPRITE_SCORE_TROFEU][0].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/score_bomba.png");
    texturas[SPRITE_SCORE_BOMBA][0].imagem = imagem_aux;
    texturas[SPRITE_SCORE_BOMBA][0].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/score_tempo.png");
    texturas[SPRITE_SCORE_TEMPO][0].imagem = imagem_aux;
    texturas[SPRITE_SCORE_TEMPO][0].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/score_bandeira.png");
    texturas[SPRITE_SCORE_BANDEIRA][0].imagem = imagem_aux;
    texturas[SPRITE_SCORE_BANDEIRA][0].textura = LoadTextureFromImage(imagem_aux);


    imagem_aux = LoadImage("Sprites/espadas.png");
    texturas[SPRITE_ESPADAS][0].imagem = imagem_aux;
    texturas[SPRITE_ESPADAS][0].textura = LoadTextureFromImage(imagem_aux);

    ImageFlipHorizontal(&imagem_aux);
    texturas[SPRITE_ESPADAS][1].imagem = imagem_aux;
    texturas[SPRITE_ESPADAS][1].textura = LoadTextureFromImage(imagem_aux);


    imagem_aux = LoadImage("Sprites/janela_1.png");
    texturas[SPRITE_JANELA][0].imagem = imagem_aux;
    texturas[SPRITE_JANELA][0].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/janela_2.png");
    texturas[SPRITE_JANELA][1].imagem = imagem_aux;
    texturas[SPRITE_JANELA][1].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/janela_3.png");
    texturas[SPRITE_JANELA][2].imagem = imagem_aux;
    texturas[SPRITE_JANELA][2].textura = LoadTextureFromImage(imagem_aux);

    imagem_aux = LoadImage("Sprites/janela_4.png");
    texturas[SPRITE_JANELA][3].imagem = imagem_aux;
    texturas[SPRITE_JANELA][3].textura = LoadTextureFromImage(imagem_aux);

}
