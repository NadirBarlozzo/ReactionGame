

void secondModGroup(int dim, int colpi)
{
  dimensions = dim;
  shot = colpi;
  timer = millis();
  setNextButton();

  while (true) {
    for (int i = 0; i < dimensions; i++)
    {
      currentButtonsState[i] = debounce(i);
      digitalRead(buttonPins[currentNumber]);

      if (currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i == currentNumber)
      {
        score++;
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(buzzerPin2, HIGH);
        delay(delayValue);
        delay(1);
        timerGame = millis() - timer;
        if (timerGame >= countdown || score == shot)
        {
          Serial.println("Completed");
          for (int i = 0; i < dimensions; i++)
          {
            digitalWrite(ledPins[i], LOW);
          }
          digitalWrite(buzzerPin, HIGH);
          digitalWrite(buzzerPin2, HIGH);
          delay(25 * delayValue);
          digitalWrite(buzzerPin, LOW);
          digitalWrite(buzzerPin2, LOW);
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

