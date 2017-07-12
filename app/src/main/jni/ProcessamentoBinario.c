//
// Created by Eron on 18/04/2016.
//
#include <jni.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_processamentoBinario(JNIEnv *env, jobject instance, jintArray FotoA_, jintArray FotoB_, jint linha, jint coluna,jstring cNomeProcesso){

    int i, j;

    float **RedA =       (int **) (malloc(linha * sizeof(int *)));
    float **BlueA =      (int **) (malloc(linha * sizeof(int *)));
    float **GreenA =     (int **) (malloc(linha * sizeof(int *)));
    float **RedB =       (int **) (malloc(linha * sizeof(int *)));
    float **BlueB =      (int **) (malloc(linha * sizeof(int *)));
    float **GreenB =     (int **) (malloc(linha * sizeof(int *)));
    float **resultadoR = (int **) (malloc(linha * sizeof(int *)));
    float **resultadoG = (int **) (malloc(linha * sizeof(int *)));
    float **resultadoB = (int **) (malloc(linha * sizeof(int *)));

    for (i = 0; i < linha; i++) {
        RedA[i] =        (int *) (malloc(coluna * sizeof(int)));
        BlueA[i] =       (int *) (malloc(coluna * sizeof(int)));
        GreenA[i] =      (int *) (malloc(coluna * sizeof(int)));
        RedB[i] =        (int *) (malloc(coluna * sizeof(int)));
        BlueB[i] =       (int *) (malloc(coluna * sizeof(int)));
        GreenB[i] =      (int *) (malloc(coluna * sizeof(int)));
        resultadoR[i] =  (int *) (malloc(coluna * sizeof(int)));
        resultadoG[i] =  (int *) (malloc(coluna * sizeof(int)));
        resultadoB[i] =  (int *) (malloc(coluna * sizeof(int)));
    }


    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            RedA[i][j]       = 0;
            GreenA[i][j]     = 0;
            BlueA[i][j]      = 0;
            RedB[i][j]       = 0;
            GreenB[i][j]     = 0;
            BlueB[i][j]      = 0;
            resultadoR[i][j] = 0;
            resultadoG[i][j] = 0;
            resultadoB[i][j] = 0;
        }
    }

    jint *valorPixelA;
    valorPixelA = (*env)->GetIntArrayElements(env, FotoA_, NULL);
    int *pixelA = valorPixelA;

    jint *valorPixelB;
    valorPixelB = (*env)->GetIntArrayElements(env, FotoB_, NULL);
    int *pixelB = valorPixelB;


    int indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            RedA[i][j]   = pixelA[indice];
            GreenA[i][j] = pixelA[indice + 1];
            BlueA[i][j]  = pixelA[indice + 2];

            RedB[i][j]   = pixelB[indice];
            GreenB[i][j] = pixelB[indice + 1];
            BlueB[i][j]  = pixelB[indice + 2];
        }
    }

    const char *cNomeProcessamento =  (*env)->GetStringUTFChars(env, cNomeProcesso, 0);
    int  maiorR, maiorG, maiorB;
    maiorR = maiorG = maiorB = (int) INT64_MIN;
    int  menorR, menorG, menorB;
    menorR = menorG = menorB = (int) INT64_MAX;

    for ( i = 0; i < linha; i++) {
        for ( j = 0; j < coluna; j++) {

            if (strcmp(cNomeProcessamento, "TruncamentoSoma") == 0 ) {

                resultadoR[i][j] = RedA[i][j]   + (RedB[i][j] + 100);
                resultadoG[i][j] = GreenA[i][j] + (GreenB[i][j] + 100);
                resultadoB[i][j] = BlueA[i][j]  + (BlueB[i][j] + 100);
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoSoma") == 0 ) {

                resultadoR[i][j] = RedA[i][j]   + (RedB[i][j] + 200);
                resultadoG[i][j] = GreenA[i][j] + (GreenB[i][j] + 200);
                resultadoB[i][j] = BlueA[i][j]  + (BlueB[i][j] + 200);
            }
            if (strcmp(cNomeProcessamento, "TruncamentoSubtracao") == 0 ) {

                resultadoR[i][j] = RedA[i][j]   - BlueB[i][j];
                resultadoG[i][j] = GreenA[i][j] - RedB[i][j];
                resultadoB[i][j] = BlueA[i][j]  - GreenB[i][j];
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoSubtracao") == 0 ) {

                resultadoR[i][j] = RedA[i][j]   - 200;
                resultadoG[i][j] = GreenA[i][j] - 200;
                resultadoB[i][j] = BlueA[i][j]  - 200;
            }
            if (strcmp(cNomeProcessamento, "TruncamentoMultiplicacao") == 0 ) {

                resultadoR[i][j] = RedA[i][j]   * (RedB[i][j]  * 200) ;
                resultadoG[i][j] = GreenA[i][j] * (GreenB[i][j]* 200);
                resultadoB[i][j] = BlueA[i][j]  * (BlueB[i][j] * 200);
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoMultiplicacao") == 0) {

                resultadoR[i][j] = RedA[i][j]   * (RedB[i][j]  * RedB[i][j]) ;
                resultadoG[i][j] = GreenA[i][j] * (GreenB[i][j]* GreenB[i][j]);
                resultadoB[i][j] = BlueA[i][j]  * (BlueB[i][j] * BlueB[i][j]);
            }


            if (strcmp(cNomeProcessamento, "TruncamentoDivisao") == 0 ) {

                resultadoR[i][j] = RedA[i][j]   / 50 ;
                resultadoG[i][j] = GreenA[i][j] / 50;
                resultadoB[i][j] = BlueA[i][j]  / 50;
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoDivisao") == 0 ) {

                resultadoR[i][j] = RedA[i][j]   / 10 ;
                resultadoG[i][j] = GreenA[i][j] / 10;
                resultadoB[i][j] = BlueA[i][j]  / 10;
            }
            if (strcmp(cNomeProcessamento, "TruncamentoAnd") == 0 ) {

                int PixelRa = 0, PixelRb = 0;
                int PixelGa = 0, PixelGb = 0;
                int PixelBa = 0, PixelBb = 0;

                PixelRa = (int) RedA[i][j];
                PixelGa = (int) GreenA[i][j];
                PixelBa = (int) BlueA[i][j];
                PixelRb = (int) RedB[i][j];
                PixelGb = (int) GreenB[i][j];
                PixelBb = (int) BlueB[i][j];

                resultadoR[i][j] = PixelRa & (PixelRb + 100);
                resultadoG[i][j] = PixelGa & (PixelGb + 100);
                resultadoB[i][j] = PixelBa & (PixelBb + 100);
            }
            if (strcmp(cNomeProcessamento, "NormalizacaoAnd") == 0){

                int PixelRa = 0, PixelRb = 0;
                int PixelGa = 0, PixelGb = 0;
                int PixelBa = 0, PixelBb = 0;

                PixelRa = (int) RedA[i][j];
                PixelGa = (int) GreenA[i][j];
                PixelBa = (int) BlueA[i][j];
                PixelRb = (int) RedB[i][j];
                PixelGb = (int) GreenB[i][j];
                PixelBb = (int) BlueB[i][j];

                resultadoR[i][j] = PixelRa & PixelRb;
                resultadoG[i][j] = PixelGa & PixelGb;
                resultadoB[i][j] = PixelBa & PixelBb;
            }
            if (strcmp(cNomeProcessamento, "TruncamentoOr") == 0) {

                int PixelRa = 0, PixelRb = 0;
                int PixelGa = 0, PixelGb = 0;
                int PixelBa = 0, PixelBb = 0;

                PixelRa = (int) RedA[i][j];
                PixelGa = (int) GreenA[i][j];
                PixelBa = (int) BlueA[i][j];
                PixelRb = (int) RedB[i][j];
                PixelGb = (int) GreenB[i][j];
                PixelBb = (int) BlueB[i][j];

                resultadoR[i][j] = PixelRa |  PixelGb;
                resultadoG[i][j] = PixelGa |  PixelBb;
                resultadoB[i][j] = PixelBa |  PixelRb;

            }
            if (strcmp(cNomeProcessamento, "NormalizacaoOr") == 0 ) {

                int PixelRa = 0, PixelRb = 0;
                int PixelGa = 0, PixelGb = 0;
                int PixelBa = 0, PixelBb = 0;

                PixelRa = (int) RedA[i][j];
                PixelGa = (int) GreenA[i][j];
                PixelBa = (int) BlueA[i][j];
                PixelRb = (int) RedB[i][j];
                PixelGb = (int) GreenB[i][j];
                PixelBb = (int) BlueB[i][j];

                resultadoR[i][j] = PixelRa | (PixelRb + 150);
                resultadoG[i][j] = PixelGa | (PixelGb + 150);
                resultadoB[i][j] = PixelBa | (PixelBb + 150);
            }
            if (strcmp(cNomeProcessamento, "TruncamentoXor") == 0 ) {

                int PixelRa = 0;
                int PixelGa = 0;
                int PixelBa = 0;

                PixelRa = (int) RedA[i][j];
                PixelGa = (int) GreenA[i][j];
                PixelBa = (int) BlueA[i][j];

                resultadoR[i][j] = PixelRa ^ 127;
                resultadoG[i][j] = PixelGa ^ 127;
                resultadoB[i][j] = PixelBa ^ 127;
            }

            if (strcmp(cNomeProcessamento, "NormalizacaoXor") == 0) {

                int PixelRa = 0, PixelRb = 0;
                int PixelGa = 0, PixelGb = 0;
                int PixelBa = 0, PixelBb = 0;

                PixelRa = (int) RedA[i][j];
                PixelGa = (int) GreenA[i][j];
                PixelBa = (int) BlueA[i][j];
                PixelRb = (int) RedB[i][j];
                PixelGb = (int) GreenB[i][j];
                PixelBb = (int) BlueB[i][j];

                resultadoR[i][j] = PixelRa ^ (127 + PixelRb);
                resultadoG[i][j] = PixelGa ^ (127 + PixelGb);
                resultadoB[i][j] = PixelBa ^ (127 + PixelBb);
            }


                if (resultadoR[i][j] > maiorR) maiorR = (int) resultadoR[i][j];
                if (resultadoG[i][j] > maiorG) maiorG = (int) resultadoG[i][j];
                if (resultadoB[i][j] > maiorB) maiorB = (int) resultadoB[i][j];

                if (resultadoR[i][j] < menorR) menorR = (int) resultadoR[i][j];
                if (resultadoG[i][j] < menorG) menorG = (int) resultadoG[i][j];
                if (resultadoB[i][j] < menorB) menorB = (int) resultadoB[i][j];
        }
    }

    char substring[5];
    memcpy(cNomeProcessamento, &substring[5], 5 );
    substring[5] = '\0';


        for ( i = 0; i < linha; i++) {
            for (j = 0; j < coluna; j++) {

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


    indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            pixelA[indice] =     (int) resultadoR[i][j];
            pixelA[indice + 1] = (int) resultadoG[i][j];
            pixelA[indice + 2] = (int) resultadoB[i][j];

            pixelB[indice] =     (int) resultadoR[i][j];
            pixelB[indice + 1] = (int) resultadoG[i][j];
            pixelB[indice + 2] = (int) resultadoB[i][j];
        }
    }
    (*env)->ReleaseIntArrayElements(env, FotoA_, valorPixelA, 0);
    (*env)->ReleaseIntArrayElements(env, FotoB_, valorPixelB, 0);

    free(RedA);
    free(GreenA);
    free(BlueA);
    free(RedB);
    free(GreenB);
    free(BlueB);
    free(resultadoR);
    free(resultadoG);
    free(resultadoB);

}

