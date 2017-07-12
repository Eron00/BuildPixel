#include <jni.h>
#include <android/bitmap.h>
#include "zoaFotoNativeLib.h"
#include <stdlib.h>

#define PROG_TITLE "ZoaFoto"


JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_media(JNIEnv *env, jobject instance, jintArray FotoResultante,
jint linha, jint coluna) {

    int i, j;
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
            RedTemp[i][j] = pixel[indice];
            GreenTemp[i][j] = pixel[indice + 1];
            BlueTemp[i][j] = pixel[indice + 2];
        }
    }

    for (i = 1; i < (linha - 1); i++) {
        for (j = 1; j < (coluna - 1); j++) {
            Red[i][j]   = (RedTemp[i - 1][j - 1] + RedTemp[i - 1][j] + RedTemp[i - 1][j + 1] +
                           RedTemp[i]    [j - 1] + RedTemp[i]    [j] + RedTemp[i]    [j + 2] +
                           RedTemp[i + 1][j - 1] + RedTemp[i + 1][j] + RedTemp[i + 1][j + 1]) / 9;


            Green[i][j] = (GreenTemp[i - 1][j - 1] + GreenTemp[i - 1][j] + GreenTemp[i - 1][j + 1] +
                           GreenTemp[i]    [j - 1] + GreenTemp[i]    [j] + GreenTemp[i]    [j + 2] +
                           GreenTemp[i + 1][j - 1] + GreenTemp[i + 1][j] + GreenTemp[i + 1][j + 1]) / 9;


            Blue[i][j] =  (BlueTemp[i - 1][j - 1] + BlueTemp[i - 1][j] + BlueTemp[i - 1][j + 1] +
                           BlueTemp[i]    [j - 1] + BlueTemp[i]    [j] + BlueTemp[i]    [j + 2] +
                           BlueTemp[i + 1][j - 1] + BlueTemp[i + 1][j] + BlueTemp[i + 1][j + 1]) / 9;

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
    free(GreenTemp);
    free(BlueTemp);
}



