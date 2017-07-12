package com.aplicacao.Processamento.ProcessamentoBinario;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesBinarias;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 30/08/2015.
 *
 * Incluido operadores unários dia 23/09
 *
 * Classe para implementação do processo de duas imagens "Normalização"
 */
public class Normalizacao implements OperacoesBinarias{
    private OperacoesBinarias EloCadeia;

    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesBinarias) ProximaOperacao;

    }
    @Override
    public void CalcularPixel(int[] FotoA, int[] FotoB, int linha, int coluna, String Processo) {


            if (Processo.contains("Normalizacao")) {
                NDK ndk = new NDK();
                ndk.processamentoBinario(FotoA, FotoB, linha, coluna, Processo);
            } else {
                EloCadeia.CalcularPixel(FotoA, FotoB, linha, coluna, Processo);
            }
    }
}

