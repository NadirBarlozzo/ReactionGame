/**
   Array contenente il vecchio stato dei bottoni.
*/
boolean lastButtonsState[6];

/**
   Array contenente lo stato attuale dei bottoni.
*/
boolean currentButtonsState[6];

/**
   Booleano che verifica se si è presenti nel primo ciclo.
*/
boolean firstCicle = true;

/**
   Array contenente i pins dei bottoni.
*/
int buttonPins[] = {22, 24, 26, 28, 30, 32};
/**
   Array contenente i pins dei led
*/

int ledPins[] = {23, 25, 27, 29, 31, 33};

/**
   Il numero di millisecondi mancanti alla fine del gioco.
*/
long countdown = 30000;

/**
   Valore relativo al vecchio indice del led da accendere.
*/
int lastNumber = NULL;

/**
   Valore relativo all'indice attuale del led da accendere.
*/
int currentNumber = -1;


float timer = 0;
/**
   Punteggio della partita
*/
int score = 0;
int buzzerPin = 7;
int buzzerPin2 = 6;
int delayValue = 20;


void setup()
{
  //Funzionamento dei pin

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
}

void loop()
{
  if (firstCicle)
  {
    boolean led = HIGH;
    for (int i = 0; i < 6; i++) {

      for (int j = 0; j < sizeof(ledPins) / sizeof(ledPins[0]); j++)
      {
        digitalWrite(ledPins[j], led);
      }
      delay(500);
      led = !led;
      if (i % 2 == 0) {

        digitalWrite(buzzerPin, HIGH);
        digitalWrite(buzzerPin2, HIGH);
        delay(delayValue);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(buzzerPin2, LOW);
      }
    }
    timer = millis();
    lightLed();
    firstCicle = false;
  }

  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
  {
    currentButtonsState[i] = debounce(i);
    //digitalRead(buttonPins[currentNumber]);
    //Serial.print("bottone corrente: ");
    //Serial.println(buttonPins[i]);
    if (currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i == currentNumber)
    {
      //Serial.println("premuto correttamente");
      score++;
      Serial.print("Score: ");
      Serial.println(score);
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(buzzerPin2, HIGH);
      delay(delayValue);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(buzzerPin2, LOW);
      lightLed();
    }

    lastButtonsState[i] = currentButtonsState[i];
    //Stampa dei dati
    /*Cifre(countdown, a,b,c,d,e,f,g);
      Cifre(score, a2,b2,c2,d2,e2,f2,g2);*/
    delay(1);
    Serial.println(millis() - timer);
    if ((millis() - timer) >= countdown)
    {
      for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
      {
        digitalWrite(ledPins[i], LOW);
      }
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(buzzerPin2, HIGH);
      delay(25 * delayValue);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(buzzerPin2, LOW);
      exit(0);
    }
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
  //Serial.print("stato bottone: ");
  //Serial.println(current);
  return current;
}

void lightLed()
{
  boolean a = true;
  while (a)
  {

    currentNumber = random(0, 6);

    if (currentNumber != lastNumber)
    {
      a = false;
    }
  }
  lastNumber = currentNumber;
  //Serial.print("currentNumber: ");
  //Serial.println(currentNumber);
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
  {
    //Serial.print("Spengo led ");
    //Serial.println(ledPins[i]);
    digitalWrite(ledPins[i], LOW);
  }
  //Serial.print("Accendo led ");
  //Serial.println(ledPins[currentNumber]);
  digitalWrite(ledPins[currentNumber], HIGH);
  /*Serial.print("led da accendere:  ");
    Serial.println(ledPins[currentNumber]);*/
}
