package com.aplicacao.Modelo;


import com.aplicacao.Interfaces.OperacoesArea;
import com.aplicacao.Interfaces.OperacoesBinarias;
import com.aplicacao.Interfaces.OperacoesUnarias;
import com.aplicacao.Processamento.ProcessamentoArea.Agucar;
import com.aplicacao.Processamento.ProcessamentoArea.CelulaThreshold;
import com.aplicacao.Processamento.ProcessamentoArea.DestacarRelevo;
import com.aplicacao.Processamento.ProcessamentoArea.Equalizar;
import com.aplicacao.Processamento.ProcessamentoArea.ErrorDiffusion;
import com.aplicacao.Processamento.ProcessamentoArea.FloydSteinberg;
import com.aplicacao.Processamento.ProcessamentoArea.FreiChen;
import com.aplicacao.Processamento.ProcessamentoArea.Kirsch;
import com.aplicacao.Processamento.ProcessamentoArea.Laplace;
import com.aplicacao.Processamento.ProcessamentoArea.Media;
import com.aplicacao.Processamento.ProcessamentoArea.OilPaint;
import com.aplicacao.Processamento.ProcessamentoArea.Prewitt;
import com.aplicacao.Processamento.ProcessamentoArea.Roberts;
import com.aplicacao.Processamento.ProcessamentoArea.Sharpen;
import com.aplicacao.Processamento.ProcessamentoArea.Sobel;
import com.aplicacao.Processamento.ProcessamentoBinario.Cartoon;
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

/**
 *
 * Created by Eron on 27/09/2015.
 */
public class Processador {


    public Imagem AtivarCPU(Imagem foto, Processo processo){

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
        OperacoesArea EloHalftone         = new CelulaThreshold();
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

            switch (processo.getCategoriaOperacao()){
                case ("Unaria"):
                    EloAzul.CalcularPixel(foto.getImagem(), processo.getProcessamentoSelecionado());
                    break;
                case ("Area"):
                      EloEqualizar.CalcularArea(foto.getImagem(),processo.getProcessamentoSelecionado());
                    break;
                case ("Binaria"):
                    EloTruncamento.CalcularPixel(foto.getImagem(), foto.getImagem(), processo.getProcessamentoSelecionado());
                    break;
            }

        return foto;
    }
}
