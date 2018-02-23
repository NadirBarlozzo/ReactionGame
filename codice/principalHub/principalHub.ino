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


const byte RECV_PIN = 50;
IRrecv irrecv(RECV_PIN);
decode_results results;
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

long arraySelected[2];
int arrayFinal[2];
long val;
int modSelected;

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

int buzzerPin = 7;
int buzzerPin2 = 6;
int delayValue = 20;

int lastNumber = -1;
int currentNumber = -1;
float timer = 0;
int dimensions = 0;
int score = 0;

int ledPins[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};

long buttons[] = {16738455, 16724175, 16718055, 16743045, 16716015, 16726215, 16734885, 16728765, 16730805, 16732845, 16748655};

int scores[] = {0, 0};

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
  irrecv.enableIRIn();
}

boolean isValid() {
  for (int i = 0; i < (sizeof(buttons) / sizeof(buttons[0])) - 2; i++) {
    if (val == buttons[i]) {
      return true;
    }
  }
  return false;
}

void loop()
{
  if (irrecv.decode(&results))
  {
    val = results.value;
    if (val == buttons[10])
    {
      modSelected = 0;
      arraySelected[0] = 0;
      arraySelected[1] = 0;
      Serial.println("Premuto +");
      while (true)
      {
        if (irrecv.decode(&results))
        {
          //Serial.println(results.value);
          val = results.value;
          if (isValid())
          {
            arraySelected[0] = arraySelected[1];
            arraySelected[1] = val;
            delay(1);
            irrecv.resume();
            convertValueToArray();
            modSelected = convertArrayToNumber();
            lcd.clear();

            lcd.setCursor(0, 0);
            lcd.print("Modalità: ");

            lcd.setCursor(0, 1);
            lcd.print(modSelected);

            if (val == buttons[10]) {
              break;
            }
          }
          irrecv.resume();
        }
        irrecv.resume();
      }
    }
  }

  if (modSelected != NULL && modSelected < 24 && modSelected > 0)
  {
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
    switch (modSelected) {

      case 1:
        firstModGroup(10, 60000, false);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 2:
        firstModGroup(10, 300000, false);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 3:
        thirdModGroup(2, true, 2);
        secondModGroup(10, 50);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 4:

        break;

      case 5:

        break;

      case 6:

        break;

      case 7:

        break;

      case 8:
        firstModGroup(10, 30000, true);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 9:

        break;

      case 10:

        break;

      case 11:

        break;

      case 12:

        break;

      case 13:

        break;

      case 14:

        break;

      case 15:
        firstModGroup(6, 30000, false);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 16:
        firstModGroup(6, 60000, false);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 17:
        secondModGroup(6, 25);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 18:
        secondModGroup(6, 50);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 19:
        firstModGroup(6, 180000, false);
        Serial.print("result:     ");
        Serial.print(scores[0]);
        Serial.print(",     ");
        Serial.println(scores[1]);
        break;

      case 20:

        break;

      case 21:

        break;

      case 22:

        break;

      case 23:

        break;


    }
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(buzzerPin2, HIGH);
    delay(25 * delayValue);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(buzzerPin2, LOW);
    scores[0] = 0;
    scores[1] = 0;
    modSelected = 0;
    delay(10);
  } else {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("La modalita ");
    lcd.setCursor(12, 0);
    lcd.print(modSelected);
    lcd.setCursor(14, 0);
    lcd.print(" non esiste,");
    lcd.setCursor(0, 1);
    lcd.print("Modalita disponibili:");
    lcd.setCursor(0, 2);
    lcd.print("1 - 23");
  }
}


boolean debounce(int n)
{
  boolean current = (digitalRead(buttonPins[n]));
  if (lastButtonsState[n] != current)
  {
    delay(1);
    current = digitalRead(buttonPins[n]);
  }
  return current;
}

void lightLed()
{
  while (true)
  {
    currentNumber = random(0, dimensions);

    if (currentNumber != lastNumber)
    {
      break;
    }
  }
  lastNumber = currentNumber;

  for (int i = 0; i < dimensions; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentNumber], HIGH);
}

void convertValueToArray()
{
  for (int i = 0; i < sizeof(arraySelected) / sizeof(arraySelected[0]); i++)
  {
    for (int j = 0; j < (sizeof(buttons) / sizeof(buttons[0])) - 2; j++) {
      if (arraySelected[i] == buttons[j]) {
        arrayFinal[i] = j;
      }
    }
  }
}

int convertArrayToNumber()
{
  int c = arrayFinal[0] * 10 + arrayFinal[1];
  return c;
}

