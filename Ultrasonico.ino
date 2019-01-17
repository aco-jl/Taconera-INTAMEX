/*
void ultrasonoco0() { 
  for(int medicion=1; medicion<=300; medicion++){
    digitalWrite(trigPin, LOW);                                       // medimos la distancia o el largo a cortar
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29;
    if (distance >= 400 || distance <= 2){
      lcd.setCursor(9,3);
      lcd.print(" ** ERROR **");
    }
    else {
      largo = 25.92 - distance;
      lcd.setCursor(11,3);
      lcd.print(largo);
      lcd.setCursor(17,3);
      lcd.print("cm");             
                  
      for (int i=1; i<=800; i++){
         char tecla = teclado.getKey();
        //Serial.print(i);
        if (tecla != NO_KEY){
          medicion = 500;
          i = 1800;                    
        }                  
      }        
    }
  }
}

void ultrasonico1() {
  // Esperar 1 segundo entre mediciones
  delay(1000);
  // Obtener medicion de tiempo de viaje del sonido y guardar en variable uS
  int uS = sonar.ping_median();
  // Imprimir la distancia medida a la consola serial
  Serial.print("Distancia: ");
  // Calcular la distancia con base en una constante
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
}

float ultrasonico2(){
  digitalWrite(9,LOW); //Por cuestión de estabilización del sensor
  delayMicroseconds(5);
  digitalWrite(9, HIGH); // envío del pulso ultrasónico//
  delayMicroseconds(10);
  float tiempo=pulseIn(8, HIGH); // Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante//
  float distancia= int(0.017*tiempo); //fórmula para calcular la distancia obteniendo un valor entero//
  //Monitorización en centímetros por el monitor serial//
  return distancia; 
  //Serial.println("Distancia ");
  //Serial.println(distancia);
  //Serial.println(" cm");
  //delay(1000);
}

float ultrasonicoaux(){
  float distancia = 5;
  return distancia; 
}
*/


