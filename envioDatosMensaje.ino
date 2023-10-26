#include "EnviarMensaje.h"
#include "SoftwareSerial.h"
//SoftwareSerial mySerial(3, 2);
const int fallaEncendido = 4;  // Entrada de falla de encendido
const int senalR = 5;  // entrada de señal R
const int senalS = 6;  // entrada de señal S
const int senalT = 7;  // entrada de señal T
const int encenderMotor = 8; 
int  fallaAccion;
int senalActiva = 0;
int senalRAnterior = 0;
int senalSAnterior = 0;
int senalTAnterior = 0;
String cadenaCharEntrada = "", fallaGenerador = "";  
char vectorChar[20];
bool mensajeEnviado = false, finCadena = false;
EnviarMensaje enviarMensaje;

void setup() {
  // put your setup code here, to run once:
  //mySerial.begin(9600);
  pinMode(fallaEncendido, INPUT);
  pinMode(senalR, INPUT);
  pinMode(senalS, INPUT);
  pinMode(senalT, INPUT);
  pinMode(encenderMotor, OUTPUT);
  Serial.begin(9600);
  enviarMensaje.configurar();
  cadenaCharEntrada.reserve(20);
  Serial.println("envio demensajes activado");
}

void loop() {
  enviarMensaje.recibirMensaje();
  if((digitalRead(senalR))&&(senalRAnterior == 0)) {
    Serial.println("entro a ver señal R");
    senalRAnterior = 1;
    senalSAnterior = 0;
    senalTAnterior = 0;
    enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase R");
  } 
  else if((digitalRead(senalS))&&(senalSAnterior == 0)) {
    Serial.println("entro a ver señal S");
    senalRAnterior = 0;
    senalSAnterior = 1;
    senalTAnterior = 0;
    enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase S");
  //statements
  } 
  else if((digitalRead(senalT))&&(senalTAnterior == 0)) {
    Serial.println("entro a ver señal T");
    senalRAnterior = 0;
    senalSAnterior = 0;
    senalTAnterior = 1;
    enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase T");
  //statements
  }
  if(digitalRead(fallaEncendido) == HIGH){
    Serial.print("hay falla al encender el generador");
    if(mensajeEnviado == true){
      mensajeEnviado = true;
    enviarMensaje.enviarMensajeTexto("falla en el encendido");
    }    
  }

  
}
