package com.aplicacao.Processamento.ProcessamentoArea;

import android.graphics.Bitmap;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesArea;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 25/09/2015.
 */
public class ErrorDiffusion implements OperacoesArea {
    private OperacoesArea EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesArea) ProximaOperacao;
    }

    @Override
    public void CalcularFoto(Bitmap Foto, String NomeClasse) {

        if (NomeClasse != "ErrorDiffusion") {
            EloCadeia.CalcularFoto(Foto, NomeClasse);
        } else {
            NDK ndk = new NDK();

            ndk.errorDifusion(Foto);

            /*
            int linha  = CalcularFoto.getLinha();
            int coluna = CalcularFoto.getColuna();

            int PropagedError;
            int TotalError;

            PropagedError = 0;
            TotalError = 0;

            Imagem ImagemResultante = new Imagem(linha,coluna);
            Imagem PreImagem = new Imagem(linha,coluna);

            for (int i = 0; i < linha; i++) {
                for (int j = 0; j < coluna; j++) {

                    int Pixel = (int)(( CalcularFoto.getR(i, j) + CalcularFoto.getG(i, j) + CalcularFoto.getB(i, j))/3d);
                    PreImagem.setRGB(i, j, Pixel, Pixel, Pixel);
                }
            }
            for (int i = 1; i < linha; i++) {
                for (int j = 1; j < coluna; j++) {

                    TotalError = PreImagem.getR(i,j) + PropagedError;

                    if(TotalError > 127)
                        ImagemResultante.setRGB(i, j, 255, 255, 255);
                    else
                        ImagemResultante.setRGB(i, j, 0, 0, 0);

                    PropagedError = TotalError - ImagemResultante.getR(i,j);
                }
            }

            CalcularFoto.setImagem(ImagemResultante.getImagem());
        }
        */

        }
    }


}
