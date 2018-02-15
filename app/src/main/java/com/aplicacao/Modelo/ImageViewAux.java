package com.aplicacao.Modelo;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;

import com.aplicacao.eron.Activities.ProcessamentoActivity;
import com.aplicacao.eron.build_pixel.R;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * Created by Eron on 14/02/2018.
 */

public class ImageViewAux{

    private ImageView imgView;

    public String AtualizaImageView(ProcessamentoActivity activity, Imagem imagem){
        imgView = (ImageView) activity.findViewById(R.id.imageView);

        File file = null;
        Bitmap FotoProcessada = imagem.getImagem();
        Matrix matrix = new Matrix();

        FotoProcessada = Bitmap.createBitmap(FotoProcessada, 0,0,
                imagem.getLinha(),
                imagem.getColuna(),matrix,true);

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

        imgView.setImageBitmap(FotoProcessada);
        return file.getAbsolutePath();
    }


    public void ImageViewRotate(){
        imgView.setRotation(90);
    }

    public void StartAnimationRightSide(Activity activity) {
        Animation animation = AnimationUtils.loadAnimation(activity, R.anim.rotate_right);
        animation.setFillAfter(true);
        imgView.startAnimation(animation);
    }

    public void StartAnimationLeftSide(Activity activity) {
        Animation animation = AnimationUtils.loadAnimation(activity, R.anim.rotate_left);
        animation.setFillAfter(true);
        imgView.startAnimation(animation);
    }
}
