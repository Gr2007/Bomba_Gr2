/*
 * Programa para control de bomba
 * Granados Villeda Johan Raciel
 * Alpha 1
*/

const int led1=2; //LEDS de control
const int led2=3;
const int led3=4;
const int rele=5;// Relevador
int Nivel;

void setup() {
  Serial.begin(9600); //Se inicializa la comunicación
  pinMode(led1,OUTPUT); //pin como salida
  pinMode(led2,OUTPUT); //pin como salida
  pinMode(led3,OUTPUT); //pin como salida
  pinMode(rele,OUTPUT); //pin como salida
  digitalWrite(led1, HIGH); // Indicador de encendido
  digitalWrite(led3,HIGH); // Indicador modo espera
}

void loop() {
  
  Serial.println(analogRead(A5)); //Depuración
  Nivel=analogRead(A5);
  
  if(Nivel>620){ //Tanque lleno 
    digitalWrite(led3,LOW); //Apagar modo espera
    digitalWrite(led2,HIGH); //Indicador de bomba encendida
    digitalWrite(rele,HIGH);//Encender bomba
    delay(240000000); //4 minutos de bombeo
    digitalWrite(rele,LOW);//Apagar bomba
    digitalWrite(led2,LOW); //Bomba apagada
    digitalWrite(led3,HIGH); // Indicador modo espera
    }
    
  delay(100); //100 micorsegundos entre ciclo de verificación

}
