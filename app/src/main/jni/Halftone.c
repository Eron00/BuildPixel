//
// Created by Eron on 02/04/2016.
//
#include <jni.h>
#include <stdlib.h>
JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_halftone(JNIEnv *env, jobject instance, jintArray FotoResultante, jint linha, jint coluna) {
    int i, j, l, c;
    int Valor;
    float **Red = (float **) (malloc(linha * sizeof(float *)));
    float **Blue = (float **) (malloc(linha * sizeof(float *)));
    float **Green = (float **) (malloc(linha * sizeof(float *)));
    float **RedTemp = (float **) (malloc(linha * sizeof(float *)));
    float **BlueTemp = (float **) (malloc(linha * sizeof(float *)));
    float **GreenTemp = (float **) (malloc(linha * sizeof(float *)));

    for (i = 0; i < linha; i++) {
        Red[i] = (float *) (malloc(coluna * sizeof(float)));
        Blue[i] = (float *) (malloc(coluna * sizeof(float)));
        Green[i] = (float *) (malloc(coluna * sizeof(float)));
        RedTemp[i] = (float *) (malloc(coluna * sizeof(float)));
        BlueTemp[i] = (float *) (malloc(coluna * sizeof(float)));
        GreenTemp[i] = (float *) (malloc(coluna * sizeof(float)));
    }
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            Red[i][j] = 0;
            Green[i][j] = 0;
            Blue[i][j] = 0;
            RedTemp[i][j] = 0;
            BlueTemp[i][j] = 0;
            GreenTemp[i][j] = 0;
        }
    }


    jint *valorPixel;
    valorPixel = (*env)->GetIntArrayElements(env, FotoResultante, NULL);
    int *pixel = valorPixel;

    int indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            Red[i][j] = pixel[indice];
            Green[i][j] = pixel[indice + 1];
            Blue[i][j] = pixel[indice + 2];
        }
    }

    for (i = 0; i < linha; i++) {
        for ( j = 0; j < coluna; j++) {
            int Pixel;
            Pixel = (int) ((Red[i][j] + Green[i][j]+ Blue[i][j]) / 3.0);
            RedTemp[i][j] = Pixel;
            BlueTemp[i][j] = Pixel;
            GreenTemp[i][j] = Pixel;
        }
    }

    for ( l = 0; l < linha - 1; l += 2) {
        for (c = 0; c < coluna - 1; c += 2) {

            Valor = (int) RedTemp[l][c];
            Valor += RedTemp[l][c + 1];
            Valor += RedTemp[l + 1][c];
            Valor += RedTemp[l + 1][c + 1];

            if (Valor > (1 * 1024) / 8) {
                Red[l][c] = 255;
                Green[l][c] = 255;
                Blue[l][c] = 255;
            }
            else
            {
                Red[l][c] = 0;
                Green[l][c] = 0;
                Blue[l][c] = 0;
            }

            if (Valor > (3 * 1024) / 8)
            {
                Red[l + 1][c +1]   = 255;
                Green[l + 1][c +1] = 255;
                Blue[l + 1][c +1]  = 255;
            }

            else
            {
                Red[l + 1][c +1]   = 0;
                Green[l + 1][c +1] = 0;
                Blue[l + 1][c +1]  = 0;
            }

            if (Valor > (5 * 1024) / 8)
            {
                Red[l + 1][c]   = 255;
                Green[l + 1][c] = 255;
                Blue[l + 1][c]  = 255;
            }
            else
            {
                Red[l + 1][c]   = 0;
                Green[l + 1][c] = 0;
                Blue[l + 1][c]  = 0;
            }

            if (Valor > (7 * 1024) / 8)
            {
                Red[l][c + 1]   = 255;
                Green[l][c + 1] = 255;
                Blue[l][c + 1]  = 255;
            }
            else
            {
                Red[l][c + 1]   = 0;
                Green[l][c + 1] = 0;
                Blue[l][c + 1]  = 0;
            }
        }
    }

    indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            pixel[indice] = (int) Red[i][j];
            pixel[indice + 1] = (int) Green[i][j];
            pixel[indice + 2] = (int) Blue[i][j];
        }
    }
    (*env)->ReleaseIntArrayElements(env, FotoResultante, valorPixel, 0);

    free(Red);
    free(Green);
    free(Blue);
    free(RedTemp);
    free(BlueTemp);
    free(GreenTemp);
}