
/**
   Il numero di millisecondi mancanti alla fine del gioco.
*/
long countdown = 0;

/**
   Valore relativo al vecchio indice del led da accendere.
*/
int lastNumber = NULL;

/**
   Valore relativo all'indice attuale del led da accendere.
*/
int currentNumber = -1;

int countdownLoop = 0;

float timer = 0;

int dimensions = 0;
/**
   Punteggio della partita
*/
int score = 0;
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
        Serial.print("Score: ");
        Serial.println(score);
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
            scores[1] = millis() - timer;
            clearVariables();
            return;
          }
          timer = millis();
        } else {
          scores[0] = score;
          scores[1] = millis() - timer;
          clearVariables();
          return;
        }


      }
    }
  }
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

void lightLed()
{
  boolean a = true;
  while (a)
  {

    currentNumber = random(0, dimensions);

    if (currentNumber != lastNumber)
    {
      a = false;
    }
  }
  lastNumber = currentNumber;
  //Serial.print("currentNumber: ");
  //Serial.println(currentNumber);
  for (int i = 0; i < dimensions; i++)
  {
    //Serial.print("Spengo led ");
    //Serial.println(ledPins[i]);
    digitalWrite(ledPins[i], LOW);
  }
  //Serial.print("Accendo led ");
  //Serial.println(ledPins[currentNumber]);
  digitalWrite(ledPins[currentNumber], HIGH);
  /*Serial.print("led da accendere:  ");
    Serial.println(ledPins[currentNumber]);*/
}

void clearVariables(){
countdown = 0;

/**
   Valore relativo al vecchio indice del led da accendere.
*/
lastNumber = NULL;

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
