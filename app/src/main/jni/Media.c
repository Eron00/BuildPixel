
#include <jni.h>
#include <android/bitmap.h>
#include "buildPixelNativeLib.h"

/*******************************************************************************************************
*----[Media]--------------------------------------------------------------------------------------------
* - Data de Criação: 20/03/2016
* - Autor: Eron Thiago Reis Silva
* - Nome da função nativa: JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_media
*
* - Descrição: Processar imagem utilizando como base uma área de 3x3 dos pixels. O resultado será a mé-
 * dia simples dessa área e o cálculo será realizado de forma separada em cada canal do RGB.
*
*********************************************************************************************************
*	PARÂMETROS:
*********************************************************************************************************
*		ENTRADA:
*
*			JNIEnv *env - ponteiro de referência para VM do Java. (classe que chama a função).
*
*			jobject instance - ponteiro de referência para o objeto this implicito passado pelo Java.?.(
*
*			jobject foto - objeto que faz referência ao Bitmap da imagem a ser processada
*
 ********************************************************************************************************
*		SAÍDA: nenhum
 ********************************************************************************************************
*/

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_media(JNIEnv *env, jobject instance, jobject foto) {

    AndroidBitmapInfo dadosImagem;                                  //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixels;                                              //ponteiro para referenciar os pixels da Imagem
    int coluna, linha;
    uint32_t *pixel;

    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    struct ARGB pixelTemp[dadosImagem.height][dadosImagem.width];          //struct da imagem

    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel
            pixelTemp[linha][coluna].blue  = (uint8_t) ((pixel[coluna] & 0x00FF0000) >> 16);
            pixelTemp[linha][coluna].green = (uint8_t) ((pixel[coluna] & 0x0000FF00) >> 8);
            pixelTemp[linha][coluna].red   = (uint8_t)  (pixel[coluna] & 0x00000FF );
        }
        localPixels = (char *)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    for(linha = 1; linha < (dadosImagem.height-1); linha++){          //inicializando para começar na segunda linha, para não haver acesso indevido de memória
        for(coluna = 1; coluna < (dadosImagem.width-1); coluna++){    //inicializando para começar na segunda coluna, para não haver acesso indevido de memória

            //calculando os valores da média do azul
                                pixelTemp[linha  ][coluna  ].blue =
                    (uint8_t) ((pixelTemp[linha-1][coluna-1].blue + 	  //noroeste
                                pixelTemp[linha-1][coluna  ].blue + 	  //norte
                                pixelTemp[linha-1][coluna+1].blue + 	  //nordeste
                                pixelTemp[linha  ][coluna-1].blue + 	  //leste
                                pixelTemp[linha  ][coluna  ].blue + 	  //centro
                                pixelTemp[linha  ][coluna+1].blue + 	  //oeste
                                pixelTemp[linha+1][coluna-1].blue + 	  //sudoeste
                                pixelTemp[linha+1][coluna  ].blue + 	  //sul
                                pixelTemp[linha+1][coluna+1].blue) / 9);  //sudeste

            //calculando os valores da média do verde
                                pixelTemp[linha  ][coluna  ].green =
                    (uint8_t) ((pixelTemp[linha-1][coluna-1].green + 	   //noroeste
                                pixelTemp[linha-1][coluna  ].green + 	   //norte
                                pixelTemp[linha-1][coluna+1].green + 	   //nordeste
                                pixelTemp[linha  ][coluna-1].green + 	   //leste
                                pixelTemp[linha  ][coluna  ].green + 	   //centro
                                pixelTemp[linha  ][coluna+1].green + 	   //oeste
                                pixelTemp[linha+1][coluna-1].green + 	   //sudoeste
                                pixelTemp[linha+1][coluna  ].green + 	   //sul
                                pixelTemp[linha+1][coluna+1].green) / 9);  //sudeste

            //calculando os valores da média do vermelho
                                pixelTemp[linha  ][coluna  ].red  =
                    (uint8_t) ((pixelTemp[linha-1][coluna-1].red + 	     //noroeste
                                pixelTemp[linha-1][coluna  ].red + 	     //norte
                                pixelTemp[linha-1][coluna+1].red + 	     //nordeste
                                pixelTemp[linha  ][coluna-1].red + 	     //leste
                                pixelTemp[linha  ][coluna  ].red + 	     //centro
                                pixelTemp[linha  ][coluna+1].red + 	     //oeste
                                pixelTemp[linha+1][coluna-1].red + 	     //sudoeste
                                pixelTemp[linha+1][coluna  ].red + 	     //sul
                                pixelTemp[linha+1][coluna+1].red) / 9);  //sudeste
        }

    }

    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //remontando o pixel com os valores processados
            pixel[coluna] = (uint32_t)
                            ((pixelTemp[linha][coluna].blue  << 16) & 0x00FF0000) |
                            ((pixelTemp[linha][coluna].green << 8)  & 0x0000FF00) |
                            ( pixelTemp[linha][coluna].red          & 0x000000FF);
        }
        localPixels = (char *)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,foto);                          //liberando a memoria alocada para a imagem

}

