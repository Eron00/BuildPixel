package com.aplicacao.Processamento.ProcessamentoArea;

import android.graphics.Bitmap;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesArea;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 05/09/2015.
 */
public class Sobel implements OperacoesArea {
    private OperacoesArea EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesArea) ProximaOperacao;
    }

    @Override
    public void CalcularFoto(Bitmap Foto, String NomeClasse) {
        if (NomeClasse != "SobelVertical" && NomeClasse != "SobelHorizontal") {
            EloCadeia.CalcularFoto(Foto, NomeClasse);
        } else {
                NDK ndk = new NDK();
                ndk.convolucao(Foto, NomeClasse, 3, 3);
        }
    }
}
