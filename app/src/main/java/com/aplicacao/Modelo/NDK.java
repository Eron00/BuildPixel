package com.aplicacao.Modelo;

import android.graphics.Bitmap;

/**
 * Created by Eron on 12/03/2016.
 */
public class NDK {

    static {
        System.loadLibrary("buildPixelNativeLib");
    }

    public native void convolucao(Bitmap Foto, String NomeMascara, int linhaMascara, int colunaMascara);

    public native void media(Bitmap foto);

    public native void equalizar(Bitmap foto);

    public native void processamentoUnario(Bitmap Foto, String NomeProcesso);

    public native void celulaThreshold(Bitmap foto);

    public native void errorDifusion(Bitmap foto);

    public native void floydSteinberg(Bitmap foto);

    public native void cartoon(Bitmap FotoOriginal, Bitmap FotoResultante);

    public native void tintaoleo(Bitmap Foto);

    public native void processamentoBinario(Bitmap fotoA, Bitmap fotoB, String Processo);

    public native void teste(Bitmap foto);




}
