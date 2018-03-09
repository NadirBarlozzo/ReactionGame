#include <Wire.h>

#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <Ethernet2.h>
#include <SPI.h>

const byte RECV_PIN = 50;
IRrecv irrecv(RECV_PIN);
decode_results results;
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


/**
   Array contenente il vecchio stato dei bottoni.
*/
boolean lastButtonsState[12];

/**
   Array contenente lo stato attuale dei bottoni.
*/
boolean currentButtonsState[12];


/**
   Array contenente i pins dei bottoni.
*/
int buttonPins[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44};
/**
   Array contenente i pins dei led
*/
int ledPins[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};

float scores[] = {0, 0};


int buzzerPin = 6;
int buzzerPin2 = 7;
int delayValue = 20;


long arraySelected[] = {0, 0};
int modeSelected;


int lastNumber = -1;
int currentNumber = -1;
float timer = 0;
int dimensions = 0;
int score = 0;

/**
   Il numero di millisecondi mancanti alla fine del gioco.
*/
long countdown = 0;


int countdownLoop = 0;


double timerGame = 0;
boolean corner;
boolean pressed = false;
float startTime;
float elapsedTime;
float timeReflection = 1000;
int shot = 100;
boolean error = false;


int hz = 0;

int nMod = 15;

//variabili per collegare Arduino a DB SQL
byte mac[] = {0x90, 0xA2, 0xDA, 0x11, 0x1D, 0x55};
IPAddress ip(192, 168, 5, 16);
IPAddress server(192, 168, 5, 17);
EthernetClient client;
int conn;

void setup() {
  //Funzionamento dei pin
  Wire.begin();
  // inizializzazione dell'oggetto lcd_I2C
  lcd.begin(20, 4);
  lcd.clear();
  //accensione retro illuminazione
  lcd.backlight();
  randomSeed(analogRead(0));
  pinMode(buzzerPin, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
  {
    //Assegno i pin ai relativi bottoni e led.
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);

    //Riempio di false i due array.
    lastButtonsState[i] = false;
    currentButtonsState[i] = false;
  }
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  conn = client.connect(server, 3305);
}

void loop()
{
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    digitalWrite(ledPins[i], LOW);
  }
  lcd.clear();
  digitalWrite(ledPins[11], HIGH);
  while (digitalRead(buttonPins[11])) {
    lcd.setCursor(0, 0);
    lcd.print("Premi @ per ");
    lcd.setCursor(0, 1);
    lcd.print("scegliere");
    lcd.setCursor(0, 2);
    lcd.print("la modalita");
  }
  digitalWrite(ledPins[11], LOW);
  delay(100);
  modeSelected = 0;
  arraySelected[0] = 0;
  arraySelected[1] = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mod disponibili:");
  lcd.setCursor(0, 1);
  lcd.print("1 - 15");
  lcd.setCursor(0, 2);
  lcd.print("Premi i bottoni");
  lcd.setCursor(0, 3);
  lcd.print("per scegliere");
  delay(200);
  do {
    for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++) {
      currentButtonsState[i] = debounce(i);
      if (currentButtonsState[i] == true && lastButtonsState[i] == false && i < 10) {
        arraySelected[0] = arraySelected[1];
        arraySelected[1] = i;
        modeSelected = arraySelected[1] + arraySelected[0] * 10;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mod disponibili:");
        lcd.setCursor(0, 1);
        lcd.print("1 - 15");
        lcd.setCursor(0, 2);
        lcd.print("modalita");
        lcd.setCursor(9, 2);
        lcd.print(modeSelected);
        if  (modeSelected < 1 || modeSelected > nMod) {
          lcd.setCursor(0, 4);
          lcd.print("mod non valida");
        }
      }
      lastButtonsState[i] = currentButtonsState[i];
    }
  } while (!currentButtonsState[11] || !(modeSelected > 0 && modeSelected <= nMod));

  boolean led = true;
  for (int i = 0; i < 6; i++) {

    for (int j = 0; j < sizeof(buttonPins) / sizeof(buttonPins[0]); j++)
    {
      digitalWrite(ledPins[j], led);
    }
    delay(500);
    led = !led;
    if (i % 2 == 0) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print(3 - i / 2);
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(buzzerPin2, HIGH);
      delay(delayValue);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(buzzerPin2, LOW);
    }
  }
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(buzzerPin2, HIGH);
  delay(delayValue * 2);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(buzzerPin2, LOW);
  lcd.clear();
  switch (modeSelected) {

    case 1:
      firstModGroup(10, 60000, false);
      break;

    case 2:
      firstModGroup(10, 300000, false);
      break;

    case 3:
      firstModGroup(6, 30000, false);
      break;

    case 4:
      firstModGroup(6, 60000, false);
      break;

    case 5:
      firstModGroup(6, 180000, false);

      break;

    case 6:
      firstModGroup(10, 30000, true);
      break;

    case 7:
      secondModGroup(10, 50);

      break;

    case 8:
      secondModGroup(6, 25);
      break;

    case 9:
      secondModGroup(6, 50);
      break;

    case 10:
      thirdModGroup(4, 100, true);
      break;

    case 11:
      thirdModGroup(4, 25, true);
      break;

    case 12:
      thirdModGroup(4, 50, true);
      break;

    case 13:
      thirdModGroup(6, 25, false);
      break;

    case 14:
      thirdModGroup(6, 50, false);
      break;

    case 15:
      thirdModGroup(10, 100, false);
      break;
  }
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(buzzerPin2, HIGH);
  delay(25 * delayValue);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(buzzerPin2, LOW);
  scores[0] = 0;
  scores[1] = 0;
  modeSelected = 0;
  delay(5000);
}

