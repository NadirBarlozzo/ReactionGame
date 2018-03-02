
void mod23()
{
  indice = 0;
  for (int i = 0; i < sizeof(buttonPinsSelected) / sizeof(buttonPinsSelected[0]); i++)
  {
    buttonPinsSelected[i] = -1;
  }

  while (true)
  {
    if (debounce(10))
    {
      break;
    }


    int pinValue = -1;
    while (true)
    {
      for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
      {
        currentButtonsState[i] = debounce(i);
        if (currentButtonsState[i])
        {
          if (debounce(10) && indice >= 2)
          {
            lampeggio();
          }
          else
          {
            if (currentButtonsState[i] != lastButtonsState[i] && buttonPins[i] != 42)
            {
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
                      break;
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

    int lastRandomIndice = -1;
    int randomIndice;
    for (int j = 0; j < indice; j++)
    {
      while (true)
      {
        randomIndice = random(0, indice);
        if (randomIndice != lastRandomIndice && !containsRandomValue(randomIndice))
        {
          randomValues[countRandom] = randomIndice;
          countRandom++;
          lastRandomIndice = randomIndice;
          break;
        }
      }
      while (true)
      {
        digitalWrite(buttonPinsSelected[randomIndice] + 1, HIGH);
        if (debounceSelected(randomIndice))
        {
          score++;
          delay(50);
          Serial.print("Punteggio: ");
          Serial.println(score);
          digitalWrite(buttonPinsSelected[randomIndice] + 1, LOW);
          randomIndice = -1;
          break;
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

  int fulltime = 0;
  for (int i = 0; i < sizeof(timeArray) / sizeof(timeArray[0]); i++)
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

