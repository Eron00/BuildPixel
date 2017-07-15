
#include <jni.h>
#include <android/bitmap.h>

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

    AndroidBitmapInfo dadosImagem,dadosImagemTemp;                                  //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixels,*localPixelsTemp;                                              //ponteiro para referenciar os pixels da Imagem
    int coluna, linha, red, green, blue;
    uint32_t *pixel,*pixelTemp;


    AndroidBitmap_getInfo(env, foto, &dadosImagem);                 //capturando as informações da imagem
    AndroidBitmap_lockPixels(env, foto, &localPixels);              //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_getInfo(env, foto, &dadosImagemTemp);             //capturando as informações da imagem (cópia auxiliar)
    AndroidBitmap_lockPixels(env, foto, &localPixelsTemp);          //capturando os dados dos pixels e bloqueando acesso ao local da memoria da imagem (cópia auxiliar)


    for(linha = 1; linha < dadosImagem.height -1; linha++){         //inicializando para começar na segunda linha, para não haver acesso indevido de memória
        pixel = (uint32_t*)localPixels;                             //carregando a próxima linha de pixels da imagem
        pixelTemp = (uint32_t*)localPixelsTemp;                     //carregando a próxima linha de pixels da imagem
        for(coluna =1; coluna < dadosImagem.width -1; coluna++){    //inicializando para começar na segunda coluna, para não haver acesso indevido de memória

            //extração dos dados RGB do pixel
            blue  = (int)
                //noroeste
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna-1]   & 0x00FF0000) >> 16) +
                //norte
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna]     & 0x00FF0000) >> 16) +
                //nordeste
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna+1]   & 0x00FF0000) >> 16) +
                //leste
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna-1]   & 0x00FF0000) >> 16) +
                //centro
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna]     & 0x00FF0000) >> 16) +
                //oeste
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna+1]   & 0x00FF0000) >> 16) +
                //sudoeste
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+coluna-1]   & 0x00FF0000) >> 16) +
                //sul
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+coluna]     & 0x00FF0000) >> 16) +
                //sudeste
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+(coluna+1)] & 0x00FF0000) >> 16) /9;

            green  = (int)
                //noroeste
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna-1]   & 0x00FF0000) >> 8) +
                //norte
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna]     & 0x00FF0000) >> 8) +
                //nordeste
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna+1]   & 0x00FF0000) >> 8) +
                //leste
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna-1]   & 0x00FF0000) >> 8) +
                //centro
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna]     & 0x00FF0000) >> 8) +
                //oeste
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna+1]   & 0x00FF0000) >> 8) +
                //sudoeste
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+coluna-1]   & 0x00FF0000) >> 8) +
                //sul
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+coluna]     & 0x00FF0000) >> 8) +
                //sudeste
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+(coluna+1)] & 0x00FF0000) >> 8) /9;

            red  = (int)
                //noroeste
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna-1]   & 0x00FF0000)) +
                //norte
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna]     & 0x00FF0000)) +
                //nordeste
                ((pixelTemp[(linha-1)*dadosImagemTemp.width+coluna+1]   & 0x00FF0000)) +
                //leste
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna-1]   & 0x00FF0000)) +
                //centro
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna]     & 0x00FF0000)) +
                //oeste
                ((pixelTemp[(linha)  *dadosImagemTemp.width+coluna+1]   & 0x00FF0000)) +
                //sudoeste
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+coluna-1]   & 0x00FF0000)) +
                //sul
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+coluna]     & 0x00FF0000)) +
                //sudeste
                ((pixelTemp[(linha+1)*dadosImagemTemp.width+(coluna+1)] & 0x00FF0000)) /9;

            // atribuindo novos valores ao pixel
            pixel[coluna] = (uint32_t) (((blue << 16) & 0x00FF0000) | ((green << 8) & 0x0000FF00) | (red & 0x000000FF));
        }

        localPixels     = (char*)localPixels + dadosImagem.stride;        //pulando para a proxima linha da imagem
        localPixelsTemp = (char*)localPixels + dadosImagemTemp.stride;    //pulando para a proxima linha da imagem

        //so the position of the south pixel is (linha+1)*info->width+coluna
        //and the one of the north is           (linha-1)*info->width+coluna
        //the left                               linha*info->width+coluna-1
        //the right                              linha*info->width+coluna+1
    }

    AndroidBitmap_unlockPixels(env,foto);                         //liberando a memoria alocada para a imagem
}



