/**
   Array contenente il vecchio stato dei bottoni.
*/
boolean lastButtonsState[11];

/**
   Array contenente lo stato attuale dei bottoni.
*/
boolean currentButtonsState[11];

/**
   Booleano che verifica se si è presenti nel primo ciclo.
*/
boolean firstCicle = true;

/**
   Array contenente i pins dei bottoni.
*/
int buttonPins[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 44};
/**
   Array contenente i pins dei led
*/

int ledPins[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 45};

long selectedTime = 1000;

/**
   Valore relativo al vecchio indice del led da accendere.
*/

int chosenNumbers[6] = { -1, -1, -1, 1, -1, -1};

int discardedNumbers[9] = { -1, -1, -1, 1, -1, -1, -1, -1, -1};

boolean pressedNumbers[10];

int scheme = 0;
int counter = 0;
int numButtons = 0;
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
  //Serial.println("Inizio ciclo");

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
    boolean b = true;
    boolean b2 = false;
    digitalWrite(ledPins[10], HIGH);
    while (b) {
      for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++) {
        if (b2 == true) {
          for (int i = 1; i < (sizeof(ledPins) / sizeof(ledPins[0])) - 2; i++)
          {
            digitalWrite(ledPins[i], HIGH);
          }
        }
        currentButtonsState[i] = debounce(i);
        if (currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i == 10) {
          b2 = true;
          digitalWrite(ledPins[10], LOW);
        } else if (currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i >= 1 && i <= 8 && b2 == true) {
          selectedTime = 1000 * i;
          b = false;
        }
      }
    }
    for (int i = 1; i < (sizeof(ledPins) / sizeof(ledPins[0])) - 1; i++)
    {
      digitalWrite(ledPins[i], LOW);
    }
    numButtons = random(1, 7);
    defineScheme(numButtons);
    for (int i = 0; i < 10; i++) {
      pressedNumbers[i] = false;
    }
    firstCicle = false;
  }

  for (int i = 0; i < (sizeof(buttonPins) / sizeof(buttonPins[0])) - 1; i++)
  {
    currentButtonsState[i] = debounce(i);
    if (currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i])
    {
      pressedNumbers[i] = true;
      counter++;
    }
    lastButtonsState[i] = currentButtonsState[i];

    delay(1);
    if (counter == numButtons) {
      if (isChecked()) {
        score++;
      }
      counter = 0;
      scheme++;
      Serial.print("schema numero : ");
      Serial.println(scheme);
      Serial.print("azzeccati: ");
      Serial.println(score);
      if (scheme >= 4)
      {

        Serial.println("                  FINE!!               ");
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
      numButtons = random(1, 7);
      for (int i = 0; i < sizeof(pressedNumbers) / sizeof(pressedNumbers[0]); i++) {
        pressedNumbers[i] = false;
      }
      defineScheme(numButtons);
    }

  }
}


boolean isChecked() {

  for (int i = 0; i < numButtons; i++) {
    if (pressedNumbers[chosenNumbers[i]]) {
      return false;
    }
  }
  return true;
}

void defineScheme(int n) {
  for (int i = 0; i < n; i++) {
    int currentNumber = random(0, 10);
    for (int j = 0;  j < i; j++) {
      if (chosenNumbers[j] == currentNumber) {
        currentNumber = random(0, 10);
        j = -1;
      }
    }
    chosenNumbers[i] = currentNumber;
  }
  int savePoint = chosenNumbers[0];
  int count = 0;
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    for (int j = 0; j < n; j++) {
      if (i == chosenNumbers[j]) {
        digitalWrite(ledPins[i], HIGH);
        break;

      }
      if (j + 1 == n) {
        discardedNumbers[count++] = i;
        Serial.println(chosenNumbers[0]);
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
  chosenNumbers[0] = savePoint;
  Serial.print("8.0: ");
  Serial.println(chosenNumbers[0]);
  delay(selectedTime - 300);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(buzzerPin2, HIGH);
  delay(50);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(buzzerPin2, LOW);
  delay(200);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(buzzerPin2, HIGH);
  delay(50);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(buzzerPin2, LOW);

  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    digitalWrite(ledPins[i], LOW);
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


