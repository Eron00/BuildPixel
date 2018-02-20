//
// Created by Eron on 18/04/2016.
//
#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_processamentoBinario(JNIEnv *env, jobject instance, jobject FotoA, jobject FotoB, jstring cNomeProcesso){


    AndroidBitmapInfo dadosImagemFotoA,dadosImagemFotoB;                                  //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixelsFotoA,*localPixelsFotoB;                                                                    //ponteiro para referenciar os pixels da Imagem
    int coluna, linha;
    int redA,greenA,blueA;
    int redB,greenB,blueB;
    uint32_t* pixelFotoA;
    uint32_t* pixelFotoB;

    int i, j;



    const char *cNomeProcessamento =  (*env)->GetStringUTFChars(env, cNomeProcesso, 0);

    int  maiorR, maiorG, maiorB;
    maiorR = maiorG = maiorB = (int) INT64_MIN;
    int  menorR, menorG, menorB;
    menorR = menorG = menorB = (int) INT64_MAX;


    AndroidBitmap_getInfo(env, FotoA, &dadosImagemFotoA);                 //capturando as informações da imagem e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_lockPixels(env, FotoA, &localPixelsFotoA);              //capturando os dados dos pixels

    int **resultadoR = (int **) (malloc(dadosImagemFotoA.height * sizeof(int *)));
    int **resultadoG = (int **) (malloc(dadosImagemFotoA.height * sizeof(int *)));
    int **resultadoB = (int **) (malloc(dadosImagemFotoA.height * sizeof(int *)));

    for (linha = 0; linha < dadosImagemFotoA.height; linha++) {
        resultadoR[linha] =  (int *) (malloc(dadosImagemFotoA.width * sizeof(int)));
        resultadoG[linha] =  (int *) (malloc(dadosImagemFotoA.width * sizeof(int)));
        resultadoB[linha] =  (int *) (malloc(dadosImagemFotoA.width * sizeof(int)));

        for (coluna = 0; coluna < dadosImagemFotoA.width; coluna++) {
            resultadoR[linha][coluna] = 0;
            resultadoG[linha][coluna] = 0;
            resultadoB[linha][coluna] = 0;
        }
    }

    AndroidBitmap_unlockPixels(env,FotoA);                         //liberando a memoria alocada para a imagem



    AndroidBitmap_getInfo(env, FotoA, &dadosImagemFotoA);                 //capturando as informações da imagem e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_lockPixels(env, FotoA, &localPixelsFotoA);              //capturando os dados dos pixels

    AndroidBitmap_getInfo(env, FotoB, &dadosImagemFotoB);                 //capturando as informações da imagem e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_lockPixels(env, FotoB, &localPixelsFotoB);              //capturando os dados dos pixels

    for(linha = 0; linha < dadosImagemFotoA.height; linha++){
        pixelFotoA = (uint32_t*)localPixelsFotoA;                            //carregando a próxima linha de pixels da imagem
        pixelFotoB = (uint32_t*)localPixelsFotoB;


        for(coluna =0; coluna < dadosImagemFotoA.width; coluna++){

            //extração dos dados RGB do pixel
            blueA  = (int)((pixelFotoA[coluna] & 0x00FF0000) >> 16);
            greenA = (int)((pixelFotoA[coluna] & 0x0000FF00) >> 8);
            redA   = (int) (pixelFotoA[coluna] & 0x00000FF );


            //extração dos dados RGB do pixel
            blueB  = (int)((pixelFotoB[coluna] & 0x00FF0000) >> 16);
            greenB = (int)((pixelFotoB[coluna] & 0x0000FF00) >> 8);
            redB   = (int) (pixelFotoB[coluna] & 0x00000FF );



            if (strcmp(cNomeProcessamento, "TruncamentoSoma") == 0 ) {

                resultadoR[linha][coluna] = redA   + (redB + 100);
                resultadoG[linha][coluna] = greenA + (greenB + 100);
                resultadoB[linha][coluna] = blueA  + (blueB + 100);
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoSoma") == 0 ) {

                resultadoR[linha][coluna] = redA   + (redB + 200);
                resultadoG[linha][coluna] = greenA + (greenB + 200);
                resultadoB[linha][coluna] = blueA  + (blueB + 200);
            }
            if (strcmp(cNomeProcessamento, "TruncamentoSubtracao") == 0 ) {

                resultadoR[linha][coluna] = redA   - blueB;
                resultadoG[linha][coluna] = greenA - redB;
                resultadoB[linha][coluna] = blueA  - greenB;
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoSubtracao") == 0 ) {

                resultadoR[linha][coluna] = redA   - 200;
                resultadoG[linha][coluna] = greenA - 200;
                resultadoB[linha][coluna] = blueA  - 200;
            }
            if (strcmp(cNomeProcessamento, "TruncamentoMultiplicacao") == 0 ) {

                resultadoR[linha][coluna] = redA   * (redB  * 200);
                resultadoG[linha][coluna] = greenA * (greenB* 200);
                resultadoB[linha][coluna] = blueA  * (blueB * 200);
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoMultiplicacao") == 0) {

                resultadoR[linha][coluna] = redA   * (redB   * redB);
                resultadoG[linha][coluna] = greenA * (greenB * greenB);
                resultadoB[linha][coluna] = blueA  * (blueB  * blueB);
            }

            if (strcmp(cNomeProcessamento, "TruncamentoDivisao") == 0 ) {

                resultadoR[linha][coluna] = redA   / 50;
                resultadoG[linha][coluna] = greenA / 50;
                resultadoB[linha][coluna] = blueA  / 50;
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoDivisao") == 0 ) {

                resultadoR[linha][coluna] = redA   / 10;
                resultadoG[linha][coluna] = greenA / 10;
                resultadoB[linha][coluna] = blueA  / 10;
            }
            if (strcmp(cNomeProcessamento, "TruncamentoAnd") == 0 ) {

                resultadoR[linha][coluna] = redA   & (redB   + 100);
                resultadoG[linha][coluna] = greenA & (greenB + 100);
                resultadoB[linha][coluna] = blueA  & (blueB  + 100);
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoAnd") == 0){

                resultadoR[linha][coluna] = redA   & redB;
                resultadoG[linha][coluna] = greenA & greenB;
                resultadoB[linha][coluna] = blueA  & blueB;

            }
            if (strcmp(cNomeProcessamento, "TruncamentoOr") == 0) {

                resultadoR[linha][coluna] = redA   | redB;
                resultadoG[linha][coluna] = greenA | greenB;
                resultadoB[linha][coluna] = blueA  | blueB;

            }
            if (strcmp(cNomeProcessamento, "NormalizacaoOr") == 0 ) {

                resultadoR[linha][coluna] = redA   | (redB   + 150);
                resultadoG[linha][coluna] = greenA | (greenB + 150);
                resultadoB[linha][coluna] = blueA  | (blueB  + 150);
            }
            if (strcmp(cNomeProcessamento, "TruncamentoXor") == 0 ) {

                resultadoR[linha][coluna] = redA   ^ 127;
                resultadoG[linha][coluna] = greenA ^ 127;
                resultadoB[linha][coluna] = blueA  ^ 127;
            }

            if (strcmp(cNomeProcessamento, "NormalizacaoXor") == 0) {

                resultadoR[linha][coluna] = redA   ^ (127 + redB);
                resultadoG[linha][coluna] = greenA ^ (127 + greenB);
                resultadoB[linha][coluna] = blueA  ^ (127 + blueB);
            }

            if (resultadoR[linha][coluna] > maiorR) maiorR = resultadoR[linha][coluna];
            if (resultadoG[linha][coluna] > maiorG) maiorG = resultadoG[linha][coluna];
            if (resultadoB[linha][coluna] > maiorB) maiorB = resultadoB[linha][coluna];

            if (resultadoR[linha][coluna] < menorR) menorR = resultadoR[linha][coluna];
            if (resultadoG[linha][coluna] < menorG) menorG = resultadoG[linha][coluna];
            if (resultadoB[linha][coluna] < menorB) menorB = resultadoB[linha][coluna];

        }

        localPixelsFotoA = (char*)localPixelsFotoA + dadosImagemFotoA.stride;    //pulando para a proxima linha da imagem
        localPixelsFotoB = (char*)localPixelsFotoB + dadosImagemFotoB.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,FotoA);                         //liberando a memoria alocada para a imagem
    AndroidBitmap_unlockPixels(env,FotoB);                         //liberando a memoria alocada para a imagem


    char substring[5];
    memcpy((void *) cNomeProcessamento, &substring[5], 5 );
    substring[5] = '\0';


        for ( i = 0; i < dadosImagemFotoA.height; i++) {
            for (j = 0; j < dadosImagemFotoA.width; j++) {

                if (strcmp(cNomeProcessamento, "Norma"))
                {
                    resultadoR[i][j] = (int) (255.0 * (resultadoR[i][j] - menorR) / (maiorR - menorR));
                    resultadoG[i][j] = (int) (255.0 * (resultadoG[i][j] - menorG) / (maiorG - menorG));
                    resultadoB[i][j] = (int) (255.0 * (resultadoB[i][j] - menorB) / (maiorB - menorB));
                }

                if (strcmp(cNomeProcessamento, "Trunc"))
                {
                    if (resultadoR[i][j] > 255) resultadoR[i][j] = 255;
                    if (resultadoG[i][j] > 255) resultadoG[i][j] = 255;
                    if (resultadoB[i][j] > 255) resultadoB[i][j] = 255;
                    if (resultadoR[i][j] < 0) resultadoR[i][j] = 0;
                    if (resultadoG[i][j] < 0) resultadoG[i][j] = 0;
                    if (resultadoB[i][j] < 0) resultadoB[i][j] = 0;
                }
            }
        }


    AndroidBitmap_getInfo(env, FotoA, &dadosImagemFotoA);                 //capturando as informações da imagem e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_lockPixels(env, FotoA, &localPixelsFotoA);              //capturando os dados dos pixels


    for(linha = 0; linha < dadosImagemFotoA.height; linha++){
        pixelFotoA = (uint32_t*)localPixelsFotoA;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagemFotoA.width; coluna++){

            pixelFotoA[coluna] = (uint32_t)  (((resultadoR[linha][coluna] << 16)& 0x00FF0000) |
                                              ((resultadoG[linha][coluna] << 8) & 0x0000FF00) |
                                               (resultadoB[linha][coluna]       & 0x000000FF));
        }

        localPixelsFotoA = (char*)localPixelsFotoA + dadosImagemFotoA.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,FotoA);                         //liberando a memoria alocada para a imagem


}

