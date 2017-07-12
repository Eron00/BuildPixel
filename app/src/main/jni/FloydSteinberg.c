//
// Created by Eron on 02/04/2016.
//
#include <jni.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_floydSteinberg(JNIEnv *env, jobject instance, jintArray FotoResultante, jint linha, jint coluna) {

    int indice, l, c;

    int nPropagedError;         /* propagated error */
    int nPixelAntigo;
    int nPixelCalculado;
    int i,j;

    float **Red = (float **) (malloc(linha * sizeof(float *)));
    float **Blue = (float **) (malloc(linha * sizeof(float *)));
    float **Green = (float **) (malloc(linha * sizeof(float *)));

    for (i = 0; i < linha; i++) {
        Red[i] = (float *) (malloc(coluna * sizeof(float)));
        Blue[i] = (float *) (malloc(coluna * sizeof(float)));
        Green[i] = (float *) (malloc(coluna * sizeof(float)));
    }
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            Red[i][j] = 0;
            Green[i][j] = 0;
            Blue[i][j] = 0;
        }
    }


    jint *valorPixel;
    valorPixel = (*env)->GetIntArrayElements(env, FotoResultante, NULL);
    int *pixel = valorPixel;

   indice = 0;
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
            Pixel = (int) ((Red[i][j] + Green[i][j]+ Blue[i][j]) / 3);
            Red[i][j] = Pixel;
            Blue[i][j] = Pixel;
            Green[i][j] = Pixel;
        }
    }

    for (l = 1; l < linha- 1; l++) {
        for (c = 1; c < coluna - 1; c++) {

            nPixelAntigo = (int) Red[l][c];
            if (nPixelAntigo > 127)
                nPixelCalculado = 255;
            else
                nPixelCalculado = 0;
            Red[l][c] = nPixelCalculado;
            Green[l][c] =  nPixelCalculado;
            Blue[l][c] =  nPixelCalculado;

            nPropagedError = nPixelAntigo - nPixelCalculado;
            Red[l + 1][c]= (   Red[l + 1][c] + (7 * nPropagedError) / 16);
            Green[l + 1][c]= (  Green[l + 1][c] + (7 * nPropagedError) / 16);
            Blue[l + 1][c]=  (Blue[l + 1][c] + (7 * nPropagedError) / 16);


            Red[l][c - 1]= (Red[l][c - 1] + (3 * nPropagedError) / 16);
            Green[l][c - 1]=  (Green[l][c - 1] + (3 * nPropagedError) / 16);
            Blue[l][c -1]= (Blue[l][c - 1] + (3 * nPropagedError) / 16);


            Red[l][c] =   (Red[l][c] + (5 * nPropagedError) / 16);
            Green[l][c] = (Green[l][c] + (5 * nPropagedError) / 16);
            Blue[l][c] =  (Blue[l][c] + (5 * nPropagedError) / 16);


            Red[l][c + 1] =  (Red[l][c + 1] + (1 * nPropagedError) / 16);
            Green[l][c + 1] =  ( Green[l][c + 1] + (1 * nPropagedError) / 16);
            Blue[l][c + 1] =  ( Blue[l][c + 1] + (1 * nPropagedError) / 16);
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
}
