package com.aplicacao.eron.Activities;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

import com.aplicacao.Modelo.Ferramentas;
import com.aplicacao.eron.build_pixel.R;

import java.io.File;
import java.io.IOException;


public class CapturaActivity extends Activity {

    private static final int APP_CAMERA = 0;
    private static final int SELECT_PICTURE = 1;

    private String ImagemlocalArq;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_captura);

    }

    public void TirarFoto(View view) {
        Intent camera = new Intent();
        camera.setAction(MediaStore.ACTION_IMAGE_CAPTURE);

        Ferramentas tool = new Ferramentas();
        File arqFoto = null;
        try {
            arqFoto = tool.CriarArquivo();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        ImagemlocalArq = arqFoto.getAbsolutePath();
        camera.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(arqFoto));

        startActivityForResult(camera, APP_CAMERA);

    }

    public void AnexarFoto(View view){
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("image/*");
        startActivityForResult(Intent.createChooser(intent,"Selecionar Imagem"), SELECT_PICTURE);
    }

private Context getContext() {
    return this;
}

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode== APP_CAMERA && resultCode == RESULT_OK) {
            Intent it = new Intent(getContext(), ProcessamentoActivity.class);
            Bundle extras = new Bundle();
            extras.putString("path", ImagemlocalArq);
            it.putExtras(extras);
            startActivity(it);
        }
        if (requestCode== SELECT_PICTURE && resultCode == RESULT_OK) {
            Uri selectedImageUri = data.getData();
            ImagemlocalArq = getPath(selectedImageUri);
            Intent it = new Intent(getContext(), ProcessamentoActivity.class);
            Bundle extras = new Bundle();
            extras.putString("path", ImagemlocalArq);
            it.putExtras(extras);
            startActivity(it);
        }
    }

    private String getPath(Uri uri) {
        // just some safety built in
        if( uri == null ) {
            return null;
        }
        // try to retrieve the image from the media store first
        // this will only work for images selected from gallery
        String[] projection = { MediaStore.Images.Media.DATA };
        @SuppressWarnings("deprecation")
        Cursor cursor = managedQuery(uri, projection, null, null, null);
        if( cursor != null ){
            int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
            cursor.moveToFirst();
            return cursor.getString(column_index);
        }
        // this is our fallback here
        return uri.getPath();
    }

}
