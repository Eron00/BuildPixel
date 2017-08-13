#include <jni.h>
#include <android/bitmap.h>
#include "buildPixelNativeLib.h"
#include <stdlib.h>

#define PROG_TITLE "ZoaFoto"



JNIEXPORT void Java_com_aplicacao_Modelo_NDK_convolucao(JNIEnv *env, jobject instance, jobject foto, jstring mascara,jint linhaMascara, jint colunaMascara) {

    AndroidBitmapInfo dadosImagem;                                  //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixels;                                              //ponteiro para referenciar os pixels da Imagem
    int coluna, linha;
    uint32_t *pixel;

    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem

    int red  [dadosImagem.height][dadosImagem.width];
    int green[dadosImagem.height][dadosImagem.width];
    int blue [dadosImagem.height][dadosImagem.width];


    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel
            blue [linha][coluna] = (int) ((pixel[coluna] & 0x00FF0000) >> 16);
            green[linha][coluna] = (int) ((pixel[coluna] & 0x0000FF00) >> 8);
            red  [linha][coluna] = (int)  (pixel[coluna] & 0x00000FF );
        }
        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,foto);


    // para encontrar posicionamento da mascara na coordenada linha
    int linhaMask  = (linhaMascara - 1) / 2;
    // para encontrar posicionamento da mascara na coordenada coluna
    int colunaMask = (colunaMascara - 1) / 2;

    int iLinha, jColuna, i, j, iMascara,jMascara;

    const char *cNomeMascara = (*env)->GetStringUTFChars(env, mascara, 0);
    float dMascaraFiltro[linhaMascara][colunaMascara];
    PopularMascara(cNomeMascara, linhaMascara, colunaMascara , dMascaraFiltro);


    for (iLinha = 0; iLinha < dadosImagem.width; iLinha++) {
        for (jColuna = 0; jColuna < dadosImagem.height; jColuna++) {

            float somatoria[] = {0, 0, 0};

            for (i = iLinha - linhaMask, iMascara = 0; i <= iLinha + linhaMask; i++,iMascara++) {
                for (j = jColuna - colunaMask, jMascara = 0; j <= jColuna + colunaMask; j++, jMascara++) {

                    // verificar se está entre  0 e a largura da imagem
                    if ((i >= 0) && (i < dadosImagem.width) && (j >= 0) && (j < dadosImagem.height)) {
                        somatoria[0] += blue[i][j]  * dMascaraFiltro[iMascara][jMascara];
                        somatoria[1] += green[i][j] * dMascaraFiltro[iMascara][jMascara];
                        somatoria[2] += red[i][j]   * dMascaraFiltro[iMascara][jMascara];
                    }
                }

                if (somatoria[0] > 255) { somatoria[0] = 255; }
                else if (somatoria[0] < 0) { somatoria[0] = 0; }

                if (somatoria[1] > 255) { somatoria[1] = 255; }
                else if (somatoria[1] < 0) { somatoria[1] = 0; }

                if (somatoria[2] > 255) { somatoria[2] = 255; }
                else if (somatoria[2] < 0) { somatoria[2] = 0; }

                blue[i][j]  = (int) somatoria[0];
                green[i][j] = (int) somatoria[1];
                red[i][j]   = (int) somatoria[2];
            }

        }
    }

    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem
    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel

            pixel[coluna] = (uint32_t) ((( blue[linha][coluna] << 16) & 0x00FF0000) |
                                        ((green[linha][coluna] << 8)  & 0x0000FF00) |
                                        (   red[linha][coluna]             & 0x000000FF));
        }

        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem
}

void convolucao(JNIEnv *env, jobject instance,jobject foto, jstring mascara, jint linhaMascara, jint colunaMascara){
    AndroidBitmapInfo dadosImagem;                                  //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixels;                                              //ponteiro para referenciar os pixels da Imagem
    int coluna, linha;
    uint32_t *pixel;

    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem

    struct ARGB pixelTemp[dadosImagem.height][dadosImagem.width];


    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel
            pixelTemp[linha][coluna].blue  = (uint8_t) ((pixel[coluna] & 0x00FF0000) >> 16);
            pixelTemp[linha][coluna].green = (uint8_t) ((pixel[coluna] & 0x0000FF00) >> 8);
            pixelTemp[linha][coluna].red   = (uint8_t) (pixel[coluna] & 0x00000FF );
        }
        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    // para encontrar posicionamento da mascara na coordenada linha
    int linhaMask  = (linhaMascara - 1) / 2;
    // para encontrar posicionamento da mascara na coordenada coluna
    int colunaMask = (colunaMascara - 1) / 2;

    int iLinha, jColuna, i, j, iMascara,jMascara;

    const char *cNomeMascara = (*env)->GetStringUTFChars(env, mascara, 0);
    float dMascaraFiltro[linhaMascara][colunaMascara];
    PopularMascara(cNomeMascara, linhaMascara, colunaMascara , dMascaraFiltro);


    for (iLinha = 0; iLinha < dadosImagem.width; iLinha++) {
        for (jColuna = 0; jColuna < dadosImagem.height; jColuna++) {

            float somatoria[] = {0, 0, 0};

            for (i = iLinha - linhaMask, iMascara = 0; i <= iLinha + linhaMask; i++,iMascara++) {
                for (j = jColuna - colunaMask, jMascara = 0; j <= jColuna + colunaMask; j++, jMascara++) {

                    // verificar se está entre  0 e a largura da imagem
                    if ((i >= 0) && (i < dadosImagem.width) && (j >= 0) && (j < dadosImagem.height)) {
                        somatoria[0] += pixelTemp[i][j].blue  * dMascaraFiltro[iMascara][jMascara];
                        somatoria[1] += pixelTemp[i][j].green * dMascaraFiltro[iMascara][jMascara];
                        somatoria[2] += pixelTemp[i][j].red   * dMascaraFiltro[iMascara][jMascara];
                    }
                }

                if (somatoria[0] > 255) { somatoria[0] = 255; }
                else if (somatoria[0] < 0) { somatoria[0] = 0; }

                if (somatoria[1] > 255) { somatoria[1] = 255; }
                else if (somatoria[1] < 0) { somatoria[1] = 0; }

                if (somatoria[2] > 255) { somatoria[2] = 255; }
                else if (somatoria[2] < 0) { somatoria[2] = 0; }

                pixelTemp[i][j].blue  = (uint8_t) somatoria[0];
                pixelTemp[i][j].green = (uint8_t) somatoria[1];
                pixelTemp[i][j].red   = (uint8_t) somatoria[2];
            }

        }
    }

    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel

            pixel[coluna] = (uint32_t) (((pixelTemp[linha][coluna].blue << 16) & 0x00FF0000) |
                                        ((pixelTemp[linha][coluna].green << 8) & 0x0000FF00) |
                                        ( pixelTemp[linha][coluna].red         & 0x000000FF));
        }

        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem
}
