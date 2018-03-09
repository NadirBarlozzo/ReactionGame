
void thirdModGroup(int dim, int colpi, boolean angolo)
{
  corner = angolo;
  dimensions = dim;
  shot = colpi;
  start();
  while (true) {
    int counter = 0;
    while (!pressed && !error && (timeElapsed() <= timeReflection || !corner)) {
      for (int i = 0; i < dimensions; i++) {
        timerGame = millis() - startTime;
        counter = i;
        if (counter) {
          switch (currentNumber) {
            case 2:
              counter = 8;
              break;
            case 3:
              counter = 9;
              break;
          }
        }

        currentButtonsState[i] = debounce(counter);

        if (lastButtonsState[i] == LOW && currentButtonsState[i] == HIGH && counter == currentNumber)
        {
          pressed = true;
        }
        if (lastButtonsState[i] == LOW && currentButtonsState[i] == HIGH && counter != currentNumber || (!corner && timeElapsed() >= timeReflection)) {

          error = true;
        }
        lastButtonsState[i] = currentButtonsState[i];
      }
    }
    stampThirdLCD(colpi);
    if (pressed) {
      digitalWrite(buzzerPin, HIGH);
      delay(delayValue);
      digitalWrite(buzzerPin, LOW);
      score++;
    }
    if (error) {
      timeReflection -= 50;
    }
    if (timeReflection < 200) {
      lcd.setCursor(0, 1);

      stampThirdLCD(colpi);
      lcd.print("GAME OVER");

      clearVariables();
      return;
    }
    pressed = false;
    error = false;
    shot--;
    start();
    if (shot <= 0) {
      int n = 0;
      for (int i = 0; i < dimensions; i++)
      {
        n = i;
        if (corner) {
          switch (i) {
            case 2:
              n = 8;
              break;
            case 3:
              n = 9;
              break;
          }
        }
        digitalWrite(ledPins[n], LOW);
      }
      scores[0] = score;
      scores[1] = timerGame;
      stampThirdLCD(colpi);
      clearVariables();
      return;
    }
  }
}

void start() {

  while (currentNumber == lastNumber)
  {
    currentNumber = random(0, dimensions);
    if (corner) {
      switch (currentNumber) {
        case 2:
          currentNumber = 8;
          break;
        case 3:
          currentNumber = 9;
          break;
      }
    }
  }
  int n = 0;
  lastNumber = currentNumber;
  for (int i = 0; i < dimensions; i++)
  {
    n = i;
    if (corner) {
      switch (i) {
        case 2:
          n = 8;
          break;
        case 3:
          n = 9;
          break;
      }
    }
    digitalWrite(ledPins[n], LOW);
  }

  digitalWrite(ledPins[currentNumber], HIGH);
  delay(200);
  startTime = millis();

}

float timeElapsed() {
  elapsedTime = (millis() - startTime);
  return elapsedTime;
}

