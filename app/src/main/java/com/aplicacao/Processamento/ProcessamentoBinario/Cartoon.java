package com.aplicacao.Processamento.ProcessamentoBinario;

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
    public void CalcularPixel(int[] FotoA, int[] FotoB, int linha, int coluna, String Processo) {
        if(Processo.equals("Cartoon")){
            NDK ndk = new NDK();
          //  ndk.tintaoleo(FotoA);
       //     ndk.convolucao(FotoB, "SobelHorizontal", linha,coluna,3,3);
            ndk.cartoon(FotoA,FotoB, linha, coluna);

        }
        else{
            EloCadeia.CalcularPixel(FotoA, FotoB, linha, coluna, Processo);

        }
    }
}
