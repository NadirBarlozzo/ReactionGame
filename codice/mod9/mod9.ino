boolean lastButtonsState[11];

boolean currentButtonsState[11];

int buttonPins[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 44};

int ledPins[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 45};

int buzzerPin = 7;
int buzzerPin2 = 6;

long timeSelected = -1;

int addendo1 = -1;
int addendo2 = -1;
int sommaFinale = -1;
int arraySomma[] = {0, 0};
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

    lastButtonsState[i] = false;
    currentButtonsState[i] = false;
  }
  Serial.begin(9600);
}

void loop()
{
  boolean a = true;
  while (a)
  {
    if (debounce(10))
    {
      Serial.println("Seleziona Tempo!");
      for (int i = 2; i < 10; i++)
      {
        digitalWrite(ledPins[i], HIGH);
      }
      a = false;
    }
  }

  boolean b = true;
  while (b)
  {
    for (int i = 2; i < 10; i++)
    {
      if (debounce(i))
      {
        timeSelected = i * 1000;

        for (int i = 2; i < 10; i++)
        {
          digitalWrite(ledPins[i], LOW);
        }

        b = false;
      }
    }
  }
  Serial.print("Tempo selezionato: ");
  Serial.println(timeSelected);

  for (int i = 0; i < 8; i++)
  {
    boolean a = true;
    while (a)
    {
      addendo1 = random(0, 10);
      addendo2 = random(0, 10);

      if (addendo1 != 0 && addendo2 != 0)
      {
        a = false;
      }
    }
    sommaFinale = addendo1 + addendo2;
    if (sommaFinale >= 10)
    {
      arraySomma[0] = 1;
      arraySomma[1] = (sommaFinale % 10);
    }
    else
    {
      arraySomma[0] = 0;
      arraySomma[1] = sommaFinale;
    }
    Serial.print(addendo1);
    Serial.print(" + ");
    Serial.println(addendo2);

    long timer = millis();
    boolean c = true;

    if (arraySomma[0] == 1)
    {
      while (c)
      {
        delay(1);
        if (debounce(arraySomma[0]))
        {
          boolean d = true;
          while (d)
          {
            delay(1);
            if (debounce(arraySomma[1]))
            {
              Serial.println("Risultato esatto");
              score++;
              d = false;
              c = false;
            }
            else if ((millis() - timer) >= timeSelected)
            {
              Serial.println("Tempo scaduto");
              d = false;
              c = false;
            }
          }
        }
        else if ((millis() - timer) >= timeSelected)
        {
          Serial.println("Tempo scaduto");
          c = false;
        }
      }
    }
    else
    {
      while (c)
      {
        delay(10);
        if (debounce(arraySomma[1]))
        {
          Serial.println("Risultato esatto");
          score++;
          delay(10);
          c = false;
        }
        else if ((millis() - timer) >= timeSelected)
        {
          Serial.println("Tempo scaduto");
          delay(10);
          c = false;
        }
      }
    }
  }
  Serial.print("PUNTEGGIO: ");
  Serial.println(score);
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
