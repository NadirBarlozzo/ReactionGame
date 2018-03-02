

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

}
