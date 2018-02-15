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
import android.graphics.Matrix;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import com.aplicacao.Modelo.Ferramentas;
import com.aplicacao.Modelo.ImageViewAux;
import com.aplicacao.Modelo.Imagem;
import com.aplicacao.Modelo.Processador;
import com.aplicacao.Modelo.Processo;
import com.aplicacao.eron.build_pixel.R;
import com.theartofdev.edmodo.cropper.CropImage;

import java.util.ArrayList;
import java.util.List;


public class ProcessamentoActivity extends AppCompatActivity {
    private ImageViewAux atualiza;
    private Imagem  foto;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Intent intent = getIntent();
        Bundle bundle = intent.getExtras();
        foto = new Imagem();
        foto.setPathImagemOriginal((String) bundle.get("path"));
        foto.setPath((String) bundle.get("path"));
        atualiza = new ImageViewAux();
        Ferramentas tool = new Ferramentas();
        foto.setImagem(tool.Redimensionar(foto.getPath()));
        atualiza.AtualizaImageView(ProcessamentoActivity.this, foto);
    }

    public void onWindowFocusChanged(boolean onFocus) {
        if(!isTablet(getContext())){atualiza.ImageViewRotate();}
        super.onWindowFocusChanged(onFocus);
}

    public void Agucar(View view){
        EnviarProcessos("Agucar", "Area");
    }
    public void DestacarRelevo(View view){
        EnviarProcessos("DestacarRelevo", "Area");
}
    public void FreiChenHorizontal(View view){
        EnviarProcessos("FreiChenHorizontal", "Area");
    }
    public void FreiChenVertical(View view){
        EnviarProcessos("FreiChenVertical", "Area");
    }
    public void Kirsch(View view){
        EnviarProcessos("Kirsch", "Area");
    }
    public void PrewittVertical(View view){
        EnviarProcessos("PrewittVertical", "Area");
    }
    public void PrewittHorizontal(View view){
        EnviarProcessos("PrewittHorizontal", "Area");
    }
    public void RobertsVertical(View view){
        EnviarProcessos("RobertsVertical", "Area");
    }
    public void RobertsHorizontal(View view){
        EnviarProcessos("RobertsHorizontal", "Area");
    }
    public void Sharpen(View view){
        EnviarProcessos("Sharpen", "Area");
    }
    public void SobelVertical(View view){
        EnviarProcessos("SobelVertical", "Area");
    }
    public void SobelHorizontal(View view){
        EnviarProcessos("SobelHorizontal", "Area");
    }
    public void Equalizar(View view){
        EnviarProcessos("Equalizar", "Area");
    }
    public void Media(View view){
        EnviarProcessos("Media", "Area");
    }
    public void ErrorDiffusion(View view){
        EnviarProcessos("ErrorDiffusion", "Area");
    }
    public void FloydSteinberg(View view){
        EnviarProcessos("FloydSteinberg", "Area");
    }
    public void Halftone(View view){
        EnviarProcessos("CelulaThreshold", "Area");
    }
    public void OilPaint(View view){
        EnviarProcessos("OilPaint", "Area");
    }

    /**
     * Seção onde se encontra os botões dos processos de imagens unários(necessita de apenas um pixel para cálculo)
     *
     *
     */

    public void Blue(View view){
        EnviarProcessos("Blue", "Unaria");
    }
    public void Brilho(View view){
        EnviarProcessos("Brilho", "Unaria");
    }
    public void CinzaMedia(View view){
        EnviarProcessos("CinzaMedia", "Unaria");
    }
    public void Luminosidade(View view){
        EnviarProcessos("Luminosidade", "Unaria");
    }
    public void Green(View view){
        EnviarProcessos("Green", "Unaria");
    }
    public void Red(View view){
        EnviarProcessos("Red", "Unaria");
    }
    public void Threshold(View view){
        EnviarProcessos("Threshold", "Unaria");
    }
    public void Azul(View view){
        EnviarProcessos("Azul", "Unaria");
    }
    public void Inverter(View view){
        EnviarProcessos("Inverter", "Unaria");
    }
    public void Sepia(View view){
        EnviarProcessos("Sepia", "Unaria");
    }
    public void Verde(View view){
        EnviarProcessos("Verde", "Unaria");
    }
    public void Vermelho(View view){
        EnviarProcessos("Vermelho", "Unaria");
    }
    public void Ciano(View view){
        EnviarProcessos("Ciano", "Unaria");
    }
    public void Magenta(View view){
        EnviarProcessos("Magenta", "Unaria");
    }
    public void Amarelo(View view){
        EnviarProcessos("Amarelo", "Unaria");
    }
    /*
    *
    * Região que corresponde aos botões que ativam processamentos binários
    * */
    public void Cartoon(View view){
        EnviarProcessos("Cartoon", "Binaria");
    }
    public void Normalizar(View view){
        AlertDialog.Builder builder = new AlertDialog.Builder(ProcessamentoActivity.this);
        builder.setTitle("Build Pixel").setItems(R.array.Operacoes, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                switch (which) {
                    case 0:
                        EnviarProcessos("NormalizacaoSoma", "Binaria");
                        break;
                    case 1:
                        EnviarProcessos("NormalizacaoSubtracao", "Binaria");
                        break;
                    case 2:
                        EnviarProcessos("NormalizacaoMultiplicacao", "Binaria");
                        break;
                    case 3:
                        EnviarProcessos("NormalizacaoDivisao", "Binaria");
                        break;
                    case 4:
                        EnviarProcessos("NormalizacaoAnd", "Binaria");
                        break;
                    case 5:
                        EnviarProcessos("NormalizacaoOr", "Binaria");
                        break;
                    case 6:
                        EnviarProcessos("NormalizacaoXor", "Binaria");
                        break;

                }
            }
        });
        builder.show();
    }

    public void Truncar(View view){
        AlertDialog.Builder builder = new AlertDialog.Builder(ProcessamentoActivity.this);
        builder.setTitle("Build Pixel").setItems(R.array.Operacoes, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                switch (which) {
                    case 0:
                        EnviarProcessos("TruncamentoSoma", "Binaria");
                        break;
                    case 1:
                        EnviarProcessos("TruncamentoSubtracao", "Binaria");
                        break;
                    case 2:
                        EnviarProcessos("TruncamentoMultiplicacao", "Binaria");
                        break;
                    case 3:
                        EnviarProcessos("TruncamentoDivisao", "Binaria");
                        break;
                    case 4:
                        EnviarProcessos("TruncamentoAnd", "Binaria");
                        break;
                    case 5:
                        EnviarProcessos("TruncamentoOr", "Binaria");
                        break;
                    case 6:
                        EnviarProcessos("TruncamentoXor", "Binaria");
                        break;
                }
            }
        });
        builder.show();
    }

    public void EnviarProcessos(String NomeExecucao, String Categoria){
        Processo processo = new Processo(NomeExecucao, Categoria);
        final List<Processo> processoList = new ArrayList<>();
        processoList.add(processo);

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
                foto.setPath(atualiza.AtualizaImageView(ProcessamentoActivity.this, foto));
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
        // no inspection SimplifiableIfStatement
        //

        switch (item.getItemId()) {
            case R.id.action_share:
                Ferramentas tool = new Ferramentas();
                tool.IntentCompartilhar(foto.getPath(), getContext());

                break;
            case R.id.action_rotate:
                Matrix matrix = new Matrix();
                matrix.postRotate(90);
                Bitmap rotate = Bitmap.createBitmap(foto.getImagem(), 0, 0,
                        foto.getLinha(),
                        foto.getColuna(),
                        matrix, true);

                foto.setImagem(rotate);
                foto.setPath(atualiza.AtualizaImageView(ProcessamentoActivity.this, foto));
                atualiza.StartAnimationRightSide(ProcessamentoActivity.this);
                break;

            case R.id.action_settings:
                break;
            case android.R.id.home:
                break;
            case R.id.action_return_image:
                Bitmap bitmap = BitmapFactory.decodeFile(foto.getPathImagemOriginal());
                foto.setImagem(bitmap);
                foto.setPath(atualiza.AtualizaImageView(ProcessamentoActivity.this, foto));
                break;
            case  R.id.action_crop:
             IntentCortarImagem();
                break;
            case  R.id.action_edit:
                break;

           // case  R.id.action_photo_size:
             //   foto.setImagem(tool.TamanhoImagemAlertaLista(getContext(), CaminhoArq));
               // foto.AtualizarImagem(foto,img);
           // case  R.id.action_details:
        }

        return super.onOptionsItemSelected(item);
    }



    private void IntentCortarImagem(){

        ContentValues valores = new ContentValues(2);
        valores.put(MediaStore.Images.Media.MIME_TYPE, "image/jpg");
        valores.put(MediaStore.Images.Media.DATA, foto.getPath());
        ContentResolver contentResolver = getContext().getContentResolver();
        Uri uri = contentResolver.insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, valores);
        CropImage.activity(uri).setAllowFlipping(false).setAllowRotation(false).start(this);

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == CropImage.CROP_IMAGE_ACTIVITY_REQUEST_CODE) {
            CropImage.ActivityResult result = CropImage.getActivityResult(data);

            if (resultCode == RESULT_OK) {
                Uri resultUri = result.getUri();
                Bitmap cropped = BitmapFactory.decodeFile(resultUri.getPath());
                foto.setImagem(cropped);
                atualiza.AtualizaImageView(ProcessamentoActivity.this, foto);
                Toast.makeText(getContext(), "Corte realizado!!" , Toast.LENGTH_SHORT).show();

            } else if (resultCode == CropImage.CROP_IMAGE_ACTIVITY_RESULT_ERROR_CODE) {
                Exception error = result.getError();
                Toast.makeText(getContext(), "Erro ao executar!!: "+ error.getMessage(), Toast.LENGTH_LONG).show();
            }
            else if (resultCode == RESULT_CANCELED)
            {
                if (result == null)
                {
                    Toast.makeText(getContext(), "Corte da imagem cancelado!!" , Toast.LENGTH_SHORT).show();
                    foto.setPath(atualiza.AtualizaImageView(ProcessamentoActivity.this, foto));

                }
            }
        }

    }


    @Override
    public void onBackPressed(){
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

}
