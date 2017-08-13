//
// Created by Eron on 02/04/2016.
//
#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>
JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_celulaThreshold(JNIEnv *env, jobject instance,jobject foto) {

    int linha, coluna;
    int Pixel,blue,green,red;

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
            Cinza[linha][coluna]  = (red + green + blue) / 3;
        }
        localPixels = (char*)localPixels + dadosImagem.stride;    //pulando para a proxima linha da imagem
    }
    AndroidBitmap_unlockPixels(env,foto);

//***************************************************************************************************************************************************
    for (linha = 0; linha < dadosImagem.height -1; linha+=2) {
        for (coluna = 0;  coluna< dadosImagem.width-1 ; coluna+=2) {
            //soma do valor atual do pixel com o erro que foi ou será gerado.
            Pixel  = Cinza[linha][coluna];
            Pixel += Cinza[linha][coluna + 1];
            Pixel += Cinza[linha + 1][coluna];
            Pixel += Cinza[linha + 1][coluna + 1];


            if (Pixel > (1 * 1024) / 8)
                Cinza[linha][coluna] = 255;
            else
                Cinza[linha][coluna] = 0;


            if (Pixel > (3 * 1024) / 8)
                Cinza[linha +1][coluna +1] = 255;
            else
                Cinza[linha +1][coluna +1] = 0;


            if (Pixel > (5 * 1024) / 8)
                Cinza[linha +1][coluna] = 255;
            else
                Cinza[linha +1][coluna] = 0;


            if (Pixel > (7 * 1024) / 8)
                Cinza[linha][coluna+1] = 255;
            else
                Cinza[linha][coluna+1] = 0;

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