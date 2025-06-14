#include <Pixy2.h>

// Definir pines de salida
const int pinRojo = 8;
const int pinVerde = 9;
const int pinNinguno = 10;
const int pinAvviso = 3;  // Pin para aviso de vueltas completadas

Pixy2 pixy;

int contadorEsquinas = 0;  // Contador de esquinas detectadas

// Variables para controlar el retraso entre detecciones
unsigned long tiempoUltimaDeteccion = 0;  // Para controlar el tiempo entre detecciones
const unsigned long retrasoDeteccion = 2000;  // 2 segundos de retraso entre detecciones

void setup() {
  pinMode(pinRojo, OUTPUT);   // Pin para rojo
  pinMode(pinVerde, OUTPUT);  // Pin para verde
  pinMode(pinNinguno, OUTPUT); // Pin para cuando no hay color
  pinMode(pinAvviso, OUTPUT); // Pin para indicar que se completaron las 12 vueltas

  Serial.begin(9600);  // Comunicación serial para depuración
  pixy.init();         // Inicializar Pixy2
}

void loop() {
  unsigned long tiempoActual = millis();  // Obtener el tiempo actual
  digitalWrite(pinAvviso, LOW);
  // Verificar si ha pasado el tiempo de retraso
  if (tiempoActual - tiempoUltimaDeteccion >= retrasoDeteccion) {
    // Obtener bloques detectados por Pixy
    pixy.ccc.getBlocks();

    // Verificar si se detectan bloques
    if (pixy.ccc.numBlocks) {
      for (int i = 0; i < pixy.ccc.numBlocks; i++) {
        byte colorData = pixy.ccc.blocks[i].m_signature;  // Firma del bloque detectado

        // Si se detecta un color y aún no se ha procesado este color, entramos en un ciclo while
        if (colorData == 3 || colorData == 4) {  // Detecta las esquinas (por ejemplo, firmas 3 y 4)
          // digitalWrite(pinRojo, HIGH);
           // Enciende pin 8 para rojo
           Serial.println("rojo");

          // digitalWrite(pinVerde, LOW);   // Apaga pin 9 para verde
          Serial.println("verde");

          digitalWrite(pinNinguno, LOW); // Apaga pin 10
          Serial.println("Esquina detectada");

          // Mantener el ciclo while mientras la firma 3 o 4 sea detectada
          while (pixy.ccc.numBlocks > 0) {
            pixy.ccc.getBlocks();  // Continuar obteniendo bloques detectados
            for (int j = 0; j < pixy.ccc.numBlocks; j++) {
              if (pixy.ccc.blocks[j].m_signature != colorData) {
                break;  // Si el color no es el mismo, salir del ciclo while
              }
            }
            delay(1000);  // Esperar un poco para evitar sobrecargar el procesador
          }

          // Al salir del ciclo while, significa que la esquina ya no está siendo detectada
          contadorEsquinas++;  // Incrementar el contador de esquinas
          Serial.print("Esquinas detectadas: ");
          Serial.println(contadorEsquinas);

          // Verificar si se han completado 12 esquinas
          if (contadorEsquinas >= 12) {
            Serial.println("Vueltas completadas");
            digitalWrite(pinAvviso, HIGH);  // Enviar HIGH al pin de aviso
            delay(100000);  // Mantener el HIGH por medio segundo
            //digitalWrite(pinAvviso, LOW);  // Volver a LOW el pin de aviso
            // contadorEsquinas = 0;  // Resetear el contador para comenzar de nuevo
          
          }

          // Resetear la detección de color después de un breve retraso
          tiempoUltimaDeteccion = tiempoActual;
          break;  // Salir del ciclo for principal después de procesar una esquina
        }
      }
    } else {
      digitalWrite(pinRojo, LOW);   // Apaga pin 8 para rojo
      digitalWrite(pinVerde, LOW);  // Apaga pin 9 para verde
      digitalWrite(pinNinguno, HIGH); // Enciende pin 10
      Serial.println("No se detectaron bloques");
    }
  }

  delay(100);  // Espera antes de la próxima lectura de Pixy
}
