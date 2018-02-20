package com.aplicacao.Modelo;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.media.Image;
import android.widget.ImageView;

import com.aplicacao.eron.Activities.ProcessamentoActivity;
import com.aplicacao.eron.build_pixel.R;

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


    public Imagem(){
    }

    public String getPath() {
        return Path;
    }

    public void setPath(String path) {
        Path = path;
    }

    private String getPathImagemOriginal() {
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

    public void VerificaOrientacaoTelaImagem() {
        try {
            ExifInterface ei = new ExifInterface(getPath());
            int orientation = ei.getAttributeInt(ExifInterface.TAG_ORIENTATION,
                    ExifInterface.ORIENTATION_UNDEFINED);

            Bitmap rotatedBitmap = null;
            switch (orientation) {

                case ExifInterface.ORIENTATION_ROTATE_90:
                    setImagem(RotacionarImagem(imagem, 90));
                    break;

                case ExifInterface.ORIENTATION_ROTATE_180:
                    setImagem(RotacionarImagem(imagem, 180));
                    break;

                case ExifInterface.ORIENTATION_ROTATE_270:
                    setImagem(RotacionarImagem(imagem, 270));
                    break;

                case ExifInterface.ORIENTATION_NORMAL:
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void Redimensionar() {
        BitmapFactory.Options bmpOptions = new BitmapFactory.Options();
        bmpOptions.inJustDecodeBounds = true;
        BitmapFactory.decodeFile(getPath(), bmpOptions);
        bmpOptions.inSampleSize = 7;
        bmpOptions.inJustDecodeBounds = false;
        imagem = BitmapFactory.decodeFile(getPath(), bmpOptions);

    }

    private Bitmap RotacionarImagem (Bitmap source, float angle) {
        Matrix matrix = new Matrix();
        matrix.postRotate(angle);
        return Bitmap.createBitmap(source, 0, 0, source.getWidth(), source.getHeight(),
                matrix, true);
    }

    public void CopiaPathOriginal(){
        setPath(getPathImagemOriginal());
    }

    public void AtualizaImagem(Activity activity) {
        ImageView imgView = activity.findViewById(R.id.imageView);
        File file = null;

        Bitmap FotoProcessada = getImagem();
        Matrix matrix = new Matrix();

        FotoProcessada = Bitmap.createBitmap(FotoProcessada, 0, 0,
               getLinha(),
               getColuna(), matrix, true);

        try {
            Ferramentas tool = new Ferramentas();
            file = tool.CriarArquivo();
            FileOutputStream fos = new FileOutputStream(file);
            FotoProcessada.compress(Bitmap.CompressFormat.JPEG, 100, fos);
            fos.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

        imgView.setImageBitmap(FotoProcessada);
        setPath(file.getAbsolutePath());
    }

}
