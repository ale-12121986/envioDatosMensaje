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

// void serialEvent(){
//   //Recepción de datos Seriales
//   while (Serial.available()) {              //Si existen datos seriales, leer a todos
//     char CaracterEntrada = Serial.read();   //Leer 1 byte serial recibido
   
//     cadenaCharEntrada += CaracterEntrada;   //Agregar el nuevo char a una cadena String 
//     if (CaracterEntrada == '\n') {          //Si el char o byte recibido es un fin de linea, activa la bandera
//       finCadena = true;                        //Si la bandera finCadena = 1, entonces la transmision esta completa
//     }  
//   }
  
// }

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
  //Serial.println("envio demensajes activado");
  // put your main code here, to run repeatedly: 
  if((digitalRead(senalR))&&(senalRAnterior == 0)) {
    senalRAnterior = 1;
    senalSAnterior = 0;
    senalTAnterior = 0;
    enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase R");
  } 
  else if((digitalRead(senalS))&&(senalSAnterior == 0)) {
    senalRAnterior = 0;
    senalSAnterior = 1;
    senalTAnterior = 0;
    //enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase S");
  //statements
  } 
  else if((digitalRead(senalT))&&(senalTAnterior == 0)) {
    senalRAnterior = 0;
    senalSAnterior = 0;
    senalTAnterior = 1;
    enviarMensaje.enviarMensajeTexto("Se trabaja con la la fase T");
  //statements
  }
  if(digitalRead(fallaEncendido) == HIGH){
    if(mensajeEnviado == true){
      mensajeEnviado = true;
    enviarMensaje.enviarMensajeTexto("falla en el encendido");
    }    
  }
}
