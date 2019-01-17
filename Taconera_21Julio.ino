#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);  // Inicializamos la pantalla 4x20 Caracteres

const byte ROWS = 4;  // Cuatro filas
const byte COLS = 4;  // Cuatro Columnas
char keys[ROWS][COLS]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS]={23, 25, 27, 29};  //Arduino Mega
byte colPins[COLS]={31, 33, 35, 37};
Keypad teclado = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// **** Pines I/O **** //
// Actuadores
const int focos = 36;      // Relay de foco ROJO(1) y AMARILLO(0)
const int motor = 38;      // Relay de Motorreductor                                          (K8)
const int feedy1 = 40;     // Pin de electroválvula de alimentar material    (Cilindro A)(Y1) (K1) 
const int feedy2 = 42;     // Pin de electroválvula de cargar material       (Cilindro A)(Y2) (K2)
const int guarda = 44;     // Pin de electroválvula de la guarda             (Cilindro B)(Y3) (K3)
const int gripper = 46;    // Pin de electroválvula del Sujetador o grippers (Cilindro C)(Y5) (K4)
const int corte = 48;      // Pin de electroválvula de CORTE                 (Cilindro D)(Y7) (K5)
const int auxiliar = 50;   // Pin de electroválvula de Polin                 (Cilindro E)(Y9) (K6)
const int limpiador = 52;  // Pin de electroválvula de Limpiador             (Cilindro F)(Y10)(K7)
// Sensores
const int D1 = 41;         // sensor de DISCO Acciodado al maximo
const int D0 = 43;         // sensor de DISCO Acciodado al minimo
#define A1 45              // sensor de FEED Acciodado al maximo
//const int A1 = 45;
const int Ap = 47;         // sensor de POSICION DE CORTE TACON
#define A0 49              // sensor de FEED Retraido al minimo
//const int A0 = 49;
const int master = 51;     // sensor MASTER

// **** Tiempos ms **** //
const int Tfeed = 10;     // Delay Alimentador
const int Tgri = 50;      // Delay Grippper
const int Tgua = 500;     // Delay Guarda
const int Tdes = 165;     // Definimos longitud del DESPUNTE (Cuando hay Nuevo Polin)
const int Tdes2 = 5600;   // Definimos longitud del DESPUNTE (Cuando encuentra Polin)
const int Treb = 10;      // Delay rebote lectura sensores (debounce)

const int rojo = 1, amarillo = 0;
const int alto = 0, bajo = 1;
const int on = 0, off = 1;

// **** Variables Globales**** //
// Variables para retener el numero introducido por el teclado
volatile int numero[4] = {99, 99, 99, 99};
volatile int fullnumber = 0;

unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long Time = 0;

int enableTeclado = 1;  // Desabilita lectura de treclado mientras trabaja   
int nuevo = 0;          // Para dedicion de despunte 
int pzas = 0;           // Cantidad de piezas a cortar
int contPiezas = 0;     // Contador de piezas cortadas
//int pantalla, medicion, despunte;
//float duration, largo, distance;
int SenalM, SenalA0, SenalAp, SenalA1, SenalD0, SenalD1;
int despunte = 0;

//const int intPin = 2; // Boton de emergencia
//volatile boolean emergency = false;
//volatile boolean e_stop = false;     //ISR variable.

void setup() {
  //pinMode(intPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(intPin), Emergencia, FALLING);//Fuciona
  //attachInterrupt(0, Emergencia, FALLING);//Fuciona

  customIO();
  digitalWrite(focos, rojo);
  digitalWrite(motor, HIGH); 
  digitalWrite(feedy1, HIGH); 
  digitalWrite(feedy2, HIGH); 
  digitalWrite(guarda, HIGH); 
  digitalWrite(gripper, HIGH); 
  digitalWrite(corte, HIGH); 
  digitalWrite(auxiliar, HIGH);
  digitalWrite(limpiador, HIGH);
  pantalla0();
  delay(2000);
  pantalla1();
}

void loop() {
  //if (emergency == false){  
    if (enableTeclado == 1) {
      char tecla = teclado.getKey();
      if (tecla != NO_KEY){  // Si algun boton fue precionado checar que tecla fue
        switch (tecla) {
          case '1':
            checknumber(1);
          break; 
          case '2':
            checknumber(2);
          break;
          case '3':
            checknumber(3);
          break;
          case '4':
            checknumber(4);
          break;
          case '5':
            checknumber(5);
          break;
          case '6':
            checknumber(6);
          break;
          case '7':
            checknumber(7);
          break;
          case '8':
            checknumber(8);
          break;
          case '9':
            checknumber(9);
          break;
          case '0':
            checknumber(0);
          break;
          case '*':
            deletenumber();
          break;
          case '#':
            //
          break;
          case 'A':
            resetnumber();
            pantalla1();
          break;
          case 'B':
            calcnumber();
            if (0 < fullnumber < 10000){ // Verifica que las pzas a cortar sea mayor a cero
              enableTeclado = 0;
              startTime = millis();
              pzas = fullnumber;
              pantalla2(pzas, contPiezas);
            }
            else{
              lcd.setCursor(0,3);
              lcd.print("Cantidad Incorrecta ");
              delay(1000);
              lcd.setCursor(0,3);
              lcd.print("Vuelve a intentar   ");
            }
          break;
          case 'C':
            //
          break;
          case 'D':
            //calculatedistance();
          break;
        }
      }
    }
    //else {
      loopProceso2();
    //}
  /*}
  else{
    lcd.clear();
    lcd.print("***EMERGENCIA***");
    lcd.setCursor(0,2);
    lcd.print(" Presiona RESET ");
    lcd.setCursor(0,3);
    lcd.print(" para continuar ");
  } */  
}
/*
void Emergencia(){                         //########################## CILCO DE PARO DE EMERGENCIA *************************************
  //while(true){
    digitalWrite(focos, rojo);
    detachInterrupt(0);
    
    digitalWrite(feedy1,HIGH);
    digitalWrite(feedy2, HIGH);                   //DESACTIVAR electrovalvula CARGAR MATERIAL
    digitalWrite(guarda, HIGH);                   //DESACTIVAR electrovalvula GUARDA ARRIBA
    digitalWrite(gripper, HIGH);                  //DESACTIVAR electrovalvula grippers Sin Apretar
    digitalWrite(corte, HIGH);                    //DESACTIVAR electrovalvula CILINDRO DE CORTE DESACTIVADO
    //digitalWrite(motoreductor, HIGH);             //Motor Apagado
    digitalWrite(auxiliar, HIGH);                 //DESACTIVAR electrovalvula CILINDRO AUX. DE MOTOREDUCTOR ACCIONADO
    digitalWrite(limpiador, HIGH);                //DESACTIVAR electrovalvula CILINDRO Limpiador retraida
    digitalWrite(focos, rojo);
    
    emergency = true;
    
    e_stop = !e_stop;

    //lcd.clear();
    //lcd.print("***EMERGENCIA***");
  //}
}*/
