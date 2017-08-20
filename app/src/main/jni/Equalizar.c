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
    int **Red = (int **) (malloc(dadosImagem.height * sizeof(int *)));
    int **Blue = (int **) (malloc(dadosImagem.height * sizeof(int *)));
    int **Green = (int **) (malloc(dadosImagem.height * sizeof(int *)));
    int linha, coluna,i,green,blue,red;											    //indice genérico


    for (linha = 0; linha < dadosImagem.height; linha++) {
        Red[linha] = (int *) (malloc(dadosImagem.width * sizeof(int)));
        Blue[linha] = (int *) (malloc(dadosImagem.width * sizeof(int)));
        Green[linha] = (int *) (malloc(dadosImagem.width * sizeof(int)));
    }


    for (linha = 0; linha < dadosImagem.height; linha++) {
        for (coluna = 0; coluna < dadosImagem.width; coluna++) {
            Red  [linha][coluna] = 0;
            Green[linha][coluna] = 0;
            Blue [linha][coluna] = 0;
        }
    }
    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){

            //extração dos dados RGB do pixel
           blue = (int) ((pixel[coluna] & 0x00FF0000) >> 16);    //para extração dos bytes. Somente o valor do canal azul
            green  = (int) ((pixel[coluna] & 0x0000FF00) >> 8);     //para extração dos bytes. Somente o valor do canal verde
            red  = (int)  (pixel[coluna] & 0x00000FF );           //para extração dos bytes. Somente o valor do canal vermelho

            Red  [linha][coluna] = red;
            Green[linha][coluna] = green;
            Blue [linha][coluna] = blue;
        }
        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }

    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem

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


    for (linha = 0; linha < dadosImagem.height; linha++) {
        for (coluna = 0; coluna < dadosImagem.width; coluna++) {
            //extração do valor do pixel
            indiceRed   =  Red   [linha][coluna];
            indiceGreen =  Green [linha][coluna];
            indiceBlue  =  Blue  [linha][coluna];

            //indice do vetor de 0 a 255.
            //Para cada ocorrência, atribui +1 ao valor.
            histogramaAbsR[indiceRed]++;
            histogramaAbsG[indiceGreen]++;
            histogramaAbsB[indiceBlue]++;
        }
    }

    for (i = 0; i < 256; i++) {
        fdpAcumuladaR[i] =(double) histogramaAbsR[i];
        fdpAcumuladaG[i] = (double )histogramaAbsG[i];
        fdpAcumuladaB[i] = (double )histogramaAbsB[i];

    }

    for (i = 1; i < 256; i++) {
        fdpAcumuladaR[i] =fdpAcumuladaR[i - 1] + histogramaAbsR[i];
        fdpAcumuladaB[i] = fdpAcumuladaB[i - 1] + histogramaAbsB[i];
        fdpAcumuladaG[i] = fdpAcumuladaG[i - 1] + histogramaAbsG[i];
    }


    int AcumuladaR = 0;
    int AcumuladaG = 0;
    int AcumuladaB = 0;

    for (linha = 0; linha < dadosImagem.height; linha++) {
        for (coluna = 0; coluna < dadosImagem.width; coluna++) {
            indiceRed   = (int) Red   [linha][coluna];
            indiceGreen = (int) Green [linha][coluna];
            indiceBlue  = (int) Blue  [linha][coluna];

            /*
               Fórmula:   Vp * 255
                         ----------
                          Pl * Pc
            Vpc =
            Pl  = posição da linha da imagem
            pc  = posição da coluna da imagem
            */
            AcumuladaR = (int) ((fdpAcumuladaR[indiceRed]   * 255) / (dadosImagem.height * dadosImagem.width));
            AcumuladaG = (int) ((fdpAcumuladaG[indiceGreen] * 255) / (dadosImagem.height * dadosImagem.width));
            AcumuladaB = (int) ((fdpAcumuladaB[indiceBlue]  * 255) / (dadosImagem.height * dadosImagem.width));

            Red[linha][coluna] = AcumuladaR;
            Green[linha][coluna] = AcumuladaG;
            Blue[linha][coluna] = AcumuladaB;

        }
    }
    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem
    for(linha = 0; linha < dadosImagem.height; linha++){
        pixel = (uint32_t*)localPixels;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagem.width; coluna++){
            //remontando o pixel com os valores processados
            pixel[coluna] = (uint32_t) (((Blue[linha][coluna] << 16) & 0x00FF0000) |
                                        ((Green[linha][coluna] << 8) & 0x0000FF00) |
                                        ( Red[linha][coluna]         & 0x000000FF));
        }
        localPixels = (char *)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
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