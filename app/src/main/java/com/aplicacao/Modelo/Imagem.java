package com.aplicacao.Modelo;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.widget.ImageView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * Created by Eron on 29/08/2015.
 */
public class Imagem {

    private Bitmap imagem;
    private String Path;
    private String PathImagemOriginal;

    public Imagem(Bitmap foto){
        this.imagem = foto;
    }
    public Imagem(){
    }

    public String getPath() {
        return Path;
    }

    public void setPath(String path) {
        Path = path;
    }

    public String getPathImagemOriginal() {
        return PathImagemOriginal;
    }

    public void setPathImagemOriginal(String pathImagemOriginal) {
        PathImagemOriginal = pathImagemOriginal;
    }
    public Bitmap getImagem() {
        return imagem;
    }
    public void setImagem(Bitmap imagem) {
        this.imagem = imagem;
    }
    public int getLinha(){
        return(this.imagem.getWidth());
    }
    public int getColuna(){
        return(this.imagem.getHeight());
    }
}
