package com.aplicacao.Modelo;

import android.graphics.Bitmap;

/**
 * Created by Eron on 12/03/2016.
 */
public class NDK {

    static {
        System.loadLibrary("zoaFotoNativeLib");
    }

    public native int convolucao(Bitmap Foto, String NomeMascara, int linhaMascara, int colunaMascara);

    public native void media(Bitmap foto);

    public native void equalizar(Bitmap foto);

    public native void processamentoUnario(Bitmap Foto, String NomeProcesso);

    public native void halftone(Bitmap foto);

    public native void errorDifusion(Bitmap foto);

    public native void floydSteinberg(Bitmap foto);

    public native void cartoon(int[] FotoOriginal, int[] FotoResultante, int linha, int coluna);

    public native void tintaoleo(Bitmap Foto);

    public native void processamentoBinario(int[] FotoA, int[] FotoB, int linha, int coluna, String Processo);

    public native void teste(Bitmap foto);

    public native void sepia(Bitmap foto);


}
