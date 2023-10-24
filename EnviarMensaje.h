#include "WString.h"
#include "SoftwareSerial.h"
#include "pins_arduino.h"
#include "Arduino.h"
SoftwareSerial mySerial(3, 2);
class EnviarMensaje{
  private:
    int contador =0;
    String respuesta="";
    //Se envian los mensajes por puerto serial al modulo sim800l
    String recepcionSerial(){
      while(mySerial.available()) {
       String respuesta = mySerial.readStringUntil('\n');
        Serial.println(respuesta);
      }
      return respuesta;
    }

    // void updateSerial(){
    //   delay(500);
    //   while (Serial.available()) 
    //   {
    //     mySerial.write(Serial.read());//reenvía lo que ha recibido el puerto del software serial 
    //   }
    //   while(mySerial.available()) 
    //   {
    //     Serial.write(mySerial.read());//reenvía el software serial recibido al puerto serial 
    //   }
    // }
    //Se configura con conmando AT para el envio de mensaje de texto
    void configurarMensajes(){
      Serial.println("entro a configurar mensaje");
      mySerial.println("AT"); //una vez que las pruebas están hechas exitosamente, regresará un OK
      delay(100);
      respuesta = recepcionSerial();
      while(strcmp(respuesta.c_str(), "OK") == 0) {
        mySerial.println("AT"); //una vez que las pruebas están hechas exitosamente, regresará un OK
        delay(100);
        respuesta = recepcionSerial();
      }
      //respuesta="";
      mySerial.println("AT+CMGF=1"); // Configurando modo texto
      delay(100);
      respuesta = recepcionSerial();
      while(strcmp(respuesta.c_str(), "OK") == 0) {
        mySerial.println("AT+CMGF=1"); //una vez que las pruebas están hechas exitosamente, regresará un OK
        delay(100);
        respuesta = recepcionSerial();
      }
      mySerial.println("AT+CMGS=\"+543584315941\"");//cambia ZZ  código del país y xxxxxxxxxxx con el número de teléfono a sms
      delay(100);
      respuesta = recepcionSerial();
      delay(100);
      respuesta = recepcionSerial();
      mySerial.println("AT+CNMI=1,2,0,0,0"); // Se  configura como se van a recibir los mensajes 
      delay(100);
      respuesta = recepcionSerial();
      while(strcmp(respuesta.c_str(), "OK") == 0) {
        mySerial.println("AT+CNMI=1,2,0,0,0"); //una vez que las pruebas están hechas exitosamente, regresará un OK
        delay(100);
        respuesta = recepcionSerial();
      }
    }

  public:
    void configurar(){
      mySerial.begin(9600);
      configurarMensajes();
    }
    void enviarMensajeTexto(String mensaje){
      Serial.println("empieza el envio de mensajes");
      configurarMensajes();
      mySerial.print(mensaje); //contenido del texto
      //updateSerial();
      //mySerial.write(26);
    }
    
};