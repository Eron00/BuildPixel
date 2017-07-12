package com.aplicacao.Modelo;


import android.graphics.Bitmap;
import android.graphics.Color;

import com.aplicacao.Interfaces.OperacoesArea;
import com.aplicacao.Interfaces.OperacoesBinarias;
import com.aplicacao.Interfaces.OperacoesUnarias;
import com.aplicacao.Processamento.ProcessamentoArea.Agucar;
import com.aplicacao.Processamento.ProcessamentoBinario.Cartoon;
import com.aplicacao.Processamento.ProcessamentoArea.DestacarRelevo;
import com.aplicacao.Processamento.ProcessamentoArea.Equalizar;
import com.aplicacao.Processamento.ProcessamentoArea.ErrorDiffusion;
import com.aplicacao.Processamento.ProcessamentoArea.FloydSteinberg;
import com.aplicacao.Processamento.ProcessamentoArea.FreiChen;
import com.aplicacao.Processamento.ProcessamentoArea.Halftone;
import com.aplicacao.Processamento.ProcessamentoArea.Kirsch;
import com.aplicacao.Processamento.ProcessamentoArea.Laplace;
import com.aplicacao.Processamento.ProcessamentoArea.Media;
import com.aplicacao.Processamento.ProcessamentoArea.OilPaint;
import com.aplicacao.Processamento.ProcessamentoArea.Prewitt;
import com.aplicacao.Processamento.ProcessamentoArea.Roberts;
import com.aplicacao.Processamento.ProcessamentoArea.Sharpen;
import com.aplicacao.Processamento.ProcessamentoArea.Sobel;
import com.aplicacao.Processamento.ProcessamentoBinario.Normalizacao;
import com.aplicacao.Processamento.ProcessamentoBinario.Truncamento;
import com.aplicacao.Processamento.ProcessamentoUnario.Amarelo;
import com.aplicacao.Processamento.ProcessamentoUnario.Azul;
import com.aplicacao.Processamento.ProcessamentoUnario.Blue;
import com.aplicacao.Processamento.ProcessamentoUnario.Brilho;
import com.aplicacao.Processamento.ProcessamentoUnario.Ciano;
import com.aplicacao.Processamento.ProcessamentoUnario.CinzaMedia;
import com.aplicacao.Processamento.ProcessamentoUnario.Green;
import com.aplicacao.Processamento.ProcessamentoUnario.Inverter;
import com.aplicacao.Processamento.ProcessamentoUnario.Luminosidade;
import com.aplicacao.Processamento.ProcessamentoUnario.Magenta;
import com.aplicacao.Processamento.ProcessamentoUnario.Red;
import com.aplicacao.Processamento.ProcessamentoUnario.Sepia;
import com.aplicacao.Processamento.ProcessamentoUnario.Threshold;
import com.aplicacao.Processamento.ProcessamentoUnario.Verde;
import com.aplicacao.Processamento.ProcessamentoUnario.Vermelho;

import java.util.List;

/**
 *
 * Created by Eron on 27/09/2015.
 */
public class Processador {


