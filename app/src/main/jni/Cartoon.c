//
// Created by Eron on 29/05/2016.
//

//
// Created by Eron on 12/04/2016.
//
#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>
#include "buildPixelNativeLib.h"


JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_cartoon(JNIEnv *env, jobject instance, jobject FotoOriginal, jobject FotoResultante) {

    AndroidBitmapInfo dadosImagemOriginal,dadosImagemResultante;                       //Estrutura nativa dos dados da Imagem(Altura, largura,etc)
    void *localPixelsOriginal,*localPixelsImagemResultante;                             //ponteiro para referenciar os pixels da Imagem
    int red,green,blue,redResult,blueResult,greenResult
    ,linha,coluna,Pixel;
    uint32_t* pixelFotoOriginal;
    uint32_t* pixelFotoResultante;

    convolucao(env, instance, FotoResultante, "SobelHorizontal", 3, 3);
    convolucao(env, instance, FotoResultante, "SobelVertical"  , 3, 3);

    AndroidBitmap_getInfo(env, FotoResultante, &dadosImagemResultante);                 //capturando as informações da imagem e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_lockPixels(env, FotoResultante, &localPixelsImagemResultante);         //capturando os dados dos pixels


    for(linha = 0; linha < dadosImagemResultante.height; linha++){
        pixelFotoResultante = (uint32_t*)localPixelsImagemResultante;                            //carregando a próxima linha de pixels da imagem
        for(coluna =0; coluna < dadosImagemResultante.width; coluna++){

            //extração dos dados RGB do pixel
            blueResult  = (int)((pixelFotoResultante[coluna] & 0x00FF0000) >> 16);
            greenResult = (int)((pixelFotoResultante[coluna] & 0x0000FF00) >> 8);
            redResult   = (int) (pixelFotoResultante[coluna] & 0x00000FF );


            Pixel = (blueResult + greenResult + redResult )/3;                            //cinza media
            Pixel = 255 - Pixel;                                        //inverter

            //threshold
            if(Pixel > 200)
               Pixel = 255;
            else
                Pixel = 0;

            pixelFotoResultante[coluna] = (uint32_t) (((Pixel << 16) & 0x00FF0000) |
                                                      ((Pixel << 8)  & 0x0000FF00) |
                                                       (Pixel        & 0x000000FF));
        }

        localPixelsImagemResultante = (char*)localPixelsImagemResultante + dadosImagemResultante.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,FotoResultante);                         //liberando a memoria alocada para a imagem


    AndroidBitmap_getInfo(env, FotoResultante, &dadosImagemResultante);                 //capturando as informações da imagem e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_lockPixels(env, FotoResultante, &localPixelsImagemResultante);         //capturando os dados dos pixels

    AndroidBitmap_getInfo(env, FotoOriginal, &dadosImagemOriginal);                 //capturando as informações da imagem e bloqueando acesso ao local da memoria da imagem
    AndroidBitmap_lockPixels(env, FotoOriginal, &localPixelsOriginal);         //capturando os dados dos pixels


    for(linha = 0; linha < dadosImagemResultante.height; linha++){
        pixelFotoResultante = (uint32_t*)localPixelsImagemResultante;                            //carregando a próxima linha de pixels da imagem
        pixelFotoOriginal = (uint32_t*)localPixelsOriginal;                            //carregando a próxima linha de pixels da imagem

        for(coluna =0; coluna < dadosImagemResultante.width; coluna++){

            //extração dos dados RGB do pixel
            blueResult  = (int)((pixelFotoResultante[coluna] & 0x00FF0000) >> 16);
            greenResult = (int)((pixelFotoResultante[coluna] & 0x0000FF00) >> 8);
            redResult   = (int) (pixelFotoResultante[coluna] & 0x00000FF );


            blue  = (int)((pixelFotoOriginal[coluna] & 0x00FF0000) >> 16);
            green = (int)((pixelFotoOriginal[coluna] & 0x0000FF00) >> 8);
            red   = (int) (pixelFotoOriginal[coluna] & 0x00000FF );

            if (redResult > 10)
                redResult = red;

            if (greenResult > 10)
               greenResult = green;

            if (blueResult > 10)
               blueResult  = blue;


            pixelFotoOriginal[coluna] = (uint32_t) (((blueResult  << 16)& 0x00FF0000) |
                                                    ((greenResult << 8) & 0x0000FF00) |
                                                     (redResult         & 0x000000FF));
        }

        localPixelsImagemResultante = (char*)localPixelsImagemResultante + dadosImagemResultante.stride;    //pulando para a proxima linha da imagem
        localPixelsOriginal = (char*)localPixelsOriginal + dadosImagemOriginal.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,FotoResultante);                         //liberando a memoria alocada para a imagem
    AndroidBitmap_unlockPixels(env,FotoOriginal);                         //liberando a memoria alocada para a imagem

}

/*
void BubbleSort (int nVetor[], int nQTDE)
{
    bool flgtrocou;
    int i,nWork;

    do
    {
        for ( i = 0 ,flgtrocou = false; i < nQTDE - 1; i++)
        {
            if (nVetor[i] < nVetor[i+1])
            {
                nWork = nVetor[i];
                nVetor[i] = nVetor[i+1];
                nVetor[i+1] = nWork;
                flgtrocou = true;
            }//if
        }//for
    } while (flgtrocou);
}//BubbleSort

*/