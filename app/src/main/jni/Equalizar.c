#include <jni.h>
#include <android/bitmap.h>
#include "zoaFotoNativeLib.h"
#include <stdlib.h>

#define PROG_TITLE "ZoaFoto"

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_equalizar(JNIEnv *env, jobject instance, jintArray FotoResultante, jint linha, jint coluna) {
    int i, j;

    float **Red = (float **) (malloc(linha * sizeof(float *)));
    float **Blue = (float **) (malloc(linha * sizeof(float *)));
    float **Green = (float **) (malloc(linha * sizeof(float *)));
    int *histogramaAbsR = (int *) (malloc(256 * sizeof(int)));
    int *histogramaAbsG = (int *) (malloc(256 * sizeof(int)));
    int *histogramaAbsB = (int *) (malloc(256 * sizeof(int)));
    double *fdpAcumuladaR = (double *) (malloc(256 * sizeof(double)));
    double *fdpAcumuladaG = (double *) (malloc(256 * sizeof(double)));
    double *fdpAcumuladaB = (double *) (malloc(256 * sizeof(double)));

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

    for (i = 0; i < 256; i++) {
        fdpAcumuladaR[i] = 0;
        fdpAcumuladaG[i] = 0;
        fdpAcumuladaB[i] = 0;
        histogramaAbsR[i] = 0;
        histogramaAbsG[i] = 0;
        histogramaAbsB[i] = 0;
    }
    jint *valorPixel;
    valorPixel = (*env)->GetIntArrayElements(env, FotoResultante, NULL);
    int *pixel = valorPixel;

    int indice = 0;
    int indiceRed = 0;
    int indiceGreen = 0;
    int indiceBlue = 0;

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            Red[i][j] = pixel[indice];
            Green[i][j] = pixel[indice + 1];
            Blue[i][j] = pixel[indice + 2];
        }
    }
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            indiceRed = (int) Red[i][j];
            indiceGreen = (int) Green[i][j];
            indiceBlue = (int) Blue[i][j];
            histogramaAbsR[indiceRed]++;
            histogramaAbsG[indiceGreen]++;
            histogramaAbsB[indiceBlue]++;
        }
    }

    for (i = 0; i < 256; i++) {
        fdpAcumuladaR[i] = histogramaAbsR[i];
        fdpAcumuladaG[i] = histogramaAbsG[i];
        fdpAcumuladaB[i] = histogramaAbsB[i];

    }

    for (i = 1; i < 256; i++) {
        fdpAcumuladaR[i] = fdpAcumuladaR[i - 1] + histogramaAbsR[i];
        fdpAcumuladaB[i] = fdpAcumuladaB[i - 1] + histogramaAbsB[i];
        fdpAcumuladaG[i] = fdpAcumuladaG[i - 1] + histogramaAbsG[i];
    }


    int AcumuladaR = 0;
    int AcumuladaG = 0;
    int AcumuladaB = 0;


    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            indiceRed = (int) Red[i][j];
            indiceGreen = (int) Green[i][j];
            indiceBlue = (int) Blue[i][j];

            AcumuladaR = (int) ((fdpAcumuladaR[indiceRed] * 255) / (linha * coluna));
            AcumuladaG = (int) ((fdpAcumuladaG[indiceGreen] * 255) / (linha * coluna));
            AcumuladaB = (int) ((fdpAcumuladaB[indiceBlue] * 255) / (linha * coluna));

            Red[i][j] = AcumuladaR;
            Green[i][j] = AcumuladaG;
            Blue[i][j] = AcumuladaB;
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
    free(fdpAcumuladaR);
    free(fdpAcumuladaG);
    free(fdpAcumuladaB);
    free(histogramaAbsR);
    free(histogramaAbsG);
    free(histogramaAbsB);

}