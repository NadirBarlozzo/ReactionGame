//#include <LCD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//primi dati sono inizializzazione delle porte A4 e A5
//gli altri si riferiscono alle righe e alle colonne
//altri codici per lcd 0x20, 0x27
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);
int b = 0;
int a = 30;

void setup() {
  Wire.begin();
  // inizializzazione dell'oggetto lcd_I2C
  lcd.begin(20,4);
  lcd.clear();
  //accensione retro illuminazione 
  lcd.backlight();
}

void loop(){
  lcd.clear();
  
  testoBase();
  
  lcd.setCursor(0,1);
  lcd.print(a);

  lcd.setCursor(0,3);
  lcd.print(b);
  
  delay(1000);
  a--;
  b++;

  //testoFinale();
}

void testoBase(){
  lcd.setCursor(0,0);
  lcd.print("Tempo: ");

  lcd.setCursor(0,2);
  lcd.print("Punti: ");
}

void testoFinale(){
  if(a == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Risultato: ");

    lcd.setCursor(0,1);
    lcd.print(b);
    exit(0);
  }
}
