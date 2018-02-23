
package com.aplicacao.Processamento.ProcessamentoBinario;

import android.graphics.Bitmap;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesBinarias;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 09/04/2016.
 */
public class Cartoon implements OperacoesBinarias {
    private OperacoesBinarias EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesBinarias) ProximaOperacao;
    }

    @Override
    public void CalcularPixel(Bitmap FotoA, Bitmap FotoB, String Processo) {
        if(Processo.equals("Cartoon")){
            NDK ndk = new NDK();
            ndk.cartoon(FotoA,FotoB);
        }
        else{
            EloCadeia.CalcularPixel(FotoA, FotoB, Processo);
        }
    }
}
