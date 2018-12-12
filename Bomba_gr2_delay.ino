/*
 * Programa para control de bomba
 * Granados Villeda Johan Raciel
 * Versión 1.5
*/

#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include "GFButton.h"

//CONSTANTES
const long intervalo = 2;  //Intervalo de tiempo de la bomba
const int led1 = 2; //LED de control
const int ledB = 3; 
const int rele = 5;// Relevador

//VARIABLES GLOBALES
unsigned long tiempo1 = 0; //Para millis, sustitucion de ciclo for con delays      
bool estado = true; //para definir estado de la bomba. TRUE = apagado, FALSE = encendido. 
bool def = true;
int Nivel = 0; //Para lectura Analogica
int pulsador=0;
int x=0;
int g=0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
GFButton button(7);

void setup() {
  Serial.begin(9600); //Se inicializa la comunicación
  pinMode(led1,OUTPUT); //pin como salida
  pinMode(rele,OUTPUT); //pin como salida   
  pinMode(ledB,OUTPUT); //pin como salida
  lcd.begin(16, 2); // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.home (); // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.print("*Powered by Gr2*");
  delay(1000);
}

void loop() {
  lcd.clear();
  lcd.home (); // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.print("DEFINIENDO");
  
  definiendo(); 

  if(!def)
  {
    while(x != g)
    {
      Serial.println(analogRead(A2)); //Depuración
      Nivel=analogRead(A2);
      int i=0;
      if(Nivel>500)
      { //Tanque lleno 
        digitalWrite(rele,HIGH);//Encender bomba
        digitalWrite(led1,HIGH); //Bomba encendida
        for(i=1;i<=intervalo;i++)
        {
          Serial.print(i);
          Serial.print(" | \n");
          delay(1000);
        }
        digitalWrite(rele,LOW);//Apagar bomba
        digitalWrite(led1,LOW); //Bomba apagada
        Nivel=0;
        g++;
      }
       lcd.setCursor(0,1);
       lcd.print("Bombeados: ");
       lcd.print(g);
    }
    def=true; 
    lcd.home (); // Mover el cursor a la primera posición de la pantalla (0, 0)
    lcd.clear();
    lcd.print("*Powered by Gr2*");
    g=0;
    x=0;
  }

  delay(5000);
}

void definiendo()
{
  unsigned long time1=millis();
  
  while(millis() < (time1 + 10000))
  {
    //Serial.println("UPSI");
    if(button.isPressed()) 
    { 
      digitalWrite(ledB,HIGH);
      delay(150);
      x++;
      Serial.println(x);
      lcd.home (); // Mover el cursor a la primera posición de la pantalla (0, 0)
      lcd.print("Por bombear: ");
      lcd.setCursor(14,0);
      lcd.print(x);
    }
    else
    {
      digitalWrite(ledB,LOW);
    }
  }

  if(x==0)
  {
      lcd.home (); // Mover el cursor a la primera posición de la pantalla (0, 0)
      lcd.clear();
      lcd.print("Por bombear: 0");
  }
  else
  {
    def = false;
  }
}

