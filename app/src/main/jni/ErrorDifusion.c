//
// Created by Eron on 02/04/2016.
//
#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>
#include "buildPixelNativeLib.h"


/*******************************************************************************************************
*----[ErrorDiffusion]--------------------------------------------------------------------------------------------
* - Data de Criação: 02/04/2016
* - Autor: Eron Thiago Reis Silva
* - Nome da função nativa: JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_errorDifusion
*
* - Descrição: Função que utiliza uma variação do processo de halftone. Onde um valor  é modificado após
* realizar o calculo com uma determinada área.
* Nessa área cria-se uma distorção dos valores e essas distoções gera o efeito final da imagem.
*
* - Padrão:  Escala de Cinza
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


JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_errorDifusion(JNIEnv *env, jobject instance,jobject foto) {


    int linha, coluna;
    int ErroQuantizado;
    int ErroTotal,blue,green,red;

    ErroQuantizado = 0;                                             //inteira para armazenar o erro calculado dos pixels
    AndroidBitmapInfo dadosImagem;                                  // variavel com os dados estruturais da imagem
    void *localPixels;                                              // ponteiro que carrega as informações dos pixels
    uint32_t *pixel;                                                // variavel local para cálculo das informações dos pixels

    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem

    int Cinza[dadosImagem.height][dadosImagem.width];


//****************************************************************************************************************************************************

    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){
            //extração dos dados RGB do pixel
            blue  = ((pixel[coluna] & 0x00FF0000) >> 16);
            green = ((pixel[coluna] & 0x0000FF00) >> 8);
            red   =  (pixel[coluna] & 0x00000FF );

            //criando o pixel com escala de cinza
            Cinza[linha][coluna]  = ( red + green + blue) / 3;
        }
        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,foto);

//***************************************************************************************************************************************************
    for (linha = 1; linha < dadosImagem.height; linha++) {
        for (coluna = 1;  coluna< dadosImagem.width ; coluna++) {
            //soma do valor atual do pixel com o erro que foi ou será gerado.
            ErroTotal = (Cinza[linha][coluna] + ErroQuantizado);

            if(ErroTotal > 127)
              Cinza[linha][coluna] = 255;

            else
              Cinza[linha][coluna] = 0;
            //após  verificar os valores, regerar o erro para o próximo pixel.
            ErroQuantizado = (ErroTotal -  Cinza[linha][coluna]);
        }
    }
// *****************************************************************************************************************************************************

    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem
    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){
            //remontando o pixel com os valores processados
            pixel[coluna] = (uint32_t) (((Cinza[linha][coluna] << 16) & 0x00FF0000) |
                                        ((Cinza[linha][coluna] << 8)  & 0x0000FF00) |
                                         (Cinza[linha][coluna]        & 0x000000FF));
        }
        localPixels = (char *)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,foto);
}