    public Imagem ExecutarProcessamento(Imagem foto, List<Processo> ListaProcessos){

        OperacoesUnarias EloAzul          = new Azul();
        OperacoesUnarias EloVerde         = new Verde();
        OperacoesUnarias EloVermelho      = new Vermelho();
        OperacoesUnarias EloSepia         = new Sepia();
        OperacoesUnarias EloBrilho        = new Brilho();
        OperacoesUnarias EloBlue          = new Blue();
        OperacoesUnarias EloCinzaMedia    = new CinzaMedia();
        OperacoesUnarias EloGreen         = new Green();
        OperacoesUnarias EloLuminosidade  = new Luminosidade();
        OperacoesUnarias EloRed           = new Red();
        OperacoesUnarias EloThreshold     = new Threshold();
        OperacoesUnarias EloInverter      = new Inverter();
        OperacoesUnarias EloCiano         = new Ciano();
        OperacoesUnarias EloMagenta       = new Magenta();
        OperacoesUnarias EloAmarelo       = new Amarelo();

        OperacoesArea EloAgucar           = new Agucar();
        OperacoesArea EloDestacarRelevo   = new DestacarRelevo();
        OperacoesArea EloEqualizar        = new Equalizar();
        OperacoesArea EloErrorDiffusion   = new ErrorDiffusion();
        OperacoesArea EloFloydSteinberg   = new FloydSteinberg();
        OperacoesArea EloFreiChen         = new FreiChen();
        OperacoesArea EloHalftone         = new Halftone();
        OperacoesArea EloKirsch           = new Kirsch();
        OperacoesArea EloLaplace          = new Laplace();
        OperacoesArea EloMedia            = new Media();
        OperacoesArea EloPrewitt          = new Prewitt();
        OperacoesArea EloRoberts          = new Roberts();
        OperacoesArea EloSharpen          = new Sharpen();
        OperacoesArea EloSobel            = new Sobel();
        OperacoesArea EloOilPaint         = new OilPaint();

        OperacoesBinarias EloTruncamento  = new Truncamento();
        OperacoesBinarias EloNormalizacao = new Normalizacao();
        OperacoesBinarias EloCartoon      = new Cartoon();



        EloAzul.setProximaOperacao(EloVerde);
        EloVerde.setProximaOperacao(EloVermelho);
        EloVermelho.setProximaOperacao(EloSepia);
        EloSepia.setProximaOperacao(EloBrilho);
        EloBrilho.setProximaOperacao(EloBlue);
        EloBlue.setProximaOperacao(EloCinzaMedia);
        EloCinzaMedia.setProximaOperacao(EloGreen);
        EloGreen.setProximaOperacao(EloLuminosidade);
        EloLuminosidade.setProximaOperacao(EloRed);
        EloRed.setProximaOperacao(EloThreshold);
        EloThreshold.setProximaOperacao(EloInverter);
        EloInverter.setProximaOperacao(EloCiano);
        EloCiano.setProximaOperacao(EloMagenta);
        EloMagenta.setProximaOperacao(EloAmarelo);


        EloEqualizar.setProximaOperacao(EloErrorDiffusion);
        EloErrorDiffusion.setProximaOperacao(EloFloydSteinberg);
        EloFloydSteinberg.setProximaOperacao(EloHalftone);
        EloHalftone.setProximaOperacao(EloMedia);
        EloMedia.setProximaOperacao(EloSobel);
        EloSobel.setProximaOperacao(EloRoberts);
        EloRoberts.setProximaOperacao(EloPrewitt);
        EloPrewitt.setProximaOperacao(EloLaplace);
        EloLaplace.setProximaOperacao(EloKirsch);
        EloKirsch.setProximaOperacao(EloFreiChen);
        EloFreiChen.setProximaOperacao(EloSharpen);
        EloSharpen.setProximaOperacao(EloDestacarRelevo);
        EloDestacarRelevo.setProximaOperacao(EloAgucar);
        EloAgucar.setProximaOperacao(EloOilPaint);

        EloTruncamento.setProximaOperacao(EloNormalizacao);
        EloNormalizacao.setProximaOperacao(EloCartoon);


        int[]Imagem = new int[foto.getLinha() * foto.getColuna() *3];
        int[]ImagemB = new int[foto.getLinha() * foto.getColuna() *3];
        int[]Red    = new int[foto.getLinha() * foto.getColuna()];
        int[]Blue   = new int[foto.getLinha() * foto.getColuna()];
        int[]Green  = new int[foto.getLinha() * foto.getColuna()];
        int[]Alpha  = new int[foto.getLinha() * foto.getColuna()];

        int indice =0;
        for(int i=0 ; i< foto.getLinha(); i++) {
            for (int j = 0; j < foto.getColuna(); j++ ,indice+=3) {
                Imagem[indice    ] = foto.getR(i, j);
                Imagem[indice + 1] = foto.getG(i, j);
                Imagem[indice + 2] = foto.getB(i ,j);

                ImagemB[indice    ] = foto.getR(i, j);
                ImagemB[indice + 1] = foto.getG(i, j);
                ImagemB[indice + 2] = foto.getB(i ,j);
            }
        }

        for(int k = 0; k < ListaProcessos.size() ; k++)
        {
            Processo list = ListaProcessos.get(k);
            switch (list.getCategoriaOperacao()){
                case ("Unaria"):
                    EloAzul.CalcularPixel(Imagem, foto.getLinha(), foto.getColuna(), list.getProcessamentoSelecionado());
                    break;
                case ("Binaria"):
                   // Problemas para executar cartoon
                   // EloTruncamento.CalcularPixel(Imagem, Imagem, foto.getLinha(), foto.getColuna(), list.getProcessamentoSelecionado());
                    EloTruncamento.CalcularPixel(Imagem, ImagemB, foto.getLinha(), foto.getColuna(), list.getProcessamentoSelecionado());
                    break;
                case ("Area"):
                    EloEqualizar.CalcularFoto(Imagem, foto.getLinha(), foto.getColuna(),list.getProcessamentoSelecionado());
                    break;
            }
        }

        ImagemB = null;
        Bitmap ImagemResultante = Bitmap.createBitmap(foto.getLinha(), foto.getColuna(), Bitmap.Config.ARGB_8888);
        indice =0;
        for(int i=0 ; i< foto.getLinha(); i++) {
            for (int j = 0; j < foto.getColuna(); j++ ,indice+=3) {
                ImagemResultante.setPixel(i, j, Color.argb(255, Imagem[indice], Imagem[indice + 1], Imagem[indice + 2]));
            }
        }

        foto.setImagem(ImagemResultante);
        return foto;
    }
}
