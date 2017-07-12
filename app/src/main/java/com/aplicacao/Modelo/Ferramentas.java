package com.aplicacao.Modelo;

import android.app.AlertDialog;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import android.widget.ListView;
import android.widget.Toast;

import com.aplicacao.eron.build_pixel.R;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import static java.lang.Math.max;
import static java.lang.Math.min;

/**
 *
 * Created by Eron on 22/03/2016.
 */


public class Ferramentas{

    public Bitmap Redimensionar(int targetW, int targetH, String path) {
        BitmapFactory.Options bmpOptions = new BitmapFactory.Options();
        bmpOptions.inJustDecodeBounds = true;
        BitmapFactory.decodeFile(path, bmpOptions);
        int photoW = bmpOptions.outWidth;
        int photoH = bmpOptions.outHeight;
        bmpOptions.inSampleSize = min(photoW / targetW, photoH / targetH);
        bmpOptions.inJustDecodeBounds = false;
        return BitmapFactory.decodeFile(path, bmpOptions);

    }

    public File CriarArquivo() throws IOException {
        String infTempo = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        String nomeImagemArq = "IMAGEM_" + infTempo + " ";
        File Diretorio = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
        return File.createTempFile(nomeImagemArq, ".jpg", Diretorio);
    }

    public void IntentCompartilhar(String LocalArquivo, Context Contexto){
        ContentValues valores = new ContentValues(2);
        valores.put(MediaStore.Images.Media.MIME_TYPE, "image/jpg");
        valores.put(MediaStore.Images.Media.DATA, LocalArquivo);
        ContentResolver contentResolver = Contexto.getContentResolver();
        Uri uri = contentResolver.insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, valores);
        Intent intent = new Intent(Intent.ACTION_SEND);
        intent.setType("image/jpg");
        intent.putExtra(Intent.EXTRA_STREAM, uri);
        Contexto.startActivity(Intent.createChooser(intent, "Compartilhar foto com..."));
    }


    public void AlertaLista(final Context contexto, final List<Processo> ListaProcessos){
        AlertDialog.Builder builder = new AlertDialog.Builder(contexto);
        builder.setTitle("Listagem de Processamentos");
        if(ListaProcessos.size() == 0)
            Toast.makeText(contexto, "Lista de processamentos vazia", Toast.LENGTH_SHORT).show();

        else {
            CharSequence[] cs = new CharSequence[ListaProcessos.size()];
            for (int i = 0; i < ListaProcessos.size(); i++) {
                cs[i] = ListaProcessos.get(i).getProcessamentoSelecionado();
            }

            builder.setItems(cs, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            final int escolha = which;
                            AlertDialog.Builder EscolhaItem = new AlertDialog.Builder(contexto);
                            EscolhaItem.setItems(R.array.Selecionar, new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    switch (which) {
                                        case 0:
                                            ListaProcessos.remove(escolha);
                                            Toast.makeText(contexto, "processo removido!", Toast.LENGTH_SHORT).show();

                                            break;

                                        case 1:
                                            AlertDialog.Builder SubstituirItem = new AlertDialog.Builder(contexto);
                                            SubstituirItem.setItems(R.array.TiposOperacao, new DialogInterface.OnClickListener() {
                                                @Override
                                                public void onClick(DialogInterface dialog, int which) {

                                                    switch (which){

                                                        case 0:
                                                            AlertDialog.Builder OperacoesUnarias = new AlertDialog.Builder(contexto);
                                                            OperacoesUnarias.setTitle("Operações Unárias");
                                                            OperacoesUnarias.setItems(R.array.OperacoesUnarias, new DialogInterface.OnClickListener() {
                                                                @Override
                                                                public void onClick(DialogInterface dialog, int which) {
                                                                    ListView lw = ((AlertDialog) dialog).getListView();
                                                                    Object itemLista = lw.getAdapter().getItem(which);
                                                                    Processo processo = new Processo(itemLista.toString(), "Unaria");
                                                                    ListaProcessos.remove(escolha);
                                                                    ListaProcessos.add(escolha, processo);
                                                                }
                                                            }).show();
                                                            break;
                                                        case 1:
                                                            AlertDialog.Builder OperacoesBinarias = new AlertDialog.Builder(contexto);
                                                            OperacoesBinarias.setTitle("Operações Binárias");
                                                            OperacoesBinarias.setItems(R.array.OperacoesBinarias, new DialogInterface.OnClickListener() {
                                                                @Override
                                                                public void onClick(DialogInterface dialog, int which) {
                                                                    ListView lw = ((AlertDialog) dialog).getListView();
                                                                    Object itemLista = lw.getAdapter().getItem(which);
                                                                    Processo processo = new Processo(itemLista.toString(), "Unaria");
                                                                    ListaProcessos.remove(escolha);
                                                                    ListaProcessos.add(escolha, processo);
                                                                }
                                                            }).show();
                                                            break;
                                                        case 2:
                                                            AlertDialog.Builder OperacoesArea = new AlertDialog.Builder(contexto);
                                                            OperacoesArea.setTitle("Operações Área");
                                                            OperacoesArea.setItems(R.array.OperacoesArea, new DialogInterface.OnClickListener() {
                                                                @Override
                                                                public void onClick(DialogInterface dialog, int which) {
                                                                    ListView lw = ((AlertDialog) dialog).getListView();
                                                                    Object itemLista = lw.getAdapter().getItem(which);
                                                                    Processo processo = new Processo(itemLista.toString(), "Unaria");
                                                                    ListaProcessos.remove(escolha);
                                                                    ListaProcessos.add(escolha, processo);
                                                                }
                                                            }).show();
                                                            break;
                                                    }

                                                }
                                            }).show();
                                            break;
                                    }
                                }
                            }).show();

                        }
                    }

            ).show();
        }
    }
}
