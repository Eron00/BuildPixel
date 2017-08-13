#include <jni.h>
#include <android/bitmap.h>
#include "buildPixelNativeLib.h"
#include <stdlib.h>

/*******************************************************************************************************
*----[Equalizar]--------------------------------------------------------------------------------------------
* - Data de Criação: 23/03/2016
* - Autor: Eron Thiago Reis Silva
* - Nome da função nativa: JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_equalizar
*
* - Descrição: Busca realçar o contraste da imagem, utilizando o método de equalização de histograma
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
JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_equalizar(JNIEnv *env, jobject instance, jobject foto) {


    AndroidBitmapInfo dadosImagem;                                  //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixels;                                              //ponteiro para referenciar os pixels da Imagem
    uint32_t *pixel;

    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem

    int *histogramaAbsR = (int *) (malloc(256 * sizeof(int)));			//alocando memoria para o vetor do histograma absoluto do canal vermelho
    int *histogramaAbsG = (int *) (malloc(256 * sizeof(int)));			//alocando memoria para o vetor do histograma absoluto do canal verde
    int *histogramaAbsB = (int *) (malloc(256 * sizeof(int)));			//alocando memoria para o vetor do histograma absoluto do canal azul
    double *fdpAcumuladaR = (double *) (malloc(256 * sizeof(double)));
    double *fdpAcumuladaG = (double *) (malloc(256 * sizeof(double)));
    double *fdpAcumuladaB = (double *) (malloc(256 * sizeof(double)));

    struct ARGB pixelTemp[dadosImagem.height][dadosImagem.width];				//estrutura para extração e calculo dos valores dos pixels
    int linha, coluna,i;											    //indice genérico


    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel
            pixelTemp[linha][coluna].blue  = (uint8_t) ((pixel[coluna] & 0x00FF0000) >> 16);    //para extração dos bytes. Somente o valor do canal azul
            pixelTemp[linha][coluna].green = (uint8_t) ((pixel[coluna] & 0x0000FF00) >> 8);     //para extração dos bytes. Somente o valor do canal verde
            pixelTemp[linha][coluna].red   = (uint8_t)  (pixel[coluna] & 0x00000FF );           //para extração dos bytes. Somente o valor do canal vermelho
        }
        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }


    for (i = 0; i < 256; i++) {
        //inicialização dos valores dos vetores
        fdpAcumuladaR[i] = 0;
        fdpAcumuladaG[i] = 0;
        fdpAcumuladaB[i] = 0;
        histogramaAbsR[i] = 0;
        histogramaAbsG[i] = 0;
        histogramaAbsB[i] = 0;
    }


    int indiceRed   = 0;
    int indiceGreen = 0;
    int indiceBlue  = 0;


    for (linha = 0; linha < dadosImagem.width; linha++) {
        for (coluna = 0; coluna < dadosImagem.height; coluna++) {
            //extração do valor do pixel
            indiceRed   = (int) pixelTemp[linha][coluna].red;
            indiceGreen = (int) pixelTemp[linha][coluna].green;
            indiceBlue  = (int) pixelTemp[linha][coluna].blue;

            //indice do vetor de 0 a 255.
            //Para cada ocorrência, atribui +1 ao valor.
            histogramaAbsR[indiceRed]++;
            histogramaAbsG[indiceGreen]++;
            histogramaAbsB[indiceBlue]++;
        }
    }

    for (i = 0; i < 256; i++) {
        fdpAcumuladaR[i] = histogramaAbsR[i];
        fdpAcumuladaG[i] = histogramaAbsG[i];
        fdpAcumuladaB[i] = histogramaAbsB[i];

    }

    for (i = 1; i < 256; i++) {
        fdpAcumuladaR[i] = fdpAcumuladaR[i - 1] + histogramaAbsR[i];
        fdpAcumuladaB[i] = fdpAcumuladaB[i - 1] + histogramaAbsB[i];
        fdpAcumuladaG[i] = fdpAcumuladaG[i - 1] + histogramaAbsG[i];
    }


    uint8_t AcumuladaR = 0;
    uint8_t AcumuladaG = 0;
    uint8_t AcumuladaB = 0;


    for (linha = 0; linha < dadosImagem.height; linha++) {
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for (coluna = 0; coluna < dadosImagem.width; coluna++) {
            indiceRed   = (int) pixelTemp[linha][coluna].red;
            indiceGreen = (int) pixelTemp[linha][coluna].green;
            indiceBlue  = (int) pixelTemp[linha][coluna].blue;

            /*
               Fórmula:   Vp * 255
                         ----------
                          Pl * Pc
            Vpc =
            Pl  = posição da linha da imagem
            pc  = posição da coluna da imagem
            */
            AcumuladaR = (uint8_t) ((fdpAcumuladaR[indiceRed]   * 255) / (linha * coluna));
            AcumuladaG = (uint8_t) ((fdpAcumuladaG[indiceGreen] * 255) / (linha * coluna));
            AcumuladaB = (uint8_t) ((fdpAcumuladaB[indiceBlue]  * 255) / (linha * coluna));


            //montando o pixel da imagem com os novos valores para cada canal
            pixel[coluna] = (uint32_t)  (((AcumuladaB << 16)& 0x00FF0000) |
                                         ((AcumuladaG << 8) & 0x0000FF00) |
                                         ( AcumuladaR       & 0x000000FF));
        }
        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    //liberando memória
    free(fdpAcumuladaR);
    free(fdpAcumuladaG);
    free(fdpAcumuladaB);
    free(histogramaAbsR);
    free(histogramaAbsG);
    free(histogramaAbsB);

    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem

}