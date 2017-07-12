package com.aplicacao.Processamento.ProcessamentoArea;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesArea;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 23/09/2015.
 */
public class FreiChen implements OperacoesArea {
    private OperacoesArea EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesArea) ProximaOperacao;
    }

    @Override
    public void CalcularFoto(int[] Foto, int linha, int coluna, String NomeClasse) {
        if (NomeClasse != "FreiChenVertical" && NomeClasse != "FreiChenHorizontal") {
            EloCadeia.CalcularFoto(Foto,linha ,coluna,NomeClasse);
        }
        else {
                NDK ndk = new NDK();
                ndk.convolucao(Foto, NomeClasse, linha, coluna, 3, 3);
            }
        }
    }
