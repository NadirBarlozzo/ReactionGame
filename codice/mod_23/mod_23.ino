/**
   Array contenente il vecchio stato dei bottoni.
*/
boolean lastButtonsState[12];

/**
   Array contenente lo stato attuale dei bottoni.
*/
boolean currentButtonsState[12];

/**
   Booleano che verifica se si è presenti nel primo ciclo.
*/
boolean firstCicle = true;

/**
   Array contenente i pins dei bottoni.
*/
int buttonPins[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44};

/**
   Array contenente i pins dei led
*/

int ledPins[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};

int buttonPinsSelected[11];
int randomValues[11];
int timeArray[10];
int timecount = 0;
int countRandom = 0;

int buzzerPin = 7;
int buzzerPin2 = 6;
int indice = 0;
int score = 0;


void setup()
{
  randomSeed(analogRead(0));
  pinMode(buzzerPin, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
  {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);

    currentButtonsState[i] = false;
    lastButtonsState[i] = false;
  }

  for (int i = 0; i < sizeof(randomValues) / sizeof(randomValues[0]); i++)
  {
    randomValues[i] = -1;
  }
  Serial.begin(9600);
}

void loop()
{
  if (firstCicle)
  {
    for (int i = 0; i < sizeof(buttonPinsSelected) / sizeof(buttonPinsSelected[0]); i++)
    {
      buttonPinsSelected[i] = -1;
      Serial.print("Il campo all'indice ");
      Serial.print(i);
      Serial.print(" ha valore ");
      Serial.println(buttonPinsSelected[i]);
    }

    boolean a = true;
    while (a)
    {
      if (debounce(10))
      {
        Serial.println("Premuto # ");
        a = false;
      }
    }


    int pinValue = -1;
    boolean b = true;
    while (b)
    {
      for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
      {
        currentButtonsState[i] = debounce(i);
        if (currentButtonsState[i])
        {
          Serial.print("Bottone premuto: ");
          Serial.println(buttonPins[i]);
          if (debounce(10) && indice >= 2)
          {
            lampeggio();
          }
          else
          {
            if (currentButtonsState[i] != lastButtonsState[i] && buttonPins[i] != 42)
            {
              Serial.println("Bottone valido");
              int conto = 0;
              for (int j = 0; j < sizeof(buttonPinsSelected) / sizeof(buttonPinsSelected[0]); j++)
              {

                if (buttonPinsSelected[j] != buttonPins[i])
                {
                  conto++;
                  Serial.print("Conto ");
                  Serial.println(conto);
                  if (conto == 11)
                  {
                    Serial.println("Non ripetuto");
                    digitalWrite(ledPins[i], HIGH);
                    buttonPinsSelected[indice] = buttonPins[i];
                    indice++;

                    if (indice == 11)
                    {
                      Serial.println("INIZIO LAMPEGGIO");
                      b = false;
                    }
                  }
                }
              }
            }
          }

          lastButtonsState[i] = currentButtonsState[i];
        }
      }

    }

    lampeggio();
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

boolean debounceSelected(int n)
{
  boolean current = (digitalRead(buttonPinsSelected[n]));
  if (lastButtonsState[n] != current)
  {
    delay(1);
    current = digitalRead(buttonPinsSelected[n]);
  }
  return current;
}

void lampeggio()
{
  for (int i = 0; i < indice; i++)
  {
    Serial.println(buttonPinsSelected[i]);
  }

  double sec = 0;
  while (sec < 3)
  {
    Serial.println("Secondo");
    for (int i = 0; i < indice; i++)
    {
      digitalWrite(buttonPinsSelected[i] + 1, LOW);
    }
    delay(500);
    sec += 0.5;
    Serial.println("Lampeggia");

    for (int i = 0; i < sizeof(buttonPinsSelected) / sizeof(buttonPinsSelected[0]); i++)
    {
      digitalWrite(buttonPinsSelected[i] + 1, HIGH);
    }
    delay(500);
    sec += 0.5;
  }

  for (int i = 0; i < sizeof(buttonPinsSelected) / sizeof(buttonPinsSelected[0]); i++)
  {
    Serial.println("Spegni led");
    digitalWrite(buttonPinsSelected[i] + 1, LOW);
  }
  play();
}

void play()
{
  int millitimer;
  int first = 0;
  Serial.println("Inizio gioco");
  for (int i = 0; i < 10; i++)
  {
    millitimer = millis();
    if (first != 0)
    {
      for (int j = 0; j < 2; j++)
      {
        for (int y = 0; y < indice; y++)
        {
          digitalWrite(buttonPinsSelected[y] + 1, HIGH);
        }
        delay(500);
        for (int y = 0; y < indice; y++)
        {
          digitalWrite(buttonPinsSelected[y] + 1, LOW);
        }
        delay(500);
      }
    }
    Serial.println(indice);
    Serial.print("Schema ");
    Serial.println(i);

    int lastRandomIndice = -1;
    int randomIndice;
    for (int j = 0; j < indice; j++)
    {
      boolean a = true;
      while (a)
      {
        randomIndice = random(0, indice);
        if (randomIndice != lastRandomIndice && !containsRandomValue(randomIndice))
        {
          randomValues[countRandom] = randomIndice;
          countRandom++;
          lastRandomIndice = randomIndice;
          a = false;
        }
      }

      Serial.print("Indice selezionato ");
      Serial.println(randomIndice);

      boolean b = true;
      while (b)
      {
        digitalWrite(buttonPinsSelected[randomIndice] + 1, HIGH);
        if (debounceSelected(randomIndice))
        {
          score++;
          delay(50);
          Serial.print("Punteggio: ");
          Serial.println(score);
          digitalWrite(buttonPinsSelected[randomIndice] + 1, LOW);
          b = false;
          randomIndice = -1;
        }
      }
    }
    first++;
    countRandom = 0;
    for (int i = 0; i < sizeof(randomValues) / sizeof(randomValues[0]); i++)
    {
      randomValues[i] = -1;
    }
    timeArray[timecount] = millis() - millitimer;
    timecount++;
  }
  Serial.println("FINE SCHEMI");

  int fulltime = 0;
  for(int i = 0; i < sizeof(timeArray) / sizeof(timeArray[0]); i++)
  {
    fulltime += timeArray[i];
  }
  Serial.print("Tempo impiegato: ");
  Serial.println(fulltime);
}

boolean containsRandomValue(int randomIndice)
{
  for (int i = 0; i < indice; i++)
  {
    if (randomIndice == randomValues[i])
    {
      return true;
    }
  }
  return false;
}

