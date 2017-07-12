package com.aplicacao.Processamento.ProcessamentoUnario;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesUnarias;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 22/03/2016.
 */
public class Magenta implements OperacoesUnarias {
    private OperacoesUnarias EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesUnarias) ProximaOperacao;
    }

    @Override
    public void CalcularPixel(int[] Foto, int linha, int coluna, String Processo) {
        if (Processo.equals("Magenta")) {
            NDK ndk = new NDK();
            ndk.processamentoUnario(Foto, linha, coluna, Processo);
        }
        else {
            EloCadeia.CalcularPixel(Foto, linha, coluna, Processo);
        }

    }
}
