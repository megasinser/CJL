#include <Servo.h>
#include <NewPing.h>

// Definir pines
const int pinServo = 6;
const int pinMotorAdelante = 9;  // Pin PWM para el motor de avance
const int pinMotorAtras = A0;    // Pin PWM para el motor de retroceso (sin uso en este código)
const int pinEnable = 5;         // Pin para habilitar el puente H (Enable) para controlar la velocidad
const int pinAvviso = A1;        // Pin donde se recibe la señal de vuelta completada (A0)

// Definir ángulos del servo
const int ANGULO_CENTRO = 80;
const int ANGULO_IZQUIERDA = 160;
const int ANGULO_DERECHA = 20;
const int ANGULO_IZQUIERDA_C = 120;
const int ANGULO_DERECHA_C = 60;

// Configuración de los sensores ultrasónicos
const int PIN_TRIGGER_1 = 7;
const int PIN_ECHO_1 = 8;
const int MAX_DISTANCIA_1 = 150;  // Distancia máxima de detección en cm para el primer sensor (izquierda)
NewPing sonar1(PIN_TRIGGER_1, PIN_ECHO_1, MAX_DISTANCIA_1);

const int PIN_TRIGGER_2 = 3;
const int PIN_ECHO_2 = 2;
const int MAX_DISTANCIA_2 = 150;  // Distancia máxima de detección en cm para el segundo sensor (derecha)
NewPing sonar2(PIN_TRIGGER_2, PIN_ECHO_2, MAX_DISTANCIA_2);

const int PIN_TRIGGER_3 = 4;
const int PIN_ECHO_3 = 11;
const int MAX_DISTANCIA_3 = 200;  // Distancia máxima de detección en cm para el sensor de frente
NewPing sonar3(PIN_TRIGGER_3, PIN_ECHO_3, MAX_DISTANCIA_3);

// Rango de distancia de referencia (margen tolerable)
const int DISTANCIA_MIN = 20;  // Distancia mínima aceptable (en cm)
const int DISTANCIA_MAX = 30;  // Distancia máxima aceptable (en cm)

// Velocidad fija para los motores (controlada por el pin enable)
const int VELOCIDAD = 250;  // Ajusta la velocidad aquí (valor entre 0 y 255)

Servo miServo;  // Crear objeto servo

bool detenerRobot = false;  // Variable para determinar si detener el robot

void setup() {
  pinMode(13, INPUT);  // Pin 13 como entrada (rojo)
  pinMode(12, INPUT);  // Pin 12 como entrada (verde)
  pinMode(10, INPUT);  // Pin 10 como entrada (ninguno)
  pinMode(pinAvviso, INPUT);  // Configurar A0 (pinAvviso) como entrada
  
  // Inicializar el servo
  miServo.attach(pinServo);
  
  // Configuración de los pines de los motores
  pinMode(pinMotorAdelante, OUTPUT);
  pinMode(pinMotorAtras, OUTPUT);  // No se utiliza en este código
  pinMode(pinEnable, OUTPUT);  // Configurar el pin Enable como salida
  
  // Inicialización del servo en el centro
  miServo.write(ANGULO_CENTRO);

  // Configuración de la comunicación serial para monitorear la distancia
  Serial.begin(9600);
  Serial.println("Esclavo listo para recibir datos...");
}

void loop() {
  // Comprobar si se recibe la señal del primer Arduino para detener el robot
  int estadoAvviso = digitalRead(pinAvviso);  // Leer el pin A1
  
  if (estadoAvviso == HIGH) {
    Serial.println("Vueltas completadas. Deteniendo el robot...");
    detenerRobot = true;  // Cambiar el estado para detener el robot
  }

  if (detenerRobot) {
    // Si la variable detenerRobot es true, se detiene todo el funcionamiento del robot
    digitalWrite(pinMotorAdelante, LOW);  // Detener motor
    Serial.println("Robot detenido permanentemente.");
    return;  // Detener el ciclo del loop
  }

  int estadoRojo = digitalRead(13);  // Leer pin 13 (rojo)
  int estadoVerde = digitalRead(12);  // Leer pin 12 (verde)
  int estadoNinguno = digitalRead(10);  // Leer pin 10 (ninguno)

  // Imprimir el color detectado basado en el pin activo
  if (estadoRojo == HIGH) {
    Serial.println("Rojo detectado");
    miServo.write(ANGULO_DERECHA);  // Gira a la derecha
    delay(500);
  } 
  else if (estadoVerde == HIGH) {
    Serial.println("Verde detectado");
    miServo.write(ANGULO_IZQUIERDA);  // Gira a la izquierda
    delay(500);
  } 
  else if (estadoNinguno == HIGH) {
    Serial.println("No se detecta color");
    miServo.write(ANGULO_CENTRO);  // Mantener en el centro
  }

  delay(100);

  // Obtener las distancias medidas por los tres sensores ultrasónicos
  int distancia1 = sonar1.ping_cm();  // Primer sensor (izquierda)
  int distancia2 = sonar2.ping_cm();  // Segundo sensor (derecha)
  int distancia3 = sonar3.ping_cm();  // Tercer sensor (frente)
  
  // Imprimir las distancias medidas en el monitor serie
  Serial.print("Derecha: ");
  Serial.print(distancia1);
  Serial.print(" cm, ");
  Serial.print("Izquierda: ");
  Serial.print(distancia2);
  Serial.print(" cm, ");
  Serial.print("Frente: ");
  Serial.println(distancia3);
  
  // Comprobar las condiciones de los sensores
  if (distancia1 < 25 && distancia1 > 5) {
    // Gira completamente a la izquierda si alguna condición se cumple
    miServo.write(ANGULO_IZQUIERDA_C);
    Serial.println("Giro izquierda");
    delay(250);  // Mantener esta posición un breve tiempo
  } 
  else if (distancia2 == 0 && distancia3 < 70 && distancia3 > 1 || distancia2 > distancia1 && distancia3 < 70 && distancia3 > 1 ) {
    // Gira completamente a la derecha si alguna condición se cumple
    miServo.write(ANGULO_IZQUIERDA);
    Serial.println("Giro esquina izquierda");
    delay(1000);
    miServo.write(ANGULO_CENTRO);
    Serial.println("corrigiendo");
    delay(1000);
  }
  else if ( distancia2 < 25 && distancia2 > 5 ) {
    // Gira completamente a la derecha si alguna condición se cumple
    miServo.write(ANGULO_DERECHA_C);
    Serial.println("Giro derecha");
    delay(250);  // Mantener esta posición un breve tiempo
  }
  else if (distancia1 > distancia2 && distancia3 < 70 && distancia3 > 1 || distancia1 == 0 && distancia3 < 70 && distancia3 >1 ) {
    // Gira completamente a la derecha si alguna condición se cumple
    miServo.write(ANGULO_DERECHA);
    Serial.println("Giro esquina derecha");
    delay(1000);
    miServo.write(ANGULO_CENTRO);
    Serial.println("corrigiendo");
    delay(1000);
  }
      
  else {
    // Si ninguna condición se cumple, el servo se mantiene en el ángulo central
    miServo.write(ANGULO_CENTRO);
    Serial.println("Avanzando al frente");
    delay(150);
  }

  analogWrite(pinEnable, VELOCIDAD);  // Controlar la velocidad con el pin enable

  // Control de la dirección del motor
  digitalWrite(pinMotorAdelante, HIGH);  // Habilitar el motor para avanzar
  digitalWrite(pinMotorAtras, LOW);      // Desactivar el motor de retroceso
  
  // Agregar un pequeño retraso para estabilizar el robot (ajustable)
  delay(100);
}
