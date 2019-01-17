/*void loopProceso() {
   if (pzas > 0){
    digitalWrite(focos, amarillo);
    // paso 0 : Evita el golpe frontal 
    digitalWrite(feedy2, LOW);
    delay(500);
    //paso 1 Extiende Piston feed hasta el frente
    digitalWrite(feedy2, HIGH);
    SenalA1 = digitalRead(A1);
    delay(Treb);
    while (SenalA1 == 0){                  //Mandamos al alimentador hasta el frente
       digitalWrite(feedy1, LOW);
       SenalA1 = digitalRead(A1);
       delay(Treb);
    }
    digitalWrite(feedy1, HIGH);
    //Paso 2: retrae piston hasta encontrar polin o señal A0(completamente retraido)
    SenalA0 = digitalRead(A0);
    delay(Treb);
    SenalM = digitalRead(master);
    delay(Treb); 
    while (SenalM == 0 && SenalA0 == 0){     //********** ESCANEAMOS PARA BUSCAR POLIN Y PONERLO EN POSICION ***********
      digitalWrite(feedy2, LOW);
      SenalA0 = digitalRead(A0);
      delay(Treb);
      SenalM = digitalRead(master);
      delay(Treb);              
    }
    digitalWrite(feedy2, HIGH);
    delay(10);
    // Paso 3: Si encontro polin, levanta guarda y atrapa polin
    if (SenalM == 1){
         digitalWrite(guarda, HIGH);
         delay(Tgua);
    // Paso 4: Extiende piston hasta el frente 
         SenalA1 = digitalRead(A1);
         delay(Treb);
         while (SenalA1 == 0){
            digitalWrite(gripper, LOW);
            delay(50);
            SenalD0 = digitalRead(D0);
            delay(Treb);
            if (SenalD0 == 1){
               digitalWrite(feedy1, LOW);
            }
            SenalA1 = digitalRead(A1);
            delay(Treb);
         }
         //*********  El polin esta en posicion ***********
         digitalWrite(feedy1, HIGH);
         delay(10);

    // Paso 5: Suelta polin    
         digitalWrite(guarda, HIGH);
         delay(10);
         digitalWrite(gripper, HIGH);
         delay(10);
    // Paso 6:  Retrae piston definido por la longitud de despunte
         digitalWrite(feedy2, LOW);
         delay(Tdes);                                     // Definimos longitud del DESPUNTE..................
         digitalWrite(feedy2, HIGH);
    // Paso 7: Atrapa polin
         digitalWrite(gripper, LOW);
         delay(Tgri);
    // Paso 8: Extiende piston hasta el frente (lo mantiene)
         SenalA1 = digitalRead(A1);
         delay(Treb);
         while (SenalA1 == 0){
           SenalD0 = digitalRead(D0);
           delay(Treb);
           if (SenalD0 == 1){
             digitalWrite(feedy1, LOW);
           }
           SenalA1 = digitalRead(A1);
           delay(Treb); 
         }
    // Paso 9: baja guarda 
         SenalD1 = digitalRead(D1);
         delay(Treb); 
         SenalA1 = digitalRead(A1);
         delay(Treb); 
         if (SenalA1 == 1 && SenalD0 == 1){
          digitalWrite(guarda, LOW);
          delay(Tgua);
    // Paso 10: sube disco de corte
          while (SenalD1 == 0){
            digitalWrite(corte, LOW);
            SenalD1 = digitalRead(D1);
            delay(Treb); 
          }
          digitalWrite(corte, HIGH);
         }
     } 
    /////////////////////////////////////////////////////////////////////////////////////// 
     if (SenalA0 == 1){
        loopcargarpolin();
     }
     //////////////////////////////////////////////////////////////////////////////////////
     while(contPiezas < pzas){                 //QQQQQQQQQQQ Inicia ciclo de piezas a cortar QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ 
          digitalWrite(focos, amarillo);
          SenalM = digitalRead(master);    
          delay(Treb); 
          if (SenalM == 1 && despunte == 0){                 // verificamos al Master
            loopalimentar();
          }
          else{
            loopcargarpolin();
          }
          SenalA1 = digitalRead(A1);
          delay(Treb);
          if (despunte == 0 && SenalM == 1){
            loopcortar();                     // Procedimiento para CORTAR
          }
          despunte = 0;
          SenalM = digitalRead(master);    
          delay(Treb); 
     }                                        //QQQQQQQQQQQQ Termina ciclo de piezas a cortar QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ  
     endTime = millis();
     Time = endTime-startTime; 
     pantalla3(contPiezas, Time);       //XXXXXXXXXXXXX PANTALLA DE FINAL DE PROCESO XXXXXXXXXXXXXXXXXXXXXXXX
     digitalWrite(feedy1,HIGH);
     digitalWrite(guarda, HIGH);                   //DESACTIVAR electrovalvula GUARDA ARRIBA
     digitalWrite(gripper, HIGH);                  //DESACTIVAR electrovalvula grippers Sin Apretar
     digitalWrite(corte, HIGH);                    //DESACTIVAR electrovalvula CILINDRO DE CORTE DESACTIVADO
     //digitalWrite(motoreductor, HIGH);             //Motor Apagado
     digitalWrite(auxiliar, HIGH);                 //DESACTIVAR electrovalvula CILINDRO AUX. DE MOTOREDUCTOR ACCIONADO
     digitalWrite(limpiador, HIGH);                //DESACTIVAR electrovalvula CILINDRO Limpiador retraida
     digitalWrite(focos, rojo);
     digitalWrite(feedy2, HIGH);                   //DESACTIVAR electrovalvula CARGAR MATERIAL
     digitalWrite(feedy2, LOW);                   //posicionamos el alimentador
     delay(3000);
     digitalWrite(feedy2, HIGH);                   //DESACTIVAR electrovalvula CARGAR MATERIAL   
     inicializar();
  }
}

void loopcortar(){                      //<<<<<<<<<<<<<< Procedimiento COTAR <<<<<<<<<<<<<<<<<<<<<<
  SenalA1 = digitalRead(A1);
  delay(Treb);
  SenalD1 = digitalRead(D1);
  delay(Treb); 
  SenalD0 = digitalRead(D0);
  delay(Treb); 
  if (SenalA1 == 1 && SenalD0 == 1){
// Paso 18: subir disco de corte
    while (SenalD1 == 0){
// Paso 17: bajo guarda
      digitalWrite(guarda, LOW);
      delay(100);
      digitalWrite(corte, LOW);
      SenalD1 = digitalRead(D1);
      delay(Treb); 
    }
    delay(100);
// Paso 19: bajar disco de corte 
    digitalWrite(corte, HIGH);
    contPiezas++;
    delay(10);
    lcd.setCursor(15,2);
    lcd.print(contPiezas);
    delay(10);
    SenalD1 = digitalRead(D1);
    delay(Treb);
    SenalA1 = digitalRead(A1);
    delay(Treb);
    SenalD0 = digitalRead(D0);
    delay(Treb);
  }  
}
void loopalimentar(){                  //<<<<<<<<<<<<<< Procedimiento ALIMENTAR <<<<<<<<<<<<<<<<<<<<<<
  digitalWrite(feedy1, HIGH);
  delay(Tfeed);
  digitalWrite(gripper, HIGH);
  delay(Tgri);
// Paso 13: retroceder distancia deseada
  SenalAp = digitalRead(Ap);
  delay(Treb);
  while (SenalAp != 0){
    digitalWrite(feedy2, LOW);
    delay(Tfeed);
    SenalAp = digitalRead(Ap);
    delay(Treb);
  }
  digitalWrite(feedy2, HIGH);
  delay(Tfeed);
// Paso 14: Levanta guarda (cambiar por paso 15)
  digitalWrite(guarda, HIGH);
  delay(Tgua);
// Paso 16: avansa hasta el frente  
  SenalA1 = digitalRead(A1);
  delay(Treb);
  while (SenalA1 == 0){
// Paso 15: atrapa polin
    digitalWrite(gripper, LOW);
    delay(50);
    SenalD0 = digitalRead(D0);
    delay(Treb);
    if (SenalD0 == 1){ // Condicion de seguridad
    digitalWrite(feedy1, LOW);
    }
    SenalA1 = digitalRead(A1);
    delay(Treb);
  } 
}

void loopcargarpolin(){               //<<<<<<<<<<<<<< Procedimiento CARGAR NUEVO POLIN <<<<<<<<<<<<<<<<<<<<<<
  despunte = 1;
  //delay(100);
  digitalWrite(gripper, HIGH);
  //delay(100);
  SenalA0 = digitalRead(A0);
  delay(Treb);
  digitalWrite(feedy1, HIGH);
  while (SenalA0 == 0){
    digitalWrite(feedy2, LOW);
    SenalA0 = digitalRead(A0);
    delay(Treb);
  }
  digitalWrite(feedy2, HIGH);
  SenalM = digitalRead(master);    
  delay(Treb);
  while (SenalM == 0){
    digitalWrite(auxiliar, LOW); 
    SenalM = digitalRead(master);    
    delay(Treb); 
  }
  digitalWrite(auxiliar, HIGH);
  SenalA1 = digitalRead(A1);
  delay(Treb);
  digitalWrite(feedy2, HIGH);
  digitalWrite(guarda, HIGH);
  digitalWrite(feedy1, LOW);                        //Ajustamos la posicion del polin, para llevarlo a despuntar
  delay(80);
  digitalWrite(feedy1, HIGH);
  SenalA1 = digitalRead(A1);
  delay(Treb);
  digitalWrite(gripper, LOW);
  while (SenalA1 == 0){ 
    SenalD0 = digitalRead(D0);
    delay(Treb);
    if (SenalD0 == 1){
    digitalWrite(feedy1, LOW);
    }
    SenalA1 = digitalRead(A1);
    delay(Treb); 
  }
  digitalWrite(feedy1, HIGH);
  SenalA1 = digitalRead(A1);
  delay(Treb);
  
  SenalD1 = digitalRead(D1);
  delay(Treb); 
  SenalA1 = digitalRead(A1);
  delay(Treb);
  SenalD0 = digitalRead(D0);
  delay(Treb); 
  if (SenalA1 == 1 && SenalD0 == 1){ 
    while (SenalD1 == 0){
      digitalWrite(guarda, LOW);
      delay(100);
      digitalWrite(corte, LOW);
      SenalD1 = digitalRead(D1);
      delay(Treb); 
    }
    delay(100);
    digitalWrite(corte, HIGH);
    delay(800);
    digitalWrite(guarda, HIGH);
    SenalD1 = digitalRead(D1);
    delay(Treb);
  }  
}
void inicializar(){
  //tecla = 'X';
  pzas = 0;
  contPiezas = 0;
  pantalla = 1;
  medicion = 0; 
  despunte = 0;
//  duration = 0;
//  distance = 0;
  SenalM = 0;
  SenalA0 = 0;
  SenalAp = 0;
  SenalA1 = 0;
  SenalD0 = 0;
  SenalD1 = 0;
}
*/


 
