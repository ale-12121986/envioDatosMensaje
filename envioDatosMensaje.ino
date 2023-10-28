#include "EnviarMensaje.h"
#include "SoftwareSerial.h"
//SoftwareSerial mySerial(3, 2);
const int fallaEncendido = 4;  // Entrada de falla de encendido
const int senalR = 5;  // entrada de señal R
const int senalS = 6;  // entrada de señal S
const int senalT = 7;  // entrada de señal T
const int marcha = 8;  //generador en marcha
int  fallaAccion;
int senalActiva = 0;
int senalRAnterior = 0;
int senalSAnterior = 0;
int senalTAnterior = 0;
int marchaAnterior = 0;
int fallaEncendidoAnterior = 0;
String cadenaCharEntrada = "", fallaGenerador = "";  
char vectorChar[20];
bool mensajeEnviado = false, finCadena = false;
EnviarMensaje enviarMensaje;

void setup() {
  // put your setup code here, to run once:
  pinMode(fallaEncendido, INPUT);
  pinMode(senalR, INPUT);
  pinMode(senalS, INPUT);
  pinMode(senalT, INPUT);
  pinMode(marcha, INPUT);

  Serial.begin(9600);
  enviarMensaje.configurar();
  cadenaCharEntrada.reserve(20);
  Serial.println("envio demensajes activado");
}

void loop() {
  enviarMensaje.recibirMensaje();
  if(digitalRead(senalR)== LOW && senalRAnterior == 0) {
    Serial.println("entro a ver señal R");
    senalRAnterior = 1;
    senalSAnterior = 0;
    senalTAnterior = 0;
    marchaAnterior = 0;
    enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase R");
  } 
  else if(digitalRead(senalS) == LOW && senalSAnterior == 0) {
    Serial.println("entro a ver señal S");
    senalRAnterior = 0;
    senalSAnterior = 1;
    senalTAnterior = 0;
    marchaAnterior = 0;
    fallaEncendidoAnterior = 0;
    enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase S");
  } 
  else if(digitalRead(senalT) == LOW && senalTAnterior == 0) {
    Serial.println("entro a ver señal T");
    senalRAnterior = 0;
    senalSAnterior = 0;
    senalTAnterior = 1;
    marchaAnterior = 0;
    fallaEncendidoAnterior = 0;
    enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase T");
  }
  if(digitalRead(marcha) == LOW && marchaAnterior == 0) {
    Serial.println("entro a ver señal T");
    senalRAnterior = 0;
    senalSAnterior = 0;
    senalTAnterior = 0;
    marchaAnterior = 1;
    fallaEncendidoAnterior = 0;
    enviarMensaje.enviarMensajeTexto("Generador en marcha");
  }
  if(digitalRead(fallaEncendido) == LOW && fallaEncendidoAnterior == 0){
    Serial.print("hay falla al encender el generador");
    senalRAnterior = 0;
    senalSAnterior = 0;
    senalTAnterior = 0;
    marchaAnterior = 0;
    fallaEncendidoAnterior = 1;
    enviarMensaje.enviarMensajeTexto("falla en el encendido");
  }

  
}
