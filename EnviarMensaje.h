#include "HardwareSerial.h"
#include "WString.h"
#include "SoftwareSerial.h"
#include "pins_arduino.h"
#include "Arduino.h"
SoftwareSerial mySerial(3, 2);
class EnviarMensaje{
  private:
    const int encenderMotor = 9;
    const int prueba = 10;
    int contador =0;
    String respuesta="";
    String mensaje="";
    String numeroTelefono = "";
    //Se envian los mensajes por puerto serial al modulo sim800l
    String recepcionSerial(){
      while(mySerial.available()) {
       String respuesta = mySerial.readStringUntil('\n');
        Serial.println(respuesta);
        int valorRecibido = respuesta.indexOf("+");
        if (valorRecibido > -1) {
          numeroTelefono = respuesta.substring(7, 18);
          Serial.println(numeroTelefono);
          mensaje = mySerial.readStringUntil('\n');
          Serial.println("el mensaje es");
          Serial.println(mensaje);
        }
      }
      return respuesta;
    }

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
      delay(500);
      respuesta = recepcionSerial();
      while(strcmp(respuesta.c_str(), "OK") == 0) {
        mySerial.println("AT+CMGF=1"); //una vez que las pruebas están hechas exitosamente, regresará un OK
        delay(100);
        respuesta = recepcionSerial();
      }
      mySerial.println("AT+CNMI=1,2,0,0,0"); // Se  configura como se van a recibir los mensajes 
      delay(100);
      respuesta = recepcionSerial();
      while(strcmp(respuesta.c_str(), "OK") == 0) {
        mySerial.println("AT+CNMI=1,2,0,0,0"); //una vez que las pruebas están hechas exitosamente, regresará un OK
        delay(100);
        respuesta = recepcionSerial();
      }
      
    }
    void accionesMensajes(int valor){
      //Serial.println("entro en accionesMensajes");
      switch (valor) {
      case 1:
        Serial.println("Se enciende el motor");
        digitalWrite(encenderMotor, LOW);
        delay(5000);
        digitalWrite(encenderMotor, HIGH);
        mensaje ="";
        //enviarMensajeTexto("Generador encendido");
        break;

        case 2:
        Serial.println("Prueba encendio");
        digitalWrite(prueba, LOW);
        mensaje ="";
        break;

        case 3:
        Serial.println("Prueba apago");
        digitalWrite(prueba, HIGH);
        mensaje ="";
        break;
      }
    }

  public:
    void configurar(){
      mySerial.begin(9600);
      pinMode(encenderMotor, OUTPUT);
      configurarMensajes();
      pinMode(prueba, OUTPUT);
      digitalWrite(encenderMotor, HIGH);
      digitalWrite(prueba, HIGH);
    }
    void enviarMensajeTexto(String mensaje){
      Serial.println("empieza el envio de mensajes");
      configurarMensajes();
      mySerial.println("AT+CMGS=\"+2215243497\"");//cambia ZZ  código del país y xxxxxxxxxxx con el número de teléfono a sms
      delay(500);
      respuesta = recepcionSerial();
      mySerial.print(mensaje); //contenido del texto
      respuesta = recepcionSerial();
      Serial.println(respuesta);
      mySerial.write(26);
      Serial.println("Se envia seguno mensaje");
      configurarMensajes();
      mySerial.println("AT+CMGS=\"+2215688347\"");//cambia ZZ  código del país y xxxxxxxxxxx con el número de teléfono a sms
      delay(500);
      respuesta = recepcionSerial();
      mySerial.print(mensaje); //contenido del texto
      respuesta = recepcionSerial();
      Serial.println(respuesta);
      mySerial.write(26);
      
    }
    void recibirMensaje(){
      respuesta = recepcionSerial();
      
      accionesMensajes(mensaje.toInt());
    }
};