package com.aplicacao.Processamento.ProcessamentoArea;

import android.graphics.Bitmap;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesArea;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 25/09/2015.
 */
public class Halftone implements OperacoesArea {
    private OperacoesArea EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesArea) ProximaOperacao;
    }

    @Override
    public void CalcularFoto(Bitmap Foto, String NomeClasse) {

        if (NomeClasse != "Halftone") {
            EloCadeia.CalcularFoto(Foto, NomeClasse);
        } else {

            NDK ndk = new NDK();

            ndk.halftone(Foto);

            /*
            int linha = CalcularFoto.getLinha();
            int coluna = CalcularFoto.getColuna();
            int Valor;
            Imagem ImagemResultante = new Imagem(linha, coluna);
            Imagem PreImagem = new Imagem(linha, coluna);

            for (int i = 0; i < linha; i++) {
                for (int j = 0; j < coluna; j++) {

                    int Pixel = (int) ((CalcularFoto.getR(i, j) + CalcularFoto.getG(i, j) + CalcularFoto.getB(i, j)) / 3d);
                    PreImagem.setRGB(i, j, Pixel, Pixel, Pixel);
                }
            }
            for (int l = 0; l < linha - 1; l += 2) {
                for (int c = 0; c < coluna - 1; c += 2) {

                    Valor = PreImagem.getR(l, c);
                    Valor += PreImagem.getR(l, c + 1);
                    Valor += PreImagem.getR(l + 1, c);
                    Valor += PreImagem.getR(l + 1, c + 1);

                    if (Valor > (1 * 1024) / 8)
                        ImagemResultante.setRGB(l, c, 255, 255, 255);
                    else
                        ImagemResultante.setRGB(l, c, 0, 0, 0);

                    if (Valor > (3 * 1024) / 8)
                        ImagemResultante.setRGB(l + 1, c + 1, 255, 255, 255);
                    else
                        ImagemResultante.setRGB(l + 1, c + 1, 0, 0, 0);

                    if (Valor > (5 * 1024) / 8)
                        ImagemResultante.setRGB(l + 1, c, 255, 255, 255);
                    else
                        ImagemResultante.setRGB(l + 1, c, 0, 0, 0);

                    if (Valor > (7 * 1024) / 8)
                        ImagemResultante.setRGB(l, c + 1, 255, 255, 255);
                    else
                        ImagemResultante.setRGB(l, c + 1, 0, 0, 0);

                }
            }

           CalcularFoto.setImagem(ImagemResultante.getImagem());
           */
        }

    }


}
