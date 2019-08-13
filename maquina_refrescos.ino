/*

   Desarrollado por:
      - Sofia Verónica Ro
      - Alejandro Vázquez del Mercado Gutiérrez
      - Osain Abitia Alvarez

   Descripción:
      Código que controla el funcionamiento de máquina de refrescos desarrollado en Ardiuno.
      
   Fecha:
      5 de Julio 2019

*/

#include <Servo.h>

Servo myservo;

// LEDs.
const int LED = 13;


// Sensores Infrarojos.
const int SENSOR1 = 2;
const int SENSOR2 = 3;
const int SENSOR5 = 4;
const int SENSOR10 = 5;

// Motores
const int pinMotor1 = 6;
const int pinMotor2 = 7;
const int pinMotor3 = 9;

// Servo motor
const int SERVO = 11;
int pos = 0;

// Botones.
int buttonPinCoca = A0;
int buttonPinFresca = A1;

int value;

int credito = 0;

// Variables de monedas.
int monedas1 = 0;
int monedas2 = 0;
int monedas5 = 0;
int monedas10 = 0;

int cambio5 = 0;
int cambio2 = 0;
int cambio1 = 0;


// Motores


void moverServoMotor() {

   // Girar servomotor por 180º.
   for (pos = 0; pos <= 180; pos += 1) { 
      myservo.write(pos);              
      delay(15);                       
  }
    
  
}

void calcularCambio(int sobrante) {

  cambio5 = 0;
  cambio2 = 0;
  cambio1 = 0;

  while(sobrante >= 5) {
     cambio5 += 1;
     digitalWrite(pinMotor3, 255);
     delay(2000);
     digitalWrite(pinMotor3, LOW);
     sobrante -= 5;
  }

  Serial.print("Cambio en monedas de 5: ");
  Serial.println(cambio5);

  while(sobrante >= 2) {
    cambio2 += 1;
    digitalWrite(pinMotor2, HIGH);
    delay(1500);
    digitalWrite(pinMotor2, LOW);
    sobrante -= 2;
  }

  Serial.print("Cambio en monedas de 2: ");
  Serial.println(cambio2);

  while(sobrante >= 1) {
    cambio1 += 1;
    digitalWrite(pinMotor1, HIGH);
    delay(600);
    digitalWrite(pinMotor1, LOW);
    sobrante -= 1;
  }

  Serial.print("Cambio en monedas de 1: ");
  Serial.println(cambio1);

  credito = 0;
  
  
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(250000);

  // Inicializar Sensores Infrarojos.
  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(SENSOR5, INPUT);
  pinMode(SENSOR10, INPUT);

  // Inicializar Botones.
  pinMode(buttonPinCoca, INPUT);
  pinMode(buttonPinFresca, INPUT);

  // Servo Motor
  pinMode(SERVO, OUTPUT);
  myservo.attach(11);

  // Declarar motores.
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);

  digitalWrite(buttonPinCoca, HIGH);
  digitalWrite(buttonPinFresca, HIGH);

  for(int i = 8; i < 11; i++){
    pinMode(i, OUTPUT);  
  }
  
}

void loop() {

  cambio5 = 0;
  cambio2 = 0;
  cambio1 = 0;



  // Lectura de sensores infrarojos.
  
  if(digitalRead(SENSOR1) == LOW) {
    
    credito += 1;
    Serial.println(credito);
    delay(500);
  
  }


  if(digitalRead(SENSOR2) == LOW) {

    credito += 2;
    monedas2 += 1;
    Serial.println(credito);
    delay(500);
    
  }

  if(digitalRead(SENSOR5) == LOW) {

    credito += 5;
    Serial.println(credito);
    delay(500);
    
  }

  if(digitalRead(SENSOR10) == LOW) {

    credito += 10;
    Serial.println(credito);
    delay(5000);
    
  }

  /* 
  Serial.println("Monedas de $1: " + monedas1);
  Serial.println("Monedas de $2: " + monedas2);
  Serial.println("Monedas de $5: " + monedas5);
  Serial.println("Monedas de $10: " + monedas10); 
  Serial.println("Dinero Total: " + credito); */


  // Si hacen click al boton de Coca.
  if(digitalRead(buttonPinCoca) == LOW) {

    Serial.println("CLicked");
  
    if(credito >= 13) {
      Serial.println("Dar Producto");
      moverServoMotor();

      int sobrante = credito - 13;
      credito = sobrante;
      Serial.print("Sobran ");
      Serial.println(sobrante);
      
      if(sobrante > 0) {
        calcularCambio(sobrante);
      }
      
      
    } else {
      Serial.println("Credito insuficiente");
    }

  delay(1000);
  digitalWrite(buttonPinCoca, HIGH);
    
  }

  // Si hacen click al boton de Fresca.
  if(digitalRead(buttonPinFresca) == LOW) {

    Serial.println("CLicked");
  
    if(credito >= 12) {
      Serial.println("Dar Producto");
      moverServoMotor();
      
      int sobrante = credito - 12;
      credito = sobrante;
      Serial.print("Sobran ");
      Serial.println(sobrante);
      
      if(sobrante > 0) {
        calcularCambio(sobrante);
      }
    } else {
      Serial.println("Credito insuficiente");
    }

  delay(1000);
  digitalWrite(buttonPinFresca, HIGH);
    
  }
    
  
  


}
