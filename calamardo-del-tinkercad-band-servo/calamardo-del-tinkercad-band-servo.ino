#include <Servo.h>                // Incluye la libreria Servo
 
Servo servo8;                    // Crea el objeto servo8 con las caracteristicas de Servo
#define PIR 3
#define VERDE 6
#define RED 7
#define ROJOS 13
#define buzzerPin 11

unsigned long millisPrevios, tiempoReferencia;
int duracion, juego, band, tiempoSensado, b, b2;

void setup() {
  tone(buzzerPin, 741, 300);
  Serial.begin(9600);
  Serial.println("Iniciando...");
  pinMode(ROJOS,OUTPUT);
  pinMode(RED,OUTPUT);
  pinMode(VERDE,OUTPUT);
  pinMode(PIR, INPUT);
  servo8.write(90);
  servo8.attach(8,544,2400);
  millisPrevios = 0;
  tiempoReferencia = 0;
  duracion = 300;
  juego = 0;
  band = 0;
  b = 0;
  b2 = 0;
  tiempoSensado = 3000;
  digitalWrite(ROJOS, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(VERDE, HIGH);
  attachInterrupt(digitalPinToInterrupt(2), modo, RISING);
  delay(20000); //delay para el PIR
  digitalWrite(ROJOS, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(VERDE, LOW);
  delay(300);
  tone(buzzerPin, 741, 300);
  digitalWrite(ROJOS, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(VERDE, HIGH);
  delay(300);
  digitalWrite(ROJOS, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(VERDE, LOW);
  delay(300);
  tone(buzzerPin, 741, 300);
  digitalWrite(ROJOS, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(VERDE, HIGH);
  delay(300);
  digitalWrite(ROJOS, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(VERDE, LOW);
  servo8.write(0);
  delay(600);
  Serial.println("LISTO!");
}

void loop() {
  
  if(juego == 1){ //Juego Iniciado
    //delay (100);
    servo8.write(180); // Gira el servo para quedarse se espalda
    if (b2 == 0){
      servo8.attach(8,544,2400);
      b2 = 1;
    }
    song();                  
    servo8.write(0);     //Gira el servo y mira a los participantes 
    //delay(1300);  //Ver si se puede sacar este delay
    digitalWrite(ROJOS, HIGH);
    tiempoReferencia = millis();
    while((millis() - tiempoReferencia <= tiempoSensado) && (band == 0)){
      if(digitalRead(PIR)) band = 1; 
      if(juego == 0) break;
    }
    digitalWrite(ROJOS, LOW);
    if(band == 1){
      for (int i = 0; i < 30; i++) {  // Ciclo para el parpadeo de los ojos
        digitalWrite(ROJOS, HIGH);
        delay(100); 
        digitalWrite(ROJOS, LOW);
        delay(100);
      }
      digitalWrite(RED, HIGH);
      tone(buzzerPin, 741, 1000);
      Serial.println("Jugador eliminado.");
      delay(2000);
      Serial.println("Saliendo jugador...");
      delay(2000);
      digitalWrite(RED, LOW);
      band = 0;
    } else {
      //Si no detectó nada, luz verde y que prosiga
      digitalWrite(VERDE, HIGH);
      tone(buzzerPin, 525, 300);
      delay(600);
      digitalWrite(VERDE, LOW);
    }
    if (duracion >= 150){
      duracion = duracion - 30;
    }
  } else {
    //Juego Terminado
    if (b == 0){
      servo8.write(0);// Gira el servo a 0 grados de frente
      delay(1000);
      b = 1;
      servo8.detach();
    }
  }
}

void modo(){
  if(juego == 0){
    juego = 1;
    b = 0;
    Serial.println("Juego iniciado");
  } else {
    juego = 0;
    b2 = 0;
    duracion = 300; //Reiniciando la duración del tempo
    tone(11, 741, 300);
    Serial.println("Finalizando Juego");
  }
}

void song(){
  
  tone(buzzerPin, 466);
  delay(duracion);
  noTone(buzzerPin);

  tone(buzzerPin, 622);
  delay(duracion);
  noTone(buzzerPin);

  tone(buzzerPin, 622);
  delay(duracion*2);
  noTone(buzzerPin);

  tone(buzzerPin, 622);
  delay(duracion*2);
  noTone(buzzerPin);

  tone(buzzerPin, 554);
  delay(duracion*2);
  noTone(buzzerPin);

  tone(buzzerPin, 622);
  delay(duracion);
  noTone(buzzerPin);

  tone(buzzerPin, 622);
  delay(duracion);
  noTone(buzzerPin);

  tone(buzzerPin, 466);
  delay(duracion);
  noTone(buzzerPin);

  tone(buzzerPin, 466);
  delay(duracion);
  noTone(buzzerPin);

  tone(buzzerPin, 554);
  delay(duracion*2);
  noTone(buzzerPin);
}
