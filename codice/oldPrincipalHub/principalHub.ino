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

long buttons[] = {16738455, 16724175, 16718055, 16743045, 16716015, 16726215, 16734885, 16728765, 16730805, 16732845, 16748655};

int scores[] = {0, 0};


int buzzerPin = 6;
int buzzerPin2 = 7;
int delayValue = 20;


long arraySelected[] = {0, 0};
//int arrayFinal[2];
//long val;
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

/**
   Booleano che verifica se si è presenti nel primo ciclo.
*/
boolean corner;
boolean pressed = false;
float startTime;
float elapsedTime;
float timeReflection = 1000;
int shot = 100;
boolean error = false;

//variabili del fourthModGroup
long selectedTime = 1000;
int chosenNumbers[6] = { -1, -1, -1, 1, -1, -1};
int discardedNumbers[9] = { -1, -1, -1, 1, -1, -1, -1, -1, -1};
boolean pressedNumbers[10];
int scheme = 0;
int counter = 0;
int numButtons = 0;
boolean flash = true;

//variabili della mod 23
int indice = 0;
int buttonPinsSelected[11];
int randomValues[11];
int timeArray[10];
int timecount = 0;
int countRandom = 0;

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
  irrecv.enableIRIn();
  Ethernet.begin(mac, ip);
  conn = client.connect(server, 3600);
}
/*boolean isValid() {
  for (int i = 0; i < (sizeof(buttons) / sizeof(buttons[0])) - 2; i++) {
    if (val == buttons[i]) {
      return true;
    }
  }
  return false;
  }*/

void loop()
{
  /*while (true) {
    if (irrecv.decode(&results))
    {
      val = results.value;
      Serial.println(val);
      if (val == buttons[10])
      {
        modeSelected = 0;
        arraySelected[0] = 0;
        arraySelected[1] = 0;
        Serial.println("Premuto +");
        break;
      }
    }
    }
    while (true)
    {
    Serial.println(modeSelected);
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
        modeSelected = convertArrayToNumber();
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Modalita: ");

        lcd.setCursor(0, 1);
        lcd.print(modeSelected);

        if (val == buttons[10]) {
          break;
        }
      }
      irrecv.resume();
    }
    irrecv.resume();
    }
  */
  digitalWrite(ledPins[10], HIGH);
  while (!debounce(10)) {
    lcd.setCursor(0, 0);
    lcd.print("Premi # per scegliere il gioco");
  }
  digitalWrite(ledPins[10], LOW);
  while (!debounce(10) || modeSelected > 0 || modeSelected < 24) {

    for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++) {
      currentButtonsState[i] = debounce(i);
      if ((currentButtonsState[i] = debounce(i)) == HIGH && lastButtonsState[i] == false && i < 10) {
        arraySelected[0] = arraySelected[1];
        arraySelected[1] = i;
        modeSelected = arraySelected[1] + arraySelected[0] * 10;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Modalita disponibili:");
        lcd.setCursor(0, 1);
        lcd.print("1 - 23");
        lcd.setCursor(0, 2);
        lcd.print("modalita");
        lcd.setCursor(9, 2);
        lcd.print(modeSelected);
        if  (modeSelected < 1 || modeSelected > 23) {
          lcd.setCursor(0, 2);
          lcd.print("Inserire modalita valida");
        }
      }
      lastButtonsState[i] = currentButtonsState[i];
    }
  }
  if (conn) {
    Serial.println("connesso");
    client.println("GET /reactiongame/insert.php?score=&modality= HTTP/1.1");
    client.println("Host: 192.168.5.17");
    client.println("Connection: close");
    client.println();
  }
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
  switch (modeSelected) {

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
      secondModGroup(10, 50);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
      break;

    case 4:
      thirdModGroup(4, 100, true);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
      break;

    case 5:

      break;

    case 6:

      break;

    case 7:
      thirdModGroup(10, 50, false);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
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
      thirdModGroup(4, 25, true);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
      break;

    case 12:
      thirdModGroup(4, 50, true);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
      break;

    case 13:
      thirdModGroup(6, 25, false);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
      break;

    case 14:
      thirdModGroup(6, 50, false);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
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
      fourthModGroup(true);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
      break;

    case 21:
      fourthModGroup(false);
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);

    case 22:

      break;

    case 23:
      mod23();
      Serial.print("result:     ");
      Serial.print(scores[0]);
      Serial.print(",     ");
      Serial.println(scores[1]);
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
  delay(10);
}


/*
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
  }*/

