

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5


#define ledPIN 13


// para leer los botones
int read_LCD_buttons() { 
  adc_key_in = analogRead(0);      // Leemos A0
  
  // Mis botones dan:  0, 145, 329,507,743
  // Y ahora los comparamos con un margen comodo

  Serial.println(adc_key_in);
  
  if (adc_key_in > 900) return btnNONE;     // Ningun boton pulsado
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 110)  return btnUP;
  if (adc_key_in < 300)  return btnDOWN;
  if (adc_key_in < 450)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;

  return btnNONE;  // Por si todo falla
}




void setup() {

  Serial.begin(9600);
  pinMode(ledPIN , OUTPUT);  //definir pin como salida

  
  lcd.begin(16, 2);              // Inicializar el LCD
  lcd.setCursor(0, 0);
  lcd.print("Prometec.net");     // print a simple message
}

void loop() {
  lcd.setCursor(9, 1);             // Cursor a linea 2, posicion 9
  lcd.print(millis() / 1000);      // Imprime segundos
  lcd.setCursor(0, 1);             // Cursor a linea 2, posicion 1

  lcd_key = read_LCD_buttons();
  if ( lcd_key == btnRIGHT)
    lcd.print("RIGHT ");
  else if ( lcd_key == btnLEFT ) {
    lcd.print("LEFT   ");
     digitalWrite(ledPIN , LOW);   // poner el Pin en LOW
  }
  else if ( lcd_key == btnUP)
    lcd.print("UP    ");
  else if ( lcd_key == btnDOWN)
    lcd.print("DOWN  ");
  else if ( lcd_key == btnSELECT) {
    lcd.print("SELECT");
    digitalWrite(ledPIN , HIGH);   // poner el Pin en HIGH
  }
  else if ( lcd_key == btnNONE)
    lcd.print("NONE  ");

}
