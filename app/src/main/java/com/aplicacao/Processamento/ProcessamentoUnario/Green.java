package com.aplicacao.Processamento.ProcessamentoUnario;

import android.graphics.Bitmap;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesUnarias;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 17/09/2015.
 */
public class Green implements OperacoesUnarias {

    private OperacoesUnarias EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesUnarias) ProximaOperacao;
    }

    @Override
    public void CalcularPixel(Bitmap Foto, String Processo) {
        if (Processo.equals("Green")) {
            NDK ndk = new NDK();
            ndk.processamentoUnario(Foto, Processo);
        }
        else {
            EloCadeia.CalcularPixel(Foto, Processo);
        }
    }
}
