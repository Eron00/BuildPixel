package com.aplicacao.Processamento.ProcessamentoBinario;

import android.graphics.Bitmap;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesBinarias;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 30/08/2015.
 */
public class Truncamento implements OperacoesBinarias {
    private OperacoesBinarias EloCadeia;


    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesBinarias) ProximaOperacao;
    }
    @Override
    public void CalcularPixel(Bitmap fotoA, Bitmap fotoB, String Processo) {

             if(Processo.contains("Truncamento")) {
                NDK ndk = new NDK();
                 ndk.processamentoBinario(fotoA, fotoB, Processo);
             } else {
                 EloCadeia.CalcularPixel(fotoA, fotoB, Processo);
             }
    }
}
