package com.aplicacao.Interfaces;

/**
 * Created by Eron on 13/12/2015.
 *
 * Interface que herda as carateristicas da interface Operacoes
 * Possui métodos que necessitam de dois pixels para realização dos calculos
 */
public interface OperacoesBinarias extends  Operacoes {

    void CalcularPixel(int[] FotoA, int[] FotoB, int linha, int coluna, String Processo);
}
