#include "SoftwareSerial.h"
#include "pins_arduino.h"
#include "Arduino.h"
SoftwareSerial mySerial(3, 2);
class EnviarMensaje{
  private:
    int contador =0;
    
    //Se envian los mensajes por puerto serial al modulo sim800l
    void updateSerial(){
      delay(500);
      while (Serial.available()) 
      {
        mySerial.write(Serial.read());//reenvía lo que ha recibido el puerto del software serial 
      }
      while(mySerial.available()) 
      {
        Serial.write(mySerial.read());//reenvía el software serial recibido al puerto serial 
      }
    }
    //Se configura con conmando AT para el envio de mensaje de texto
    void configurarDatosMensajes(){
      String respuesta="";
      mySerial.println("AT"); //una vez que las pruebas están hechas exitosamente, regresará un OK
      //updateSerial();
      while (respuesta =="OK") {
        respuesta = mySerial.readString();
        delay(10);
        contador++;
        if(contador == 50){
          mySerial.println("AT");
          contador = 0;
          respuesta = "";
        }
      }
      mySerial.println("AT+CMGF=1"); // Configurando modo texto
      while (mySerial.readString() =="OK") {
        delay(10);
        contador++;
        if(contador == 50){
          mySerial.println("AT+CMGF=1");
          contador = 0;
          respuesta = "";
        }
      }
      mySerial.println("AT+CMGS=\"+ZZxxxxxxxxxx\"");//cambia ZZ  código del país y xxxxxxxxxxx con el número de teléfono a sms
      updateSerial();
      mySerial.println("AT+CNMI=1,2,0,0,0"); // Se  configura como se van a recibir los mensajes 
      while (mySerial.readString() =="OK") {
        delay(10);
        contador++;
        if(contador == 50){
          mySerial.println("AT+CNMI=1,2,0,0,0");
          contador = 0;
          respuesta = "";
        }
      } 
    }

  public:
    void configurar(){
      mySerial.begin(9600);
      configurarDatosMensajes();
    }
    void enviarMensajeTexto(String mensaje){
      configurarDatosMensajes();
      mySerial.print(mensaje); //contenido del texto
      updateSerial();
      //mySerial.write(26);
    }
    
};