package com.aplicacao.Processamento.ProcessamentoUnario;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesUnarias;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 17/09/2015.
 */
public class Red implements OperacoesUnarias {

    private OperacoesUnarias EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesUnarias) ProximaOperacao;
    }

    @Override
    public void CalcularPixel(int[] Foto, int linha, int coluna, String Processo) {
        if (Processo.equals("Red")) {
            NDK ndk = new NDK();
            ndk.processamentoUnario(Foto, linha, coluna, Processo);
        }
        else {
            EloCadeia.CalcularPixel(Foto, linha, coluna, Processo);
        }

    }
}
