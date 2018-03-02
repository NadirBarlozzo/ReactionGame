

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

void setNextButton()
{
  while (true)
  {
    currentNumber = random(0, dimensions);

    if (currentNumber != lastNumber)
    {
      break;
    }
  }
  lastNumber = currentNumber;

  for (int i = 0; i < dimensions; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentNumber], HIGH);
}

void stampLCD(){
  
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Tempo: ");

    lcd.setCursor(0, 2);
    lcd.print("Punteggio: ");

    lcd.setCursor(0, 1);
    lcd.print(timerGame);

    lcd.setCursor(0, 3);
    lcd.print(score);
}

void clearVariables() {


/*lastNumber = -1;
currentNumber = -1;*/
timer = 0;
dimensions = 0;
score = 0;
countdown = 0;


countdownLoop = 0;


timerGame = 0;


pressed = false;

timeReflection = 1000;
shot = 100;
error = false;

selectedTime = 1000;
int chosenNumbers[6] = { -1, -1, -1, 1, -1, -1};
int discardedNumbers[9] = { -1, -1, -1, 1, -1, -1, -1, -1, -1};
boolean pressedNumbers[10];
scheme = 0;
counter = 0;
numButtons = 0;
int buttonPinsSelected[11];
int randomValues[11];
int timeArray[10];
int timecount = 0;
int countRandom = 0;
}
