
/**
   Il numero di millisecondi mancanti alla fine del gioco.
*/
long countdown = 0;


int countdownLoop = 0;



double timerGame = 0;

/**
   Booleano che verifica se si è presenti nel primo ciclo.
*/
boolean firstCicle = true;

void firstModGroup(int d, long t, boolean octave)
{
  while (true) {
    if (firstCicle)
    {
      dimensions = d;
      countdown = t;
      boolean led = HIGH;
      timer = millis();
      lightLed();
      firstCicle = false;
    }

    for (int i = 0; i < dimensions; i++)
    {
      currentButtonsState[i] = debounce(i);
      //digitalRead(buttonPins[currentNumber]);
      //Serial.print("bottone corrente: ");
      //Serial.println(buttonPins[i]);
      if (currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i == currentNumber)
      {
        //Serial.println("premuto correttamente");
        score++;

        digitalWrite(buzzerPin, HIGH);
        digitalWrite(buzzerPin2, HIGH);
        delay(delayValue);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(buzzerPin2, LOW);
        lightLed();
      }

      lastButtonsState[i] = currentButtonsState[i];
      delay(1);
      Serial.println(millis() - timer);
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

          lightLed();
          if (countdownLoop >= 4) {
            for (int i = 0; i < dimensions; i++)
            {
              digitalWrite(ledPins[i], LOW);
            }
            scores[0] = score;
            scores[1] = timerGame;
            clearVariables1();
            return;
          }
          timer = millis();
        } else {
          scores[0] = score;
          scores[1] = timerGame;
          clearVariables1();
          return;
        }
      }
    }
    
    if (true) {
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
  }
}

void clearVariables1() {
  countdown = 0;

  /**
     Valore relativo al vecchio indice del led da accendere.
  */
  lastNumber = -1;

  /**
     Valore relativo all'indice attuale del led da accendere.
  */
  currentNumber = -1;

  countdownLoop = 0;

  timer = 0;

  dimensions = 0;
  /**
     Punteggio della partita
  */
  score = 0;

  firstCicle = true;
}
