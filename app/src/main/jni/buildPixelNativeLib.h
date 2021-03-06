#include <jni.h>
#include <android/log.h>
//
// Created by Eron on 12/03/2016.
//

#ifndef TESTE_ZOAFOTONATIVELIB_H
#define TESTE_ZOAFOTONATIVELIB_H

#endif //TESTE_ZOAFOTONATIVELIB_H

// cabeçalho das mensagens de estado do android/ "LOG" + "I" informação
#define LOGI(...) __android_log_print (ANDROID_LOG_INFO, PROG_TITLE, __VA_ARGS__);

// cabeçalho / "LOG" + "E"rro
#define LOGE(...) __android_log_print (ANDROID_LOG_ERROR, PROG_TITLE,__VA_ARGS__);

typedef struct ARGB
{
    //estrutura para manupulação da imagem
    uint8_t alpha;
    uint8_t red;
    uint8_t green;
    uint8_t blue;

}ARGB;

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_convolucao(JNIEnv *env, jobject instance, jobject foto,jstring mascara, jint linhaMascara, jint colunaMascara);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_media(JNIEnv *env, jobject instance, jobject foto);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_equalizar(JNIEnv *env, jobject instance, jobject foto);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_processamentoUnario(JNIEnv *env, jobject instance, jobject Foto, jstring cNomeProcesso);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_celulaThreshold(JNIEnv *env, jobject instance,jobject foto);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_errorDifusion(JNIEnv *env, jobject instance,jobject foto);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_floydSteinberg(JNIEnv *env, jobject instance, jintArray FotoResultante, jint linha, jint coluna);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_cartoon(JNIEnv *env, jobject instance, jobject FotoOriginal,jobject FotoResultante);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_tintaoleo(JNIEnv *env, jobject instance,jobject foto);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_processamentoBinario(JNIEnv *env, jobject instance, jobject FotoA, jobject FotoB, jstring cNomeProcesso);

JNIEXPORT void JNICALL
        Java_com_aplicacao_Modelo_NDK_teste(JNIEnv *env, jobject instance, jobject foto);



void convolucao(JNIEnv *env, jobject instance, jobject foto, char* mascara, int linhaMascara, int colunaMascara);

void PopularMascara(const char *cNomeProcessamento , int nLinhasMascara, int nColunasMascara, float dMascaraFiltro[nLinhasMascara][nColunasMascara]);

void tintaoleo(JNIEnv *env, jobject instance,jobject foto);

void processamentoUnario(JNIEnv *env, jobject instance, jintArray FotoResultante, jint linha, jint coluna, jstring cNomeProcesso);

