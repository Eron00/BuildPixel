
//
// Created by Eron on 11/07/2017.
//

#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>
#include "buildPixelNativeLib.h"

/*******************************************************************************************************
*----[Teste]--------------------------------------------------------------------------------------------
* - Data de Criação: 11/07/2017
* - Autor: Eron Thiago Reis Silva
* - Nome da função nativa: JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_teste
*
* - Descrição:  Função para testar o processamento de bitmaps de forma nativa. tem por objetivo retornar um
*  bitmap com foco no pixel vermelho, zerando o canal azul e verde.
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

JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_teste(JNIEnv *env, jobject instance, jobject foto) {

    AndroidBitmapInfo dadosImagem;                                  //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixels;                                              //ponteiro para referenciar os pixels da Imagem
    int coluna, linha, red, green, blue,Pixel;
    uint32_t* pixel;


    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels


    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel
            blue  = (int)((pixel[coluna] & 0x00FF0000) >> 16);
            green = (int)((pixel[coluna] & 0x0000FF00) >> 8);
            red   = (int) (pixel[coluna] & 0x00000FF );

            Pixel = (blue + green + red )/3;

            //Zerando os valores do canal azul e verde



//so the position of the south pixel is (linha+1)*info->width+coluna
            //and the one of the north is           (linha-1)*info->width+coluna
            //the left                               linha*info->width+coluna-1
            //the right                              linha*info->width+coluna+1
            // atribuindo novos valores ao pixel


            pixel[coluna] = (uint32_t) (((Pixel << 16) & 0x00FF0000) |
                                        ((Pixel << 8) & 0x0000FF00) |
                                        (Pixel        & 0x000000FF));
        }

        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem

}
