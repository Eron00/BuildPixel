//
// Created by Eron on 14/04/2016.
//
#include <jni.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_tintaoleo(JNIEnv *env, jobject instance, jintArray FotoResultante, jint linha, jint coluna) {

    int i,j, l;
    // para encontrar posicionamento da mascara na coordenada linha
    int linhaMask = (7 - 1) / 2;
    // para encontrar posicionamento da mascara na coordenada coluna
    int colunaMask = (7 - 1) / 2;


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

    int levels = 90;

    int currentIntensity = 0;
    int maxIntensity = 0;
    int maxIndex = 0;

    double blue = 0;
    double green = 0;
    double red = 0;
    int iLinha = 0;
    int jColuna = 0;


    int* intensityBin = (int)(malloc((levels) * sizeof(int)));
    int* blueBin      = (int)(malloc((levels) * sizeof(int)));
    int* greenBin     = (int)(malloc((levels) * sizeof(int)));
    int* redBin       = (int)(malloc((levels) * sizeof(int)));

    for (iLinha = 0; iLinha < linha; iLinha++) {
        for (jColuna = 0; jColuna < coluna; jColuna++) {
            maxIntensity = maxIndex = 0;
           for(l=0; l < levels; l++)
           {
               intensityBin[l] =0;
               blueBin[l] =0;
               greenBin[l]=0;
               redBin[l]=0;
           }

            for (i = iLinha - linhaMask; i <= iLinha + linhaMask; i++) {
                for (j = jColuna - colunaMask; j <= jColuna + colunaMask; j++) {

                    // verificar se está entre  0 e a largura da imagem
                    if ((i >= 0) && (i < linha) && (j >= 0) && (j < coluna)) {

                        currentIntensity =  ((int)((Red[i][j]+Green[i][j]+Blue [i][j]) / 3 )* levels) / 255;

                        intensityBin[currentIntensity]++;
                        redBin[currentIntensity]       += (int)Red[i][j] ;
                        greenBin[currentIntensity]     += (int)Green[i][j];
                        blueBin[currentIntensity]      += (int)Blue[i][j];

                        if (intensityBin[currentIntensity] > maxIntensity) {
                            maxIntensity = intensityBin[currentIntensity];
                            maxIndex = currentIntensity;
                        }
                    }
                }
            }

            red = redBin[maxIndex] / maxIntensity;
            green = greenBin[maxIndex] / maxIntensity;
            blue = blueBin[maxIndex] / maxIntensity;

            if(red > 255)
                red = 255;
            if(red < 0)
                red = 0;
            if(green > 255)
                green = 255;
            if(green < 0)
                green = 0;
            if(blue > 255)
                blue = 255;
            if(blue < 0)
                blue = 0;
            RedTemp[iLinha][jColuna] = (float) red;
            BlueTemp[iLinha][jColuna] = (float) blue;
            GreenTemp[iLinha][jColuna] = (float) green;

        }
    }



    indice = 0;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++, indice += 3) {
            pixel[indice] = (int) RedTemp[i][j];
            pixel[indice + 1] = (int) GreenTemp[i][j];
            pixel[indice + 2] = (int) BlueTemp[i][j];
        }
    }
    (*env)->ReleaseIntArrayElements(env, FotoResultante, valorPixel, 0);


    free(Red);
    free(Green);
    free(Blue);
    free(RedTemp);
    free(BlueTemp);
    free(GreenTemp);
    free(intensityBin);
    free(redBin);
    free(greenBin);
    free(blueBin);
}

/*
    int i;


    int index = 0;
    int intensity_count[255] = {0} ;
    int sumR[255] = {0};
    int sumG[255] = {0};
    int sumB[255] = {0};
    int current_intensity = 0;
    int row,col, x, y;
    int curMax = 0;
    int maxIndex = 0;
    int radius = 2;
   int intensity_level = 20;
    int r =0;
    int g =0;
    int b =0;

    jint *valorPixel;
    valorPixel = (*env)->GetIntArrayElements(env, FotoResultante, NULL);
    int *pixel = valorPixel;

    jint *valorTemp = NULL;
    valorPixel = (*env)->GetIntArrayElements(env, FotoResultante, NULL);
    int *pixelTemp = valorTemp;

    for(col = radius; col < (coluna - radius) ; col++ ) {
        for(row = radius; row < (linha - radius); row++) {
            memset(&intensity_count[0] , 0, sizeof(intensity_count)/sizeof(int));
            memset(&sumR[0], 0 ,sizeof(sumR)/sizeof(int));
            memset(&sumG[0], 0 ,sizeof(sumG)/sizeof(int));
            memset(&sumB[0], 0 ,sizeof(sumB)/sizeof(int));
/* Calculat e the h ighest i ntensit y Neighb ouring Pixels.
            for(y = -radius; y <= radius; y++ ) {
                for(x = -radius; x <= radius; x++ ) {
                    index = ( (col + y) * linha * 3) + ((row + x) * 3);
                    r = pixel[index + 0] ;
                    g = pixel[index + 1] ;
                    b = pixel[index + 2] ;
                    current_intensity = (int) (((r + g + b ) * intensity_level/3.0)/255);
                    intensity_count[current_intensity]++;
                    sumR[current_intensity] += r;
                    sumG[current_intensity] += g;
                    sumB[current_intensity] += b;
                }
            }
            index = (col * linha * 3) + (row * 3);
             T he high est inte nsity n eighbour ing pix els are average d out t o get th e exact color.
            maxIndex = 0;
            curMax = intensity_count[maxIndex] ;
            for(i = 0; i < intensity_level; i++) {
                if( intensity_count[i] > curMax ) {
                    curMax = intensity_count[i];
                    maxIndex = i;
                }
            }
            if(curMax > 0) {
                pixelTemp[ index + 0] = sumR[maxIndex]/curMax;
                pixelTemp[ index + 1] = sumG[maxIndex]/curMax;
                pixelTemp[ index + 2] = sumB[maxIndex]/curMax;
            }
        }
    }
    (*env)->ReleaseIntArrayElements(env, FotoResultante, valorPixel, 0);
    (*env)->ReleaseIntArrayElements(env, FotoResultante, valorTemp, 0);

}
*/


