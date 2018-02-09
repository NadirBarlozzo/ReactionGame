boolean lastButtonsState[6];
boolean currentButtonsState[6];
boolean firstCicle = true;
int buttonPins[] = {1, 2, 3, 4, 5, 6};
int ledPins[] = {7, 8, 9, 10, 11, 12};
long countdown = 100000;

int lastNumber = NULL;

int currentNumber = -1;

float timer = 0;
int score = 0;

int buzzerPin = 7;
int buzzerPin2 = 6;
int delayValue = 20;

void setup()
{
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
    digitalRead(buttonPins[currentNumber]);

    if (currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i == currentNumber)
    {
      score++;
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(buzzerPin2, HIGH);
      delay(delayValue);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(buzzerPin2, LOW);
      lightLed();
    }

    lastButtonsState[i] = currentButtonsState[i];

    delay(1);

    if (millis() - timer >= countdown || score == 50)
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
  boolean current = digitalRead(buttonPins[n]);
  if (lastButtonsState[n] != current)
  {
    delay(1);
    current = digitalRead(buttonPins[n]);
  }
  return current;
}

void lightLed()
{
  boolean a = true;
  while (a)
  {
    currentNumber = random(0, 10);

    if (currentNumber != lastNumber)
    {
      a = false;
    }
  }
  lastNumber = currentNumber;

  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentNumber], HIGH);
}
