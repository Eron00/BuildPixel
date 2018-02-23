package com.aplicacao.Modelo;


/**
 * Created by Eron on 29/01/2016.
 */
public class Processo {

    private String ProcessamentoSelecionado;
    private String CategoriaOperacao;

    public Processo(String NomeProcesso, String CategoriaOperacao) {
       this.ProcessamentoSelecionado = NomeProcesso;
       this.CategoriaOperacao = CategoriaOperacao;
    }

    public String getProcessamentoSelecionado() {
        return ProcessamentoSelecionado;
    }

    public String getCategoriaOperacao() {
        return CategoriaOperacao;
    }

    public void setProcessamentoSelecionado(String processamentoSelecionado) {
        ProcessamentoSelecionado = processamentoSelecionado;
    }

}
