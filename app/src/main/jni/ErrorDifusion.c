//
// Created by Eron on 02/04/2016.
//
#include <jni.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_errorDifusion(JNIEnv *env, jobject instance, jintArray FotoResultante, jint linha, jint coluna) {
    int i, j;
    int PropagedError;
    int TotalError;

    PropagedError = 0;

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
            Pixel = (int) ((Red[i][j] + Green[i][j] + Blue[i][j]) / 3);
            RedTemp[i][j] = Pixel;
            BlueTemp[i][j] = Pixel;
            GreenTemp[i][j] = Pixel;
        }
    }
    for (i = 1; i < linha; i++) {
        for (j = 1; j < coluna; j++) {

            TotalError = (int) (RedTemp[i][j]+ PropagedError);

            if(TotalError > 127)
            {
                Red[i][j] = 255;
                Green[i][j] = 255;
                Blue[i][j] = 255;
            }

            else
            {
                Red[i][j] = 0;
                Green[i][j] = 0;
                Blue[i][j] = 0;
            }

            PropagedError = (int) (TotalError - Red[i][j]);
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


