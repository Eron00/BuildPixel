//
// Created by Eron on 11/07/2017.
//

#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>

/*******************************************************************************************************
*----[Teste]--------------------------------------------------------------------------------------------
* - Data de Criação: 11/07/2017
* - Autor: Eron Thiago Reis Silva
* - Nome da função: JNIEXPORT void JNICALL Java_com_aplicacao_Modelo_NDK_teste
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

    AndroidBitmapInfo dadosImagem;
    void *localPixels;
    AndroidBitmap_getInfo(env, foto, &dadosImagem);
    AndroidBitmap_lockPixels(env, foto, &localPixels);


    int xx, yy, red, green, blue;
    uint32_t* line;

    for(yy = 0; yy < dadosImagem.height; yy++){
        line = (uint32_t*)localPixels;
        for(xx =0; xx < dadosImagem.width; xx++){

            //extract the RGB values from the pixel
            blue  = (int)((line[xx] & 0x00FF0000) >> 16);
            green = (int)((line[xx] & 0x0000FF00) >> 8);
            red   = (int) (line[xx] & 0x00000FF );

            //change the RGB values
            blue = 0;
            green = 0;

            // set the new pixel back in
            line[xx] =
                    ((blue << 16) & 0x00FF0000) |
                    ((green << 8) & 0x0000FF00) |
                    (red & 0x000000FF);
        }

        localPixels = (char*)localPixels + dadosImagem.stride;
    }
    AndroidBitmap_unlockPixels(env,foto);

}
