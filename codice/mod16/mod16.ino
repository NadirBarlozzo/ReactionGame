/**
 * Array contenente il vecchio stato dei bottoni. 
 */
boolean lastButtonsState[4];

/**
 * Array contenente lo stato attuale dei bottoni.
 */
boolean currentButtonsState[4];

/**
 * Booleano che verifica se si è presenti nel primo ciclo.
 */
boolean firstCicle = true;

/**
 * Array contenente i pins dei bottoni.
 */
int buttonPins[] = {1,2,3,4};

/**
 * Array contenente i pins dei led
 */
int ledPins[] = {5,6,7,8};

/**
 * Il numero di millisecondi mancanti alla fine del gioco.
 */
int countdown = 60000;

/**
 * Valore relativo al vecchio indice del led da accendere.
 */
int lastNumber = -1;

/**
 * Valore relativo all'indice attuale del led da accendere.
 */
int currentNumber = -1;

/**
 * Punteggio della partita
 */
int score = 0;

void setup() 
{
  for(int i = 0; i < sizeof(buttonPins); i++)
  {
    //Assegno i pin ai relativi bottoni e led.
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);

    //Riempio di false i due array.
    lastButtonsState[i] = false;
    currentButtonsState[i] = false;
  }

  Serial.begin(9600);
}

void loop() 
{ 
  if(firstCicle)
  {
    lightLed();
    firstCicle = false;  
  }
  
  for(int i = 0; i < sizeof(buttonPins); i++)
  {
    currentButtonsState[i] = debounce(i); 
    //digitalRead(buttonPins[currentNumber]);

    if(currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i == currentNumber)
    {
      score++;
      lightLed();
    }
    
    lastButtonsState[i] = currentButtonsState[i];
    countdown--;
    delay(1);
    
    if(countdown == 0)
    {
      exit(0);
    }
  } 
}

boolean debounce(int n)
{
   boolean current = digitalRead(buttonPins[n]); 
   if(lastButtonsState[n] != current)
   {
       delay(5);
       current = digitalRead(buttonPins[n]);
   }
   return current;
}

void lightLed()
{
  boolean a = true;
  while(a)
  {
    currentNumber = random(0,9); 
    
    if(currentNumber != lastNumber)
    {
      a = false;
    }
  }
  lastNumber = currentNumber;

  for(int i = 0; i < sizeof(ledPins); i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentNumber], HIGH);
}
