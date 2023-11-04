package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.telephony.SmsManager;


public class MainActivity extends AppCompatActivity {
    private Button encenderGenerador;
    private Button iniciarPrueba;
    private Button detenerPrueba;
    private TextView messageTextView;
    String mensaje = "";
    String numeroTelefono = "+542213588203";
    public class SMSReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.getAction().equals("android.provider.Telephony.SMS_RECEIVED")) {
                // Procesa el mensaje SMS aquí
            }
        }
    }

    private void enviarMensaje(String numero, String mensaje) {
        //try {
            SmsManager smsManager = SmsManager.getDefault();
            smsManager.sendTextMessage(numero, null, mensaje, null, null);
        //} catch (Exception e) {
           // e.printStackTrace();
        //}
        //Uri uri = Uri.parse("smsto:" + numero);
        //Intent intent = new Intent(Intent.ACTION_SENDTO, uri);
        //intent.putExtra("sms_body", mensaje);
        //startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        encenderGenerador = findViewById(R.id.button);
        iniciarPrueba = findViewById(R.id.button2);
        detenerPrueba = findViewById(R.id.button3);
        messageTextView =findViewById(R.id.textView2);
        if (ActivityCompat.checkSelfPermission(MainActivity.this, android.Manifest.permission.SEND_SMS)!= PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.SEND_SMS},1);
        }
        encenderGenerador.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                mensaje = "Se encendio el generador";
                messageTextView.setText(mensaje);
                enviarMensaje(numeroTelefono,"1");
            }
        });
        iniciarPrueba.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mensaje = "Inicio Prueba";
                messageTextView.setText(mensaje);
                enviarMensaje(numeroTelefono,"2");
            }
        });
        detenerPrueba.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mensaje = "Detener Prueba";
                messageTextView.setText(mensaje);
                enviarMensaje(numeroTelefono,"3");
            }
        });
    }
}