
void fourthModGroup(boolean f)
{
  while (true) {
    if (firstCicle)
    {
      boolean flash = f;
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
      if (counter == getNumButtons()) {
        if (isChecked()) {
          score++;
        }
        counter = 0;
        scheme++;
        if (scheme >= 4)
        {
          scores[0] = score;
          scores[1] = timerGame;
          clearVariables();
          return;
        }
        numButtons = random(1, 7);
        for (int i = 0; i < sizeof(pressedNumbers) / sizeof(pressedNumbers[0]); i++) {
          pressedNumbers[i] = false;
        }
        defineScheme(numButtons);
      }

    }

    stampLCD();
  }
}
boolean getNumButtons() {
  return flash ? numButtons : 10 - numButtons;
}

boolean isChecked() {

  for (int i = 0; i < numButtons; i++) {
    if (pressedNumbers[chosenNumbers[i]] == flash) {
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
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
  chosenNumbers[0] = savePoint;
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

