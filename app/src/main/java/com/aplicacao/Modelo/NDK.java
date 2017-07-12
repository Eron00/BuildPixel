package com.aplicacao.Modelo;

/**
 * Created by Eron on 12/03/2016.
 */
public class NDK {

    static {
        System.loadLibrary("zoaFotoNativeLib");
    }

    public native int convolucao(int[] Foto, String NomeMascara, int linha, int coluna, int linhaMascara, int colunaMascara);

    public native void media(int[] Foto, int linha, int coluna);

    public native void equalizar(int[] Foto, int linha, int coluna);

    public native void processamentoUnario(int[] Foto, int linha, int coluna, String NomeProcesso);

    public native void halftone(int[] Foto, int linha, int coluna);

    public native void errorDifusion(int[] Foto, int linha, int coluna);

    public native void floydSteinberg(int[] Foto, int linha, int coluna);

    public native void cartoon(int[] FotoOriginal, int[] FotoResultante, int linha, int coluna);

    public native void tintaoleo(int[] Foto, int linha, int coluna);

    public native void processamentoBinario(int[] FotoA, int[] FotoB, int linha, int coluna, String Processo);

}
