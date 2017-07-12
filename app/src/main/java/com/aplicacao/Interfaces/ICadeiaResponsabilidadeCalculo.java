package com.aplicacao.Interfaces;

/**
 * Created by Eron on 30/08/2015.
 *
 * Modificado em 02/09/2015 inclusão método calcular.
 *
 * Interface experimental para estudo sobre o pattern "Chain of responsability"
 *
 * setProximaOperacao(ICadeiaResponsabilidadeCalculo ProximaOperacao) - > Assinatura do metodo onde a classe que
 * irá implementar a interface irá verificar se o objeto enviado da classe cliente poderá ser executado por ele
 * ou terá que ser enviado para outra classe da cadeia onde poderá atender a solicitação.
 *
 *
 * public int Calcular(Pixel calculo) - > Assinatura do método para cálculo do pixel entre duas imagens.
 *
 *
 * 26/09 - alterado o metodo Calcular para void, o retorno no tipo int estava ocasionando um bug para os outros elos,
 * fazendo com que o calculo retornasse zerado.
 *
 */
public interface ICadeiaResponsabilidadeCalculo {

    void setProximaOperacao(ICadeiaResponsabilidadeCalculo ProximaOperacao);




}
