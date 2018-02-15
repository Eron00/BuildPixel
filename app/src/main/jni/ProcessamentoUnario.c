//
// Created by Eron on 31/03/2016.
//

#include <jni.h>
#include <android/bitmap.h>
#include "buildPixelNativeLib.h"
#include <stdlib.h>
#include <math.h>

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_processamentoUnario(JNIEnv *env, jobject instance, jobject Foto, jstring cNomeProcesso) {

    AndroidBitmapInfo dadosImagem;
    void* localPixels;
    int linha, coluna, red,green,blue;
    u_int32_t* pixel;

    AndroidBitmap_getInfo(env,Foto,&dadosImagem);
    AndroidBitmap_lockPixels(env,Foto,&localPixels);


    const char *cNomeProcessamento =  (*env)->GetStringUTFChars(env, cNomeProcesso, 0);
    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            int Pixel = 0;
            //extração dos dados RGB do pixel
            blue  = (int)((pixel[coluna] & 0x00FF0000) >> 16);
            green = (int)((pixel[coluna] & 0x0000FF00) >> 8);
            red   = (int) (pixel[coluna] & 0x00000FF );

            if (strcmp(cNomeProcessamento, "Amarelo") == 0) {
                red = 255;
                green = 255;
                blue =0;
            }
            if (strcmp(cNomeProcessamento, "Azul") == 0) {
                red = 0;
                green = 0;
            }
            if (strcmp(cNomeProcessamento, "Blue") == 0) {
                red = blue;
                green = blue;

            }
            if (strcmp(cNomeProcessamento, "Brilho") == 0) {

                Pixel = (int)(fmax(red, fmax(green,blue)) +
                              (fmin(red, fmin(green,blue)/2.0)));
                red = Pixel ;
                green = Pixel;
                blue = Pixel;

            }
            if (strcmp(cNomeProcessamento, "Ciano") == 0) {
                red =0;
                green = 255;
                blue = 255;
            }
            if (strcmp(cNomeProcessamento, "CinzaMedia") == 0) {

                Pixel = (red + green +blue) / 3;

                red = Pixel ;
                green = Pixel;
                blue = Pixel;
            }
            if (strcmp(cNomeProcessamento, "Green") == 0) {
                red = green;
                blue = green;
            }

            if (strcmp(cNomeProcessamento, "Inverter") == 0) {
                int PixelR = 0;
                int PixelG = 0;
                int PixelB = 0;
                PixelR = (255 - red);
                PixelG = (255 - green);
                PixelB = (255 - blue);
                red = PixelR;
                green = PixelG;
                blue = PixelB;
            }

            if (strcmp(cNomeProcessamento, "Luminosidade") == 0) {

                Pixel  = (int) (0.2125 * red + 0.7154 * green + 0.0721 * blue);
                red = Pixel;
                green = Pixel;
                blue = Pixel;
            }

            if (strcmp(cNomeProcessamento, "Magenta") == 0) {
                red = 255;
                blue = 255;
                green = 0;
            }

            if (strcmp(cNomeProcessamento, "Red") == 0) {
                green = red;
                blue  = red;
            }

            if (strcmp(cNomeProcessamento, "Sepia") == 0) {
                int PixelR = 0;
                int PixelG = 0;
                int PixelB = 0;

                Pixel = (int) ((red * 0.3) + (green* 0.59) + (blue* 0.11));


                PixelR = Pixel + 40;
                PixelG = Pixel + 20;
                PixelB = Pixel - 20;


                if(PixelR > 255)
                    PixelR = 255;
                if(PixelG > 255)
                    PixelG = 255;
                if(PixelB < 0)
                    PixelB = 0;

                red   = PixelR;
                green = PixelG;
                blue  = PixelB;
            }

            if (strcmp(cNomeProcessamento, "Threshold") == 0) {
                if(red > 200)
                {
                    red = 255;
                    green = 255;
                    blue = 255;
                }
                else
                {
                    red = 0;
                   green = 0;
                   blue = 0;
                }
            }
            if (strcmp(cNomeProcessamento, "Verde") == 0) {
                red = 0;
                blue = 0;
            }
            if (strcmp(cNomeProcessamento, "Vermelho") == 0) {

                green = 0;
                blue = 0;
            }

            // atribuindo novos valores ao pixel
            pixel[coluna] = (uint32_t) (((blue << 16) & 0x00FF0000) |
                                        ((green << 8) & 0x0000FF00) |
                                        (red          & 0x000000FF));
        }

        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    AndroidBitmap_unlockPixels(env,Foto);
}

