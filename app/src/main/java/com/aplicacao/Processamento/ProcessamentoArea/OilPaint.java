package com.aplicacao.Processamento.ProcessamentoArea;

import android.graphics.Bitmap;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesArea;
import com.aplicacao.Modelo.NDK;


/**
 * Created by Eron on 14/04/2016.
 */
public class OilPaint implements OperacoesArea {
    private OperacoesArea EloCadeia;

    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesArea) ProximaOperacao;
    }

    @Override
    public void CalcularFoto(Bitmap Foto, String Processo) {
        if (Processo != "OilPaint") {
            EloCadeia.CalcularFoto(Foto, Processo);
        }  else{
            NDK ndk = new NDK();
            ndk.tintaoleo(Foto);
        }
    }
}



