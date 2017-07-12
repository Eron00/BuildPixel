//
// Created by Eron on 29/05/2016.
//

//
// Created by Eron on 12/04/2016.
//
#include <jni.h>
#include <stdlib.h>
#include "zoaFotoNativeLib.h"



JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_cartoon(JNIEnv *env, jobject instance, jintArray FotoOriginal, jintArray FotoResultante, jint linha, jint coluna) {



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

    jint *valorPixelOriginal;
    valorPixelOriginal = (*env)->GetIntArrayElements(env, FotoOriginal, NULL);
    int *pixelOriginal = valorPixelOriginal;

    int indice = 0;
    convolucao(env,instance,FotoResultante, "SobelHorizontal", linha,coluna,3,3);
    convolucao(env,instance,FotoResultante, "SobelVertical", linha,coluna,3,3);

    jint *valorPixelResultante;
    valorPixelResultante = (*env)->GetIntArrayElements(env, FotoResultante, NULL);
    int *pixelResultante = valorPixelResultante;




    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            Red[i][j] = pixelOriginal[indice];
            Green[i][j] = pixelOriginal[indice + 1];
            Blue[i][j] = pixelOriginal[indice + 2];
        }
    }

    indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            RedTemp[i][j] = pixelResultante[indice];
            GreenTemp[i][j] = pixelResultante[indice + 1];
            BlueTemp[i][j] = pixelResultante[indice + 2];
        }
    }

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            int Pixel = 0;
            //cinzamedia
            Pixel = (int)(RedTemp[i][j] + GreenTemp[i][j] + BlueTemp[i][j]) / 3;
            RedTemp[i][j] = Pixel ;
            GreenTemp[i][j] = Pixel;
            BlueTemp[i][j] = Pixel;
        }
    }

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            //inverter
            int PixelR = 0;
            int PixelG = 0;
            int PixelB = 0;
            PixelR = (int) (255 - RedTemp[i][j]);
            PixelG = (int) (255 - GreenTemp[i][j]);
            PixelB = (int) (255 - BlueTemp[i][j]);
            RedTemp[i][j] = PixelR;
            GreenTemp[i][j] = PixelG;
            BlueTemp[i][j] = PixelB;
        }
    }

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            //threshold
            if(RedTemp[i][j] > 200)
            {
                RedTemp[i][j] = 255;
                GreenTemp[i][j] = 255;
                BlueTemp[i][j] = 255;
            }
            else
            {
                RedTemp[i][j] = 0;
                GreenTemp[i][j] = 0;
                BlueTemp[i][j] = 0;
            }
        }
    }



    indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {

            if (RedTemp[i][j] > 10)  {
                RedTemp[i][j] = (int) Red[i][j];
            }
            if (GreenTemp[i][j] > 10)  {
                GreenTemp[i][j] = (int) Green[i][j];
            }
            if (BlueTemp[i][j] > 10)  {
                BlueTemp[i][j] = (int) Blue[i][j];
            }

            pixelOriginal[indice] = (int) RedTemp[i][j];
            pixelOriginal[indice + 1] =  (int) GreenTemp[i][j];
            pixelOriginal[indice + 2] =  (int) BlueTemp[i][j];
        }
    }
    (*env)->ReleaseIntArrayElements(env, FotoResultante, valorPixelResultante, 0);
    (*env)->ReleaseIntArrayElements(env, FotoOriginal, valorPixelOriginal, 0);


    free(Red);
    free(Green);
    free(Blue);
    free(RedTemp);
    free(BlueTemp);
    free(GreenTemp);

}

/*
void BubbleSort (int nVetor[], int nQTDE)
{
    bool flgtrocou;
    int i,nWork;

    do
    {
        for ( i = 0 ,flgtrocou = false; i < nQTDE - 1; i++)
        {
            if (nVetor[i] < nVetor[i+1])
            {
                nWork = nVetor[i];
                nVetor[i] = nVetor[i+1];
                nVetor[i+1] = nWork;
                flgtrocou = true;
            }//if
        }//for
    } while (flgtrocou);
}//BubbleSort

*/