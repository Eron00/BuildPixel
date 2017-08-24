//
// Created by Eron on 14/04/2016.
//
#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_tintaoleo(JNIEnv *env, jobject instance,jobject foto) {

    // para encontrar posicionamento da mascara na coordenada linha
    int linhaMask = (7 - 1) / 2;
    // para encontrar posicionamento da mascara na coordenada coluna
    int colunaMask = (7 - 1) / 2;


    AndroidBitmapInfo dadosImagem;                                  //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixels;                                              //ponteiro para referenciar os pixels da Imagem
    uint32_t *pixel;

    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem

    int **Red = (int **) (malloc(dadosImagem.height * sizeof(int *)));
    int **Blue = (int **) (malloc(dadosImagem.height * sizeof(int *)));
    int **Green = (int **) (malloc(dadosImagem.height * sizeof(int *)));

    int linha, coluna,i,j,green,blue,red;											    //indice genérico


    for (linha = 0; linha < dadosImagem.height; linha++) {
        Red[linha] = (int *) (malloc(dadosImagem.width * sizeof(int)));
        Blue[linha] = (int *) (malloc(dadosImagem.width * sizeof(int)));
        Green[linha] = (int *) (malloc(dadosImagem.width * sizeof(int)));
    }

    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel
            Blue [linha][coluna] = (int) ((pixel[coluna] & 0x00FF0000) >> 16);    //para extração dos bytes. Somente o valor do canal azul
            Green[linha][coluna] = (int) ((pixel[coluna] & 0x0000FF00) >> 8);     //para extração dos bytes. Somente o valor do canal verde
            Red  [linha][coluna] = (int)  (pixel[coluna] & 0x00000FF );           //para extração dos bytes. Somente o valor do canal vermelho
        }
        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem

    int levels = 90;
    int currentIntensity = 0;
    int maxIntensity = 0;
    int maxIndex = 0;
    int iLinha = 0;
    int jColuna = 0;

    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem

    for (iLinha = 0; iLinha < dadosImagem.height; iLinha++) {
        pixel = (uint32_t*)localPixels;
        for (jColuna = 0; jColuna < dadosImagem.width; jColuna++) {
            maxIntensity = maxIndex = 0;

            int intensityBin[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int blueBin[]      = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int greenBin[]     = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int redBin[]       = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


            for (i = iLinha - linhaMask; i <= iLinha + linhaMask; i++) {
                for (j = jColuna - colunaMask; j <= jColuna + colunaMask; j++) {

                    // verificar se está entre  0 e a largura da imagem
                    if ((i >= 0) && (i < dadosImagem.height) && (j >= 0) && (j < dadosImagem.width)) {

                        currentIntensity = ( ((Red[i][j] + Green[i][j] + Blue[i][j]) / 3) * levels) / 255;

                        intensityBin[currentIntensity]++;
                        redBin[currentIntensity]   +=   Red[i][j];
                        greenBin[currentIntensity] +=   Green[i][j];
                        blueBin[currentIntensity]  +=   Blue[i][j];

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

            if (red > 255)
                red = 255;
            if (red < 0)
                red = 0;
            if (green > 255)
                green = 255;
            if (green < 0)
                green = 0;
            if (blue > 255)
                blue = 255;
            if (blue < 0)
                blue = 0;

            pixel[jColuna] = (uint32_t) (((blue << 16) & 0x00FF0000) |
                                        ((green << 8) & 0x0000FF00) |
                                        ( red         & 0x000000FF));


        }
        localPixels = (char *)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem

    free(Red);
    free(Green);
    free(Blue);
}


