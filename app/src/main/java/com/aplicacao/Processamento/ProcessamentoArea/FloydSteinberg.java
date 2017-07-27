package com.aplicacao.Processamento.ProcessamentoArea;


import android.graphics.Bitmap;

import com.aplicacao.Interfaces.Operacoes;
import com.aplicacao.Interfaces.OperacoesArea;
import com.aplicacao.Modelo.NDK;

/**
 * Created by Eron on 25/09/2015.
 */
public class FloydSteinberg implements OperacoesArea {
    private OperacoesArea EloCadeia;
    @Override
    public void setProximaOperacao(Operacoes ProximaOperacao) {
        this.EloCadeia = (OperacoesArea) ProximaOperacao;
    }

    @Override
    public void CalcularFoto(Bitmap Foto, String NomeClasse) {

        if (NomeClasse != "FloydSteinberg") {
            EloCadeia.CalcularFoto(Foto, NomeClasse);
        } else {

            NDK ndk = new NDK();

            ndk.floydSteinberg(Foto);

            /*
            int PropagedError,
                    OldPixel,
                    NewPixel;

            int linha  = CalcularFoto.getLinha();
            int coluna = CalcularFoto.getColuna();
            Imagem ImagemResultante = new Imagem(linha,coluna);
            Imagem PreImagem = new Imagem(linha,coluna);

            for (int i = 0; i < linha; i++) {
                for (int j = 0; j < coluna; j++) {

                    int Pixel = (int)(( CalcularFoto.getR(i, j) + CalcularFoto.getG(i, j) + CalcularFoto.getB(i, j))/3d);
                    PreImagem.setRGB(i, j, Pixel, Pixel, Pixel);
                }
            }
            for (int i = 1; i < linha - 1; i++) {
                for (int j = 1; j < coluna - 1; j++) {
                    OldPixel = PreImagem.getR(i,j);
                    if(OldPixel > 127)
                        NewPixel = 255;
                    else
                        NewPixel = 0;

                    ImagemResultante.setRGB(i, j, NewPixel,NewPixel,NewPixel);
                    PropagedError = OldPixel - NewPixel;

                    int PixelA = PreImagem.getR(i + 1, j)+ (PropagedError * 7)/16;
                    ImagemResultante.setRGB(i+1,j ,PixelA, PixelA, PixelA);

                    int PixelB = PreImagem.getR(i, j -1)+ (PropagedError * 3)/16;
                    ImagemResultante.setRGB(i,j-1 ,PixelB, PixelB, PixelB);

                    int PixelC = PreImagem.getR(i, j)+ (PropagedError * 5)/16;
                    ImagemResultante.setRGB(i,  j ,PixelC, PixelC, PixelC);

                    int PixelD = PreImagem.getR(i, j + 1)+ (PropagedError * 1)/16;
                    ImagemResultante.setRGB(i,j+1 ,PixelD, PixelD, PixelD);
                }
            }
            CalcularFoto.setImagem(ImagemResultante.getImagem());
        }
        */
        }
    }

}

//