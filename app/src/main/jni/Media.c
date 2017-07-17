
#include <jni.h>
#include <android/bitmap.h>
#include "zoaFotoNativeLib.h"

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
    int coluna, linha, red, green, blue,alpha;
    uint32_t *pixel;



    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem

    ARGB pixelTemp[dadosImagem.height][dadosImagem.width];

    for(linha = 1; linha < (dadosImagem.height-1); linha++){         //inicializando para começar na segunda linha, para não haver acesso indevido de memória
        pixel = (uint32_t*)localPixels;
        for(coluna = 1; coluna < (dadosImagem.width-1); coluna++){    //inicializando para começar na segunda coluna, para não haver acesso indevido de memória
            //extração dos dados RGB do pixel
//**************************************************************************************************
            alpha  = (int)((pixel[coluna] & 0xFF000000) >> 24);

            //capturando os valores do azul
            //noroeste
            blue =(int) ((pixel[(linha-1)*dadosImagem.width+(coluna-1)] & 0x00FF0000) >> 16);
            //norte
            blue+=(int) ((pixel[(linha-1)*dadosImagem.width+(coluna)]   & 0x00FF0000) >> 16);
            //nordeste
            blue+=(int) ((pixel[(linha-1)*dadosImagem.width+(coluna+1)] & 0x00FF0000) >> 16);
            //leste
            blue+=(int) ((pixel[(linha)*dadosImagem.width+(coluna-1)]   & 0x00FF0000) >> 16);
            //centro
            blue+=(int) ((pixel[(linha)*dadosImagem.width+(coluna)]     & 0x00FF0000) >> 16);
            //oeste
            blue+=(int) ((pixel[(linha)*dadosImagem.width+(coluna+1)]   & 0x00FF0000) >> 16);
            //sudoeste
            blue+=(int) ((pixel[(linha+1)*dadosImagem.width+(coluna-1)] & 0x00FF0000) >> 16);
            //sul
            blue+=(int) ((pixel[(linha+1)*dadosImagem.width+(coluna)]   & 0x00FF0000) >> 16);
            //sudeste
            blue+=(int) ((pixel[(linha+1)*dadosImagem.width+(coluna+1)] & 0x00FF0000) >> 16);
//******************************************************************************************************
            //capturando os valores do verde
            //noroeste
            green =(int) ((pixel[(linha-1)*dadosImagem.width+(coluna-1)] & 0x0000FF00) >> 8);
            //norte
            green+=(int) ((pixel[(linha-1)*dadosImagem.width+(coluna)]   & 0x0000FF00) >> 8);
            //nordeste
            green+=(int) ((pixel[(linha-1)*dadosImagem.width+(coluna+1)] & 0x0000FF00) >> 8);
            //leste
            green+=(int) ((pixel[(linha)*dadosImagem.width+(coluna-1)]   & 0x0000FF00) >> 8);
            //centro
            green+=(int) ((pixel[(linha)*dadosImagem.width+(coluna)]     & 0x0000FF00) >> 8);
            //oeste
            green+=(int) ((pixel[(linha)*dadosImagem.width+(coluna+1)]   & 0x0000FF00) >> 8);
            //sudoeste
            green+=(int) ((pixel[(linha+1)*dadosImagem.width+(coluna-1)] & 0x0000FF00) >> 8);
            //sul
            green+=(int) ((pixel[(linha+1)*dadosImagem.width+(coluna)]   & 0x0000FF00) >> 8);
            //sudeste
            green+=(int) ((pixel[(linha+1)*dadosImagem.width+(coluna+1)] & 0x0000FF00) >> 8);

//*********************************************************************************************************************
            //capturando os valores do vermelho
            //noroeste
            red =(int) (pixel[(linha-1)*dadosImagem.width+(coluna-1)]  & 0x000000FF);
            //norte
            red+=(int) (pixel[(linha-1)*dadosImagem.width+(coluna)]    & 0x000000FF);
            //nordeste
            red+=(int) (pixel[(linha-1)*dadosImagem.width+(coluna+1)]  & 0x000000FF);
            //leste
            red+=(int) (pixel[(linha)*dadosImagem.width+(coluna-1)]    & 0x000000FF);
            //centro
            red+=(int) (pixel[(linha)*dadosImagem.width+(coluna)]      & 0x000000FF);
            //oeste
            red+=(int) (pixel[(linha)*dadosImagem.width+(coluna+1)]    & 0x000000FF);
            //sudoeste
            red+=(int) (pixel[(linha+1)*dadosImagem.width+(coluna-1)]  & 0x000000FF);
            //sul
            red+=(int) (pixel[(linha+1)*dadosImagem.width+(coluna)]    & 0x000000FF);
            //sudeste
            red+=(int) (pixel[(linha+1)*dadosImagem.width+(coluna+1)]  & 0x000000FF);

            blue/=9;
            red/=9;
            green/=9;
            
            // atribuindo novos valores ao pixel
            pixel[coluna] = (uint32_t)  ((alpha << 24)& 0xFF000000) |
                                        ((blue << 16) & 0x00FF0000) |
                                        ((green << 8) & 0x0000FF00) |
                                        (red          & 0x000000FF);
        }
        localPixels = (uint32_t*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem
}



