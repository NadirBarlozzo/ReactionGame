
void thirdModGroup(int dim, int colpi, boolean angolo)
{
  while (true) {
    if (firstCicle)
    {
      corner = angolo;
      dimensions = dim;
      shot = colpi;
      start();
      firstCicle = false;
    }
    int counter = 0;
    while (pressed == false && error == false && (timeElapsed() <= timeReflection || !corner)) {
      for (int i = 0; i < dimensions; i++) {
        if (!corner) {
          counter = i;
        } else {
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
        if (lastButtonsState[i] == LOW &&  currentButtonsState[i] == HIGH && counter != currentNumber || (!corner && timeElapsed() <= timeReflection)) {
          error = true;
        }
        lastButtonsState[i] = currentButtonsState[i];
      }
    }
    if (pressed) {
      digitalWrite(buzzerPin, HIGH);
      delay(delayValue);
      digitalWrite(buzzerPin, LOW);
      score++;
      Serial.println(score);
    }
    if (error) {
      timeReflection -= 50;
    }
    pressed = false;
    error = false;
    shot--;
    start();
    if (shot <= 0) {
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
    stampLCD();
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
  lastNumber = currentNumber;
  for (int i = 0; i < dimensions; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }

  digitalWrite(ledPins[currentNumber], HIGH);
  //delay(1000);
  startTime = millis();

}

float timeElapsed() {
  elapsedTime = (millis() - startTime);
  elapsedTime = elapsedTime;
  return elapsedTime;
}

