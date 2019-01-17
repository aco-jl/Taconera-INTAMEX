void customIO (){ 
  //DEFINIMOS PINES DEL SENSOR DE DISTANCIA
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  
  // Relay Output pin directions 
  pinMode(focos, OUTPUT); 
  pinMode(motor, OUTPUT); 
  pinMode(feedy1, OUTPUT); 
  pinMode(feedy2, OUTPUT); 
  pinMode(guarda, OUTPUT); 
  pinMode(gripper, OUTPUT); 
  pinMode(corte, OUTPUT);
  pinMode(auxiliar, OUTPUT);
  pinMode(limpiador, OUTPUT);

  // Sensors Input pin directions 
  pinMode(D1, INPUT); 
  pinMode(D0, INPUT); 
  pinMode(A1, INPUT); 
  pinMode(Ap, INPUT); 
  pinMode(A0, INPUT); 
  pinMode(master, INPUT);
}
