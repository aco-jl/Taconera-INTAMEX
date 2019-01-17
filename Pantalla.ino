void pantalla0(){
  lcd.backlight();                              // iniciamos el fondo retroiluminado
  lcd.init();                                   // inicializamos lcd
  lcd.clear();                                  //Limpiamos Pantalla
  lcd.print("Favor de introducir");
  lcd.setCursor(0,1);
  lcd.print("cantidad de Piezas");
  lcd.setCursor(0,2);
  lcd.print("Que quieres cortar:");
  lcd.setCursor(0,3);
  lcd.print("Despues Presiona B");
}

void pantalla1(){
  lcd.clear();
  lcd.print("*** PROGRAMANDO ***");
  lcd.setCursor(0,1);
  lcd.print("Cuantas Piezas");
  lcd.setCursor(0,2);
  lcd.print("vas a cortar:");
}

void pantalla2(int pzas ,int contPiezas){
  lcd.clear();
  lcd.print("**** PROCESANDO ****");
  lcd.setCursor(0,1);
  lcd.print("Pzas a cortar:");
  lcd.setCursor(15,1);
  lcd.print(pzas);
  lcd.setCursor(0,2);
  lcd.print("Pzas cortadas:");
  lcd.setCursor(15,2);
  lcd.print(contPiezas);
  lcd.setCursor(0,3);
  lcd.print("Ti Trans: 0:00  min.");
}

void pantalla3(int contPiezas, unsigned long Time){
  unsigned long mtos = Time/1000; //milisegundos a segundos
  unsigned long minT = Time/60000; //segundos a minutos 
  unsigned long segT = mtos-(minT*60); //funcion que optine segundos del 0 al 60;
  
  lcd.clear();                             //XXXXXXXXXXXXX PANTALLA DE FINAL DE PROCESO XXXXXXXXXXXXXXXXXXXXXXXX
  lcd.print("*** TERMINADO ***");
  lcd.setCursor(0,1);
  lcd.print("Piezas Cortadas:");
  lcd.setCursor(16,1);
  lcd.print(contPiezas);
  lcd.setCursor(0,2);
  lcd.print("Duracion: ");
  //lcd.setCursor(10,2);
  lcd.print(minT);
  lcd.print(":");
  if (segT < 10){
    lcd.print("0");
  }
  lcd.print(segT);
  lcd.setCursor(16,2);
  lcd.print("min.");
}

void show(String y) {
  lcd.setCursor(15,2);
  lcd.print("    ");
  //int numLength = y.length();
  //lcd.setCursor(15-numLength,1);
  lcd.setCursor(15,2);
  lcd.print(y); 
}

void showcont(int y, unsigned long Time) {
  unsigned long mtos = Time/1000; //milisegundos a segundos
  unsigned long minT = Time/60000; //segundos a minutos 
  unsigned long segT = mtos-(minT*60); //funcion que optine segundos del 0 al 60;
  //lcd.setCursor(15,2);
  //lcd.print("    ");
  //int numLength = y.length();
  //lcd.setCursor(15-numLength,1);
  lcd.setCursor(15,2);
  lcd.print(y); 
  lcd.setCursor(10,3);
  lcd.print(minT);
  lcd.print(":");
  if (segT < 10){
    lcd.print("0");
  }
  lcd.print(segT);
  lcd.setCursor(16,3);
  lcd.print("min.");
}

/*
void checknumber(int x){
num1 = num1 + key;
int numLength = num1.length();
lcd.setCursor(15-numLength,1);
lcd.print(num1); 
*/
