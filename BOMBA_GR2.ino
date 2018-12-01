/*
 * Programa para control de bomba
 * Granados Villeda Johan Raciel
 * Alpha 5
*/

const int led1=2; //LEDS de control
const int led2=3;
const int rele=5;// Relevador
int Nivel;

void setup() {
  Serial.begin(9600); //Se inicializa la comunicación
  pinMode(led1,OUTPUT); //pin como salida
  pinMode(led2,OUTPUT); //pin como salida
  pinMode(rele,OUTPUT); //pin como salida
  digitalWrite(led1, HIGH); // Indicador de encendido
}

void loop() {
  
  Serial.println(analogRead(A5)); //Depuración
  Nivel=analogRead(A5);
  int i=0;
  if(Nivel>620){ //Tanque lleno 
    digitalWrite(rele,HIGH);//Encender bomba
    digitalWrite(led2,HIGH); //Bomba encendida
    for(i=1;i<=240;i++){
      Serial.print(i);
      Serial.print(" | \n");
      delay(1000);
      }
    digitalWrite(rele,LOW);//Apagar bomba
    digitalWrite(led2,LOW); //Bomba apagada
    Nivel=0;
    }

}
