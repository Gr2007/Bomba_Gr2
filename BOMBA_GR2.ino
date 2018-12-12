/*
 * Programa para control de bomba
 * Granados Villeda Johan Raciel
 * Versión 1.5
*/


//CONSTANTES
const long intervalo = 3000;  //Intervalo de tiempo de la bomba
const int led1 = 2; //LED de control
const int rele = 5;// Relevador

//VARIABLES GLOBALES
unsigned long tiempo1 = 0; //Para millis, sustitucion de ciclo for con delays      
bool estado = true; //para definir estado de la bomba. TRUE = apagado, FALSE = encendido. 
int Nivel = 0; //Para lectura Analogica

void setup() {
  Serial.begin(9600); //Se inicializa la comunicación
  pinMode(led1,OUTPUT); //pin como salida
  pinMode(rele,OUTPUT); //pin como salida
}

void loop() {

  if (estado) //BOMBA APAGADA
  {
    Serial.println(analogRead(A2)); // Depuración, revisión de estado del nivel en Serial
    Nivel = analogRead(A2); // Asignación del nivel
   
    if(Nivel > 500) //Control de nivel
      encender(); // FUNCION DE ENCENDIDO DE BOMBA
  }

  if(!estado)//BOMBA ENCENDIDA
  {
    if(millis() > (tiempo1 + intervalo)) // Para el tiempo 
      apagar(); // FUNCION DE APAGADO DE BOMBA

    if(tiempo1 !=0) // DEPURACION DEL TIEMPO 
      Serial.println(millis() - tiempo1); // tiempo entre encendio y apagado
    
  }
}

void encender() 
{
  tiempo1 = millis(); // INICIO DEL CONTEO 
  digitalWrite(rele,HIGH);// Encender bomba
  digitalWrite(led1,HIGH); // Bomba encendida
  estado = false; // Para control de la bomba, revisar constantes
}

void apagar()
{
  tiempo1 = 0; // reiniciar contador
  digitalWrite(rele,LOW);// Apagar bomba
  digitalWrite(led1,LOW); // Bomba apagada
  estado = true; // para control de la bomba, revisar constantes
}
