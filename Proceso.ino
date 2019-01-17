void loopProceso2() {
  if (pzas > 0){
    digitalWrite(focos, amarillo);
    // Paso 1: Evita el golpe frontal
    digitalWrite(feedy2, LOW);
    delay(500);
    digitalWrite(feedy2, HIGH);
    // Paso 2: Mandamos al alimentador hasta el frente
    SenalA1 = digitalRead(A1);
    delay(Treb);
    while (SenalA1 == 0){
      digitalWrite(feedy1, LOW);
      SenalA1 = digitalRead(A1);
      delay(Treb);
    }
    digitalWrite(feedy1, HIGH); 
    // Paso 3: ESCANEAMOS PARA BUSCAR POLIN Y PONERLO EN POSICION
    SenalA0 = digitalRead(A0);
    delay(Treb);
    SenalM = digitalRead(master);
    delay(Treb); 
    while (SenalM == 0 && SenalA0 == 0){
      digitalWrite(feedy2, LOW);
      SenalA0 = digitalRead(A0);
      delay(Treb);
      SenalM = digitalRead(master);
      delay(Treb);              
    }
    digitalWrite(feedy2, HIGH);
    // Pasos 4, 5: Si no hay Polin
    if (SenalA0 == 1){
      loopcargarpolin2();
    }
    // Pasos 6, 14: Si hay Polin
    if (SenalM == 1){
      loopdespunte2();
    }
    SenalM = digitalRead(master);
      delay(Treb);
    // ********Inicia ciclo de piezas a cortar********* //
    while(contPiezas < pzas){
      digitalWrite(focos, amarillo);
      SenalM = digitalRead(master);
      delay(Treb);
      if (SenalM == 1){
    // Pasos: 15, 22
        loopalimentar2();
    // Pasos: 23, 25
        SenalA1 = digitalRead(A1);
        delay(Treb);
        SenalM = digitalRead(master);
        delay(Treb);
        if (SenalM==1 && SenalA1==1 && despunte==0){
          loopcortar2();           // Procedimiento para CORTAR
        }  
      }
      else{
        loopcargarpolin2();
        loopdespunte2();
      }
    }                               //QQQQQQQQQQQQ Termina ciclo de piezas a cortar QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ  
    endTime = millis();
    Time = endTime-startTime; 
    pantalla3(contPiezas, Time);    //XXXXXXXXXXXXX PANTALLA DE FINAL DE PROCESO XXXXXXXXXXXXXXXXXXXXXXXX
    
    digitalWrite(feedy1,HIGH);
    digitalWrite(guarda, HIGH);     //DESACTIVAR electrovalvula GUARDA ARRIBA
    digitalWrite(gripper, HIGH);    //DESACTIVAR electrovalvula grippers Sin Apretar
    digitalWrite(corte, HIGH);      //DESACTIVAR electrovalvula CILINDRO DE CORTE DESACTIVADO
    digitalWrite(motor, HIGH);      //Motor Apagado
    digitalWrite(auxiliar, HIGH);   //DESACTIVAR electrovalvula CILINDRO AUX. DE MOTOREDUCTOR ACCIONADO
    digitalWrite(limpiador, HIGH);  //DESACTIVAR electrovalvula CILINDRO Limpiador retraida
    digitalWrite(focos, rojo);      //FOCO ROJO
    digitalWrite(feedy2, HIGH);     //DESACTIVAR electrovalvula CARGAR MATERIAL
    digitalWrite(feedy2, LOW);      //posicionamos el alimentador
    delay(3000);
    digitalWrite(feedy2, HIGH);     //DESACTIVAR electrovalvula CARGAR MATERIAL
    inicializar2();
  }
}
void loopdespunte2(){
  digitalWrite(guarda, HIGH);
  delay(Tgua);
  // Paso 7: El polin esta en posicion
  SenalA1 = digitalRead(A1);
  delay(Treb);
  while (SenalA1 == 0){
  // Paso 6: Atrapa polin
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
  digitalWrite(feedy1, HIGH);
  // Paso 8: Suelta Polin
  digitalWrite(guarda, HIGH);
  delay(10);
  digitalWrite(gripper, HIGH);
  delay(10);
  // Paso 9: Retrae piston definido por un delay de despunte
  if (nuevo == 0){
    digitalWrite(feedy2, LOW);
    delay(Tdes2);                 // Definimos longitud del DESPUNTE (Cuando encuentra Polin)
    digitalWrite(feedy2, HIGH);
    nuevo = 0;
  }
  else{
    //digitalWrite(feedy2, LOW);
    //delay(Tdes);                // Definimos longitud del DESPUNTE (Cuando hay Nuevo Polin)
    //digitalWrite(feedy2, HIGH);
    //nuevo = 0;
  }
  // Paso 10:
  digitalWrite(gripper, LOW);
  delay(5);
  // Paso 11: Extiende piston hasta el frente (lo mantiene)
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
  // Paso 12: Baja Guarda
  SenalD1 = digitalRead(D1);
  delay(Treb); 
  SenalA1 = digitalRead(A1);
  delay(Treb); 
  if (SenalA1 == 1 && SenalD0 == 1){
    digitalWrite(guarda, LOW);
    delay(Tgua);
  // Paso 13: Sube disco de corte
    while (SenalD1 == 0){
      digitalWrite(corte, LOW);
      SenalD1 = digitalRead(D1);
      delay(Treb); 
    }
  }
  // Paso 14: Baja disco de corte
  SenalD0 = digitalRead(D0);
  delay(Treb);
  while (SenalD0 == 0){
    digitalWrite(corte, HIGH);
    SenalD0 = digitalRead(D0);
    delay(Treb); 
  }
  digitalWrite(feedy1, HIGH); //Permite retraccion
}

void loopcortar2(){             //<<<<<<<<<<<<<< Procedimiento COTAR <<<<<<<<<<<<<<<<<<<<<<
  SenalA1 = digitalRead(A1);
  delay(Treb);
  SenalD1 = digitalRead(D1);
  delay(Treb); 
  SenalD0 = digitalRead(D0);
  delay(Treb); 
  if (SenalA1 == 1 && SenalD0 == 1){
// Paso 24: subir disco de corte
    while (SenalD1 == 0){
// Paso 23: bajo guarda
      digitalWrite(guarda, LOW);
      delay(100);
      digitalWrite(corte, LOW);
      SenalD1 = digitalRead(D1);
      delay(Treb); 
    }
    delay(100);
// Paso 25: bajar disco de corte
    SenalD0 = digitalRead(D0);
    delay(Treb);
    while (SenalD0 == 0){
      digitalWrite(corte, HIGH);
      SenalD0 = digitalRead(D0);
      delay(Treb); 
    }
/////////////////////////////////////////////////////////////////////////////////
    contPiezas++;
    delay(10);
    
    endTime = millis();
    Time = endTime-startTime;

    unsigned long mtos = Time/1000; //milisegundos a segundos
    unsigned long minT = Time/60000; //segundos a minutos 
    unsigned long segT = mtos-(minT*60); //funcion que optine segundos del 0 al 60;

    lcd.setCursor(15,2);
    lcd.print(contPiezas); 
    lcd.setCursor(10,3);
    lcd.print(minT);
    lcd.print(":");
    if (segT < 10){
      lcd.print("0");
    }
    lcd.print(segT);
    lcd.setCursor(16,3);
    lcd.print("min.");
//////////////////////////////////////////////////////////////////////////////
    delay(10);
    SenalD1 = digitalRead(D1);
    delay(Treb);
    SenalA1 = digitalRead(A1);
    delay(Treb);
    SenalD0 = digitalRead(D0);
    delay(Treb);
  }  
}
void loopalimentar2(){      //<<<<<<<<<<<<<< Procedimiento ALIMENTAR <<<<<<<<<<<<<<<<<<<<<<
  // Condiciones
  digitalWrite(feedy1, HIGH);
  delay(Tfeed);
  // Paso 15: Liberar Polin
  digitalWrite(gripper, HIGH);
  delay(Tgri);
  // Paso 16: Retroceder distancia deseada
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
  // Seguridad: Verificamos si hay material.
  SenalM = digitalRead(master);
  delay(Treb);
  if (SenalM == 0){
  // Pasos: 17, 19.
    loopcargarpolin2();
    loopdespunte2();
    despunte = 1; // Bandera padar salto de programa---------------------------------------
  }
  else {
    // Paso 20: Levanta guarda (cambiar por paso 15)
    digitalWrite(guarda, HIGH);
    delay(Tgua);
    // Paso 22: avansa hasta el frente  
    SenalA1 = digitalRead(A1);
    delay(Treb);
    while (SenalA1 == 0){
    // Paso 21: atrapa polin
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
    despunte = 0; // Bandera padar salto de programa---------------------------------------
  } 
}

void loopcargarpolin2(){               //<<<<<<<<<<<<<< Procedimiento CARGAR NUEVO POLIN <<<<<<<<<<<<<<<<<<<<<<
  // Codiciones: Polin suelto, Alimentadir retrocede
  digitalWrite(gripper, HIGH);
  digitalWrite(feedy1, HIGH);
 
  SenalM = digitalRead(master);
  delay(Treb);
  if (SenalM == 0){
  // Paso 3: ESCANEAMOS PARA BUSCAR POLIN Y PONERLO EN POSICION
    SenalA0 = digitalRead(A0);
    delay(Treb);
    SenalM = digitalRead(master);
    delay(Treb); 
    while (SenalM == 0 && SenalA0 == 0){
      digitalWrite(feedy2, LOW);
      SenalA0 = digitalRead(A0);
      delay(Treb);
      SenalM = digitalRead(master);
      delay(Treb);              
    }
    digitalWrite(feedy2, HIGH);
  }

  if (SenalM == 0 && SenalA0 == 1){
  // Paso 4:
    SenalM = digitalRead(master);    
    delay(Treb);
    while (SenalM == 0){
      digitalWrite(auxiliar, LOW);
      digitalWrite(motor, LOW); 
      SenalM = digitalRead(master);    
      delay(Treb); 
    }
    // Paso 5:
    digitalWrite(auxiliar, HIGH);
    digitalWrite(motor, HIGH);
    digitalWrite(feedy1, LOW);
    delay(Tdes);                 // Delay despunte cuando carga nuevo polin. 
    digitalWrite(gripper, LOW);
    nuevo = 1;
  }
}

void inicializar2(){
//  tecla = 'X';
//  pantalla = 1;
//  medicion = 0; 
//  despunte = 0;
//  duration = 0;
//  distance = 0;
  pzas = 0;
  contPiezas = 0;
  enableTeclado = 1;
  nuevo = 0;
  despunte = 0;
  SenalM = 0;
  SenalA0 = 0;
  SenalAp = 0;
  SenalA1 = 0;
  SenalD0 = 0;
  SenalD1 = 0;
}



 
