#Comunicacion para encender un Generador electrico

## Comunicacion: se utilizan los pines 3 y 2 para realizar una comunicacion serial con el modulo SIM800l
## Falla del gnerador: si hay falla por que el generador no pudo encender me van llegar una señal por el pin 4 y me envia un mensaje de texto que dice falla del generador
## Señales de red: las señales que me indican cual es la red que esta operando van a a funcionar por los pines 5, 6, 7 que van a ser las señales de la red electrica R S T, si cambia de fase electrica me va a llegar un mensaje que me indique qe señal se esta alimentando
## recepcion de mensaje: envias un mensaje de texto con el numero 1 para encender el generador 
