package com.aplicacao.eron.Activities;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Matrix;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageView;

import com.aplicacao.Modelo.Ferramentas;
import com.aplicacao.Modelo.Imagem;
import com.aplicacao.Modelo.NDK;
import com.aplicacao.Modelo.Processador;
import com.aplicacao.Modelo.Processo;
import com.aplicacao.eron.build_pixel.R;

import java.io.File;
import java.util.ArrayList;
import java.util.List;


public class ProcessamentoActivity extends AppCompatActivity {

    Bitmap      bit;
    String      CaminhoArq;
    ImageView   img;
    Imagem      foto;
    Processo    processo;
    Ferramentas tool;
    Boolean anima;
    //keep track of cropping intent
    final int PIC_CROP = 2;
    //keep track of camera capture intent
    List<Processo> processoList = new ArrayList<>();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Intent intent = getIntent();
        Bundle bundle = intent.getExtras();
        CaminhoArq    = (String) bundle.get("path");


    }

    public void onWindowFocusChanged(boolean onFocus) {
        img = (ImageView) findViewById(R.id.imageView);

        if(bit == null) {
            bit  = BitmapFactory.decodeFile(CaminhoArq);
            tool = new Ferramentas();
            foto = new Imagem(tool.Redimensionar(img.getWidth(), img.getHeight(), CaminhoArq));
            foto.AtualizarImagem(foto, img);
            anima = false;
            /*
            if(!isTablet(getContext())) {
               img.setRotation(90);
           }
           */
            super.onWindowFocusChanged(onFocus);
        }


    }

    public void Agucar(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Agucar", "Area");
        processoList.add(processo);
    }
    public void DestacarRelevo(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("DestacarRelevo", "Area");
        processoList.add(processo);
}
    public void FreiChenHorizontal(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("FreiChenHorizontal", "Area");
        processoList.add(processo);

    }
    public void FreiChenVertical(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("FreiChenVertical", "Area");
        processoList.add(processo);
    }
    public void Kirsch(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Kirsch", "Area");
        processoList.add(processo);

    }
    public void PrewittVertical(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("PrewittVertical", "Area");
        processoList.add(processo);
    }
    public void PrewittHorizontal(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("PrewittHorizontal", "Area");
        processoList.add(processo);
    }
    public void RobertsVertical(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("RobertsVertical", "Area");
        processoList.add(processo);

    }
    public void RobertsHorizontal(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("RobertsHorizontal", "Area");
        processoList.add(processo);
    }
    public void Sharpen(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Sharpen", "Area");
        processoList.add(processo);
    }
    public void SobelVertical(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("SobelVertical", "Area");
        processoList.add(processo);
    }
    public void SobelHorizontal(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("SobelHorizontal", "Area");
        processoList.add(processo);
    }
    public void Equalizar(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Equalizar", "Area");
        processoList.add(processo);
    }
    public void Media(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Media", "Area");
        processoList.add(processo);
    }
    public void ErrorDiffusion(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("ErrorDiffusion", "Area");
        processoList.add(processo);
    }
    public void FloydSteinberg(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("FloydSteinberg", "Area");
        processoList.add(processo);
    }
    public void Halftone(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Halftone", "Area");
        processoList.add(processo);
    }
    public void OilPaint(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("OilPaint", "Area");
        processoList.add(processo);

    }

    /**
     * Seção onde se encontra os botões dos processos de imagens unários(necessita de apenas um pixel para cálculo)
     *
     *
     */

    public void Blue(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Blue", "Unaria");
        processoList.add(processo);
    }
    public void Brilho(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Brilho", "Unaria");
        processoList.add(processo);
    }
    public void CinzaMedia(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("CinzaMedia", "Unaria");
        processoList.add(processo);
    }
    public void Luminosidade(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Luminosidade", "Unaria");
        processoList.add(processo);
    }
    public void Green(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Green", "Unaria");
        processoList.add(processo);
    }
    public void Red(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Red", "Unaria");
        processoList.add(processo);
    }
    public void Threshold(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Threshold", "Unaria");
        processoList.add(processo);
    }
    public void Azul(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Azul", "Unaria");
        processoList.add(processo);
    }
    public void Inverter(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Inverter", "Unaria");
        processoList.add(processo);
    }
    public void Sepia(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Sepia", "Unaria");
        processoList.add(processo);

    }
    public void Verde(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Verde", "Unaria");
        processoList.add(processo);
    }
    public void Vermelho(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Vermelho", "Unaria");
        processoList.add(processo);
    }
    public void Ciano(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Ciano", "Unaria");
        processoList.add(processo);
    }
    public void Magenta(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Magenta", "Unaria");
        processoList.add(processo);
    }
    public void Amarelo(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Amarelo", "Unaria");
        processoList.add(processo);
    }
    public void Teste(View view){

                NDK ndk = new NDK();
                Bitmap pic = Bitmap.createBitmap(foto.getLinha(), foto.getColuna(), Bitmap.Config.ARGB_8888);

                for(int i=0 ; i< foto.getLinha(); i++) {
                    for (int j = 0; j < foto.getColuna(); j++) {
                        pic.setPixel(i, j, Color.argb(255, foto.getR(i,j), foto.getG(i,j),foto.getB(i,j)));
                    }
                }
                ndk.teste(pic);
                foto.setImagem(pic);
                foto.AtualizarImagem(foto,img);
            }

    /*
    *
    * Região que corresponde aos botões que ativam processamentos binários
    * */
    public void Cartoon(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        processo = new Processo("Cartoon", "Binaria");
        processoList.add(processo);

    }
    public void Normalizar(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        AlertDialog.Builder builder = new AlertDialog.Builder(ProcessamentoActivity.this);

        builder.setTitle("Build Pixel").setItems(R.array.Operacoes, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                switch (which) {
                    case 0:
                        processo = new Processo("NormalizacaoSoma", "Binaria");
                        processoList.add(processo);
                        break;
                    case 1:
                        processo = new Processo("NormalizacaoSubtracao", "Binaria");
                        processoList.add(processo);
                        break;
                    case 2:
                        processo = new Processo("NormalizacaoMultiplicacao", "Binaria");
                        processoList.add(processo);
                        break;
                    case 3:
                        processo = new Processo("NormalizacaoDivisao", "Binaria");
                        processoList.add(processo);
                        break;
                    case 4:
                        processo = new Processo("NormalizacaoAnd", "Binaria");
                        processoList.add(processo);
                        break;
                    case 5:
                        processo = new Processo("NormalizacaoOr", "Binaria");
                        processoList.add(processo);
                        break;
                    case 6:
                        processo = new Processo("NormalizacaoXor", "Binaria");
                        processoList.add(processo);
                        break;

                }
            }
        });
        builder.show();
    }

    public void Truncar(View view){
        Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
        Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_in);
        btnEnviarProcesso.setVisibility(View.VISIBLE);
        if(!anima){btnEnviarProcesso.setAnimation(animacao);anima = true;}
        AlertDialog.Builder builder = new AlertDialog.Builder(ProcessamentoActivity.this);
        builder.setTitle("Build Pixel").setItems(R.array.Operacoes, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                switch (which) {
                    case 0:
                        processo = new Processo("TruncamentoSoma", "Binaria");
                        processoList.add(processo);
                        break;
                    case 1:
                        processo = new Processo("TruncamentoSubtracao", "Binaria");
                        processoList.add(processo);
                        break;
                    case 2:
                        processo = new Processo("TruncamentoMultiplicacao", "Binaria");
                        processoList.add(processo);
                        break;
                    case 3:
                        processo = new Processo("TruncamentoDivisao", "Binaria");
                        processoList.add(processo);
                        break;
                    case 4:
                        processo = new Processo("TruncamentoAnd", "Binaria");
                        processoList.add(processo);
                        break;
                    case 5:
                        processo = new Processo("TruncamentoOr", "Binaria");
                        processoList.add(processo);
                        break;
                    case 6:
                        processo = new Processo("TruncamentoXor", "Binaria");
                        processoList.add(processo);
                        break;
                }
            }
        });
        builder.show();
    }

    public void EnviarProcessos(View view){

        AsyncTask Tarefa = new AsyncTask() {
            ProgressDialog progressDialog = new ProgressDialog(ProcessamentoActivity.this);
            Processador proc = new Processador();

            @Override
            protected void onPreExecute() {
                super.onPreExecute();
                progressDialog.setTitle("Build Pixel");
                progressDialog.setMessage("Em processamento...");
                progressDialog.setCancelable(false);
                progressDialog.show();
            }

            @Override
            protected Void doInBackground(Object... params) {
                foto = proc.ExecutarProcessamento(foto, processoList);
               processoList.clear();
                return null;
            }

            @Override
            protected void onPostExecute(Object o) {
                super.onPostExecute(o);
                progressDialog.dismiss();
                CaminhoArq = foto.AtualizarImagem(foto, img);
                Button btnEnviarProcesso = (Button) findViewById(R.id.btnEnviarProcesso);
                Animation animacao = AnimationUtils.loadAnimation(getContext(), R.anim.fade_out);
                btnEnviarProcesso.setAnimation(animacao);
                btnEnviarProcesso.setVisibility(View.INVISIBLE);
                anima = false;
            }
        };

        Tarefa.execute(foto);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);

     return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        //noinspection SimplifiableIfStatement
        Ferramentas tool = new Ferramentas();

        switch (item.getItemId()) {

            case R.id.action_share:
                tool.IntentCompartilhar(CaminhoArq, getContext());

                break;
            case R.id.action_rotate:
                Matrix matrix = new Matrix();
                matrix.postRotate(90);
                Bitmap rotate = Bitmap.createBitmap(foto.getImagem(), 0, 0,
                        foto.getLinha(),
                        foto.getColuna(),
                        matrix, true);
                Animation animation = AnimationUtils.loadAnimation(getContext(), R.anim.rotate_right);
                animation.setFillAfter(true);
                foto.setImagem(rotate);
                CaminhoArq = foto.AtualizarImagem(foto, img);
                img.startAnimation(animation);

                break;

            case R.id.action_settings:
                break;
            case android.R.id.home:
                bit.recycle();
                break;
            case R.id.action_return_image:
                Imagem foto2 = new Imagem(foto.getImagemOriginal());
                CaminhoArq = foto.AtualizarImagem(foto2, img);
                break;
            case  R.id.action_crop:
                      IntentCortarImagem();
                break;
            case  R.id.action_edit:
                tool.AlertaLista(getContext(),processoList);
                break;

           // case  R.id.action_photo_size:
             //   foto.setImagem(tool.TamanhoImagemAlertaLista(getContext(), CaminhoArq));
               // foto.AtualizarImagem(foto,img);
           // case  R.id.action_details:
        }

        return super.onOptionsItemSelected(item);
    }


    @Override
    public void onBackPressed(){
        if(bit != null)
        bit.recycle();
      ProcessamentoActivity.this.finish();
    }

    private boolean isTablet(Context context) {
        boolean xlarge =((context.getResources().getConfiguration().screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) == 4);
        boolean large = ((context.getResources().getConfiguration().screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) == Configuration.SCREENLAYOUT_SIZE_LARGE);
        return (xlarge || large);
    }
    private Context getContext() {
        return this;
    }

    private void IntentCortarImagem(){
        ContentValues valores = new ContentValues(2);
        valores.put(MediaStore.Images.Media.MIME_TYPE, "image/jpg");
        valores.put(MediaStore.Images.Media.DATA, CaminhoArq);
        ContentResolver contentResolver = getContext().getContentResolver();
        Uri picUri = contentResolver.insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, valores);
        Intent cropIntent = new Intent("com.android.camera.action.CROP");
        //indicate image type and Uri
        cropIntent.setDataAndType(picUri, "image/*");
        //set crop properties
        cropIntent.putExtra("crop", "true");
        //indicate aspect of desired crop
        cropIntent.putExtra("aspectX", 1);
        cropIntent.putExtra("aspectY", 1);
        //indicate output X and Y
        cropIntent.putExtra("outputX", 256);
        cropIntent.putExtra("outputY", 256);
        //retrieve data on return
        cropIntent.putExtra("return-data", true);
        //start the activity - we handle returning in onActivityResult
        startActivityForResult(cropIntent, PIC_CROP);
    }
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == RESULT_OK) {
            //user is returning from cropping the image
            if(requestCode == PIC_CROP){
                //get the returned data
                Bundle extras = data.getExtras();
                //get the cropped bitmap
                Bitmap thePic = extras.getParcelable("data");
                //display the returned cropped image
                Matrix matrix = new Matrix();
                matrix.setRotate(270);
                thePic = Bitmap.createBitmap(thePic, 0,0,
                        thePic.getWidth(),
                        thePic.getHeight(),
                        matrix, true);
                foto.setImagem(thePic);
                foto.AtualizarImagem(foto,img);
            }
        }
    }

}
