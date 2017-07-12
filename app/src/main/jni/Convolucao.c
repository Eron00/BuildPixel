#include <jni.h>
#include <android/bitmap.h>
#include "zoaFotoNativeLib.h"
#include <stdlib.h>

#define PROG_TITLE "ZoaFoto"



JNIEXPORT void Java_com_aplicacao_Modelo_NDK_convolucao(JNIEnv *env, jobject instance, jintArray Imagem, jstring mascara,jint linha,
                                                        jint coluna, jint linhaMascara, jint colunaMascara) {

    // para encontrar posicionamento da mascara na coordenada linha
    int linhaMask = (linhaMascara - 1) / 2;
    // para encontrar posicionamento da mascara na coordenada coluna
    int colunaMask = (colunaMascara - 1) / 2;

    int iLinha, jColuna, i, j, iMascara,jMascara;

    const char *cNomeMascara = (*env)->GetStringUTFChars(env, mascara, 0);
    float dMascaraFiltro[linhaMascara][colunaMascara];
    PopularMascara(cNomeMascara, linhaMascara,colunaMascara , dMascaraFiltro);


    float **Red     = (float **) (malloc(linha * sizeof(float *)));
    float **Blue    = (float **) (malloc(linha * sizeof(float *)));
    float **Green   = (float **) (malloc(linha * sizeof(float *)));
    float **RedTemp     = (float **) (malloc(linha * sizeof(float *)));
    float **BlueTemp    = (float **) (malloc(linha * sizeof(float *)));
    float **GreenTemp   = (float **) (malloc(linha * sizeof(float *)));

    for (i = 0; i < linha; i++) {
        Red  [i] = (float *) (malloc(coluna * sizeof(float)));
        Blue [i] = (float *) (malloc(coluna * sizeof(float)));
        Green[i] = (float *) (malloc(coluna * sizeof(float)));
        RedTemp  [i] = (float *) (malloc(coluna * sizeof(float)));
        BlueTemp [i] = (float *) (malloc(coluna * sizeof(float)));
        GreenTemp[i] = (float *) (malloc(coluna * sizeof(float)));
    }
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            Red  [i][j] = 0;
            Green[i][j] = 0;
            Blue [i][j] = 0;
            RedTemp  [i][j] = 0;
            BlueTemp[i][j] = 0;
            GreenTemp [i][j] = 0;
        }
    }

    jint *valorPixel;
    valorPixel = (*env)->GetIntArrayElements(env, Imagem, NULL);
    int *pixel = valorPixel;

    int indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            RedTemp  [i][j] = pixel[indice];
            GreenTemp[i][j] = pixel[indice + 1];
            BlueTemp [i][j] = pixel[indice + 2];
        }
    }

    for (iLinha = 0; iLinha < linha; iLinha++) {
        for (jColuna = 0; jColuna < coluna; jColuna++) {

            float media[] = {0, 0, 0};

            for (i = iLinha - linhaMask, iMascara = 0; i <= iLinha + linhaMask; i++,iMascara++) {
                for (j = jColuna - colunaMask, jMascara = 0; j <= jColuna + colunaMask; j++, jMascara++) {

                    // verificar se está entre  0 e a largura da imagem
                    if ((i >= 0) && (i < linha) && (j >= 0) && (j < coluna)) {
                        media[0] += RedTemp  [i][j] * dMascaraFiltro[iMascara][jMascara];
                        media[1] += GreenTemp[i][j] * dMascaraFiltro[iMascara][jMascara];
                        media[2] += BlueTemp [i][j] * dMascaraFiltro[iMascara][jMascara];
                    }
                }
            }
            if (media[0] > 255) { media[0] = 255; }
            else if (media[0] < 0) { media[0] = 0; }

            if (media[1] > 255) { media[1] = 255; }
            else if (media[1] < 0) { media[1] = 0; }

            if (media[2] > 255) { media[2] = 255; }
            else if (media[2] < 0) { media[2] = 0; }

            Red  [iLinha][jColuna] = (int)media[0];
            Green[iLinha][jColuna] = (int)media[1];
            Blue [iLinha][jColuna] = (int)media[2];
        }
    }
    indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            pixel[indice]     = (int) Red  [i][j];
            pixel[indice + 1] = (int) Green[i][j];
            pixel[indice + 2] = (int) Blue [i][j];
        }
    }

    (*env)->ReleaseIntArrayElements(env, Imagem, valorPixel, 0);
    free(Red);
    free(Green);
    free(Blue);
    free(RedTemp);
    free(GreenTemp);
    free(BlueTemp);
}
void convolucao(JNIEnv *env, jobject instance, jintArray Imagem, jstring mascara,jint linha, jint coluna, jint linhaMascara, jint colunaMascara){
    // para encontrar posicionamento da mascara na coordenada linha
    int linhaMask = (linhaMascara - 1) / 2;
    // para encontrar posicionamento da mascara na coordenada coluna
    int colunaMask = (colunaMascara - 1) / 2;

    int iLinha, jColuna, i, j;


    float dMascaraFiltro[linhaMascara][colunaMascara];
    PopularMascara(mascara, linhaMascara,colunaMascara , dMascaraFiltro);


    float **Red     = (float **) (malloc(linha * sizeof(float *)));
    float **Blue    = (float **) (malloc(linha * sizeof(float *)));
    float **Green   = (float **) (malloc(linha * sizeof(float *)));
    float **RedTemp     = (float **) (malloc(linha * sizeof(float *)));
    float **BlueTemp    = (float **) (malloc(linha * sizeof(float *)));
    float **GreenTemp   = (float **) (malloc(linha * sizeof(float *)));

    for (i = 0; i < linha; i++) {
        Red  [i] = (float *) (malloc(coluna * sizeof(float)));
        Blue [i] = (float *) (malloc(coluna * sizeof(float)));
        Green[i] = (float *) (malloc(coluna * sizeof(float)));
        RedTemp  [i] = (float *) (malloc(coluna * sizeof(float)));
        BlueTemp [i] = (float *) (malloc(coluna * sizeof(float)));
        GreenTemp[i] = (float *) (malloc(coluna * sizeof(float)));
    }
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            Red  [i][j] = 0;
            Green[i][j] = 0;
            Blue [i][j] = 0;
            RedTemp  [i][j] = 0;
            BlueTemp[i][j] = 0;
            GreenTemp [i][j] = 0;
        }
    }

    jint *valorPixel;
    valorPixel = (*env)->GetIntArrayElements(env, Imagem, NULL);
    int *pixel = valorPixel;

    int indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            RedTemp  [i][j] = pixel[indice];
            GreenTemp[i][j] = pixel[indice + 1];
            BlueTemp [i][j] = pixel[indice + 2];
        }
    }

    for (iLinha = 0; iLinha < linha; iLinha++) {
        for (jColuna = 0; jColuna < coluna; jColuna++) {

            int iMascara = 0, jMascara = 0;
            float media[] = {0, 0, 0};

            for (i = iLinha - linhaMask; i <= iLinha + linhaMask; i++) {
                for (j = jColuna - colunaMask; j <= jColuna + colunaMask; j++) {

                    // verificar se está entre  0 e a largura da imagem
                    if ((i >= 0) && (i < linha) && (j >= 0) && (j < coluna)) {
                        media[0] += RedTemp  [i][j] * dMascaraFiltro[iMascara][jMascara];
                        media[1] += GreenTemp[i][j] * dMascaraFiltro[iMascara][jMascara];
                        media[2] += BlueTemp [i][j] * dMascaraFiltro[iMascara][jMascara];
                    }
                    jMascara++;
                }
                iMascara++;
                jMascara = 0;
            }
            if (media[0] > 255) { media[0] = 255; }
            else if (media[0] < 0) { media[0] = 0; }

            if (media[1] > 255) { media[1] = 255; }
            else if (media[1] < 0) { media[1] = 0; }

            if (media[2] > 255) { media[2] = 255; }
            else if (media[2] < 0) { media[2] = 0; }

            Red  [iLinha][jColuna] = (int)media[0];
            Green[iLinha][jColuna] = (int)media[1];
            Blue [iLinha][jColuna] = (int)media[2];
        }
    }
    indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            pixel[indice]     = (int) Red  [i][j];
            pixel[indice + 1] = (int) Green[i][j];
            pixel[indice + 2] = (int) Blue [i][j];
        }
    }

    (*env)->ReleaseIntArrayElements(env, Imagem, valorPixel, 0);
    free(Red);
    free(Green);
    free(Blue);
    free(RedTemp);
    free(GreenTemp);
    free(BlueTemp);
}