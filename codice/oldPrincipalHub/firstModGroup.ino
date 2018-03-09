
void firstModGroup(int d, long t, boolean octave)
{
  dimensions = d;
  countdown = t;
  boolean led = HIGH;
  timer = millis();
  setNextButton();
  while (true) {
    for (int i = 0; i < dimensions; i++)
    {
      currentButtonsState[i] = debounce(i);
      if (currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i == currentNumber)
      {
        score++;

        digitalWrite(buzzerPin, HIGH);
        digitalWrite(buzzerPin2, HIGH);
        delay(delayValue);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(buzzerPin2, LOW);
        setNextButton();
      }

      lastButtonsState[i] = currentButtonsState[i];
      delay(1);
      timerGame = (millis() - timer) / 1000;
      if ((millis() - timer) >= countdown)
      {
        for (int i = 0; i < dimensions; i++)
        {
          digitalWrite(ledPins[i], LOW);
        }
        if (octave) {
          digitalWrite(buzzerPin, HIGH);
          digitalWrite(buzzerPin2, HIGH);
          delay(2000);
          digitalWrite(buzzerPin, LOW);
          digitalWrite(buzzerPin2, LOW);
          countdownLoop++;

          setNextButton();
          if (countdownLoop >= 4) {
            for (int i = 0; i < dimensions; i++)
            {
              digitalWrite(ledPins[i], LOW);
            }
            scores[0] = score;
            scores[1] = timerGame;
            clearVariables();
            return;
          }
          timer = millis();
        } else {
          scores[0] = score;
          scores[1] = timerGame;
          clearVariables();
          return;
        }
      }
    }

    stampLCD();
  }
}

