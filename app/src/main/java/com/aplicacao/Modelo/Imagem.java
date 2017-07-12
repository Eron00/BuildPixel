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
    private Bitmap ImagemOriginal;

    public Imagem(Bitmap foto){
        this.imagem = foto;
        this.ImagemOriginal = foto;
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
    public int getA(int x, int y) {
        return(Color.alpha((this.imagem.getPixel(x, y))));
    }
    public int getR(int x, int y) {
        return(Color.red((this.imagem.getPixel(x, y))));
    }
    public int getG(int x, int y) {
        return(Color.green((this.imagem.getPixel(x, y))));
    }
    public int getB(int x, int y) {
        return(Color.blue((this.imagem.getPixel(x, y))));
    }
    public void setRGB(int x, int y, int R, int G, int B) {
        this.imagem.setPixel(x, y, Color.rgb(R, G, B));
    }
    public void setARGB(int x, int y,int A, int R, int G, int B) {
        this.imagem.setPixel(x, y, Color.argb(A, R, G, B));
    }

    public Bitmap getImagemOriginal() {
        return ImagemOriginal;
    }


    public String AtualizarImagem(Imagem imagem, ImageView img) {


        File file = null;

        Bitmap FotoProcessada = imagem.getImagem();


        Matrix matrix = new Matrix();
        //matrix.setRotate(90);

        FotoProcessada = Bitmap.createBitmap(FotoProcessada, 0,0,
                imagem.getLinha(),
                imagem.getColuna(),
                matrix, true);

        try {
            Ferramentas tool = new Ferramentas();
            file = tool.CriarArquivo();
            FileOutputStream fos  = new FileOutputStream(file);
           FotoProcessada.compress(Bitmap.CompressFormat.JPEG, 100, fos);
            fos.close();
            ExifInterface exif = new ExifInterface(file.getAbsolutePath());
            exif.getAttributeInt(ExifInterface.TAG_ORIENTATION, ExifInterface.ORIENTATION_NORMAL);

        } catch (IOException e) {
            e.printStackTrace();
        }

        img.setImageBitmap(FotoProcessada);
        return file.getAbsolutePath();
    }
}