void processamentoUnario(JNIEnv *env, jobject instance, jintArray FotoResultante, jint linha, jint coluna, jstring cNomeProcesso){
    int i, j;

    float **Red   = (float **) (malloc(linha * sizeof(float *)));
    float **Blue  = (float **) (malloc(linha * sizeof(float *)));
    float **Green = (float **) (malloc(linha * sizeof(float *)));

    for (i = 0; i < linha; i++) {
        Red[i]   = (float *) (malloc(coluna * sizeof(float)));
        Blue[i]  = (float *) (malloc(coluna * sizeof(float)));
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

    int indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            Red[i][j] = pixel[indice];
            Green[i][j] = pixel[indice + 1];
            Blue[i][j] = pixel[indice + 2];
        }
    }

    const char *cNomeProcessamento =  (*env)->GetStringUTFChars(env, cNomeProcesso, 0);
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            int Pixel = 0;
            if (strcmp(cNomeProcessamento, "Amarelo") == 0) {
                Red[i][j] = 255;
                Green[i][j] = 255;
            }
            if (strcmp(cNomeProcessamento, "Azul") == 0) {
                Red[i][j] = 0;
                Green[i][j] = 0;
            }
            if (strcmp(cNomeProcessamento, "Blue") == 0) {
                Red[i][j] = Blue[i][j];
                Green[i][j] = Blue[i][j];

            }
            if (strcmp(cNomeProcessamento, "Brilho") == 0) {

                Pixel = (int)(fmax(Red[i][j], fmax(Green[i][j],Blue[i][j])) +
                              (fmin(Red[i][j], fmin(Green[i][j],Blue[i][j])/2.0)));

                Red[i][j] = Pixel ;
                Green[i][j] = Pixel;
                Blue[i][j] = Pixel;

            }
            if (strcmp(cNomeProcessamento, "Ciano") == 0) {

                Green[i][j] = 255;
                Blue[i][j] = 255;
            }
            if (strcmp(cNomeProcessamento, "CinzaMedia") == 0) {

                Pixel = (int)(Red[i][j] + Green[i][j] + Blue[i][j]) / 3;

                Red[i][j] = Pixel ;
                Green[i][j] = Pixel;
                Blue[i][j] = Pixel;
            }
            if (strcmp(cNomeProcessamento, "Green") == 0) {
                Red[i][j] = Green[i][j];
                Blue[i][j] = Green[i][j];
            }

            if (strcmp(cNomeProcessamento, "Inverter") == 0) {
                int PixelR = 0;
                int PixelG = 0;
                int PixelB = 0;
                PixelR = (int) (255 - Red[i][j]);
                PixelG = (int) (255 - Green[i][j]);
                PixelB = (int) (255 - Blue[i][j]);
                Red[i][j] = PixelR;
                Green[i][j] = PixelG;
                Blue[i][j] = PixelB;
            }

            if (strcmp(cNomeProcessamento, "Luminosidade") == 0) {

                Pixel  = (int) (0.2125 * Red[i][j] + 0.7154 * Green[i][j]+ 0.0721 * Blue[i][j]);
                Red[i][j] = Pixel;
                Green[i][j] = Pixel;
                Blue[i][j] = Pixel;
            }

            if (strcmp(cNomeProcessamento, "Magenta") == 0) {
                Red[i][j] = 255;
                Blue[i][j] = 255;
            }

            if (strcmp(cNomeProcessamento, "Red") == 0) {
                Green[i][j] = Red[i][j];
                Blue[i][j] = Red[i][j];
            }

            if (strcmp(cNomeProcessamento, "Sepia") == 0) {
                int PixelR = 0;
                int PixelG = 0;
                int PixelB = 0;

                Pixel = (int) ((Red[i][j] * 0.3) + (Green[i][j] * 0.59) + (Blue[i][j] * 0.11));


                PixelR = Pixel + 40;
                PixelG = Pixel + 20;
                PixelB = Pixel - 20;


                if(PixelR > 255)
                    PixelR = 255;
                if(PixelG > 255)
                    PixelG = 255;
                if(PixelB < 0)
                    PixelB = 0;

                Red[i][j]   = PixelR;
                Green[i][j] = PixelG;
                Blue[i][j]  = PixelB;
            }

            if (strcmp(cNomeProcessamento, "Threshold") == 0) {
                if(Red[i][j] > 200)
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
            }
            if (strcmp(cNomeProcessamento, "Verde") == 0) {
                Red[i][j] = 0;
                Blue[i][j] = 0;
            }
            if (strcmp(cNomeProcessamento, "Vermelho") == 0) {

                Green[i][j] = 0;
                Blue[i][j] = 0;
            }
        }
    }

    indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            pixel[indice] =     (int) Red[i][j];
            pixel[indice + 1] = (int) Green[i][j];
            pixel[indice + 2] = (int) Blue[i][j];
        }
    }
    (*env)->ReleaseIntArrayElements(env, FotoResultante, valorPixel, 0);

    free(Red);
    free(Green);
    free(Blue);
}