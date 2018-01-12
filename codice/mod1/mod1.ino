/**
 * Array contenente il vecchio stato dei bottoni. 
 */
boolean lastButtonsState[10];

/**
 * Array contenente lo stato attuale dei bottoni.
 */
boolean currentButtonsState[10];

/**
 * Booleano che verifica se si è presenti nel primo ciclo.
 */
boolean firstCicle = true;

/**
 * Array contenente i pins dei bottoni.
 */
int buttonPins[] = {1,2,3,4,5,6,7,8,9,10};

/**
 * Array contenente i pins dei led
 */
int ledPins[] = {11,12,13,14,15,16,17,18,19,20};

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

//Pin per il sette segmenti
//barra superiore
int a = 9;
//lato destro superiore
int b = 10;
//inferiore destra
int c = 11;
//inferiore
int d = 12;
//inferiore sinistra
int e = 13;
//superiore sinistra
int f = 14;
//centrale
int g = 15;

//Pin per il secondo sette segmenti
//barra superiore
int a2 = 16;
//lato destro superiore
int b2 = 17;
//inferiore destra
int c2 = 18;
//inferiore
int d2 = 19;
//inferiore sinistra
int e2 = 20;
//superiore sinistra
int f2 = 21;
//centrale
int g2 = 22;

void setup() 
{
  //Funzionamento dei pin
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(g2, OUTPUT);
  
  for(int i = 0; i < sizeof(buttonPins)/sizeof(buttonPins[0]); i++)
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
  
  for(int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
  {
    currentButtonsState[i] = debounce(i); 
    //digitalRead(buttonPins[currentNumber]);

    if(currentButtonsState[i] == true && currentButtonsState[i] != lastButtonsState[i] && i == currentNumber)
    {
      score++;
      digitalWrite(buzzerPin, HIGH); 
      delay(delayValue); 
      digitalWrite(targetPin, LOW);
      lightLed();
    }
    
    lastButtonsState[i] = currentButtonsState[i];
    countdown--;
    //Stampa dei dati
    Cifre(countdown, a,b,c,d,e,f,g);
    Cifre(score, a2,b2,c2,d2,e2,f2,g2);
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

  for(int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentNumber], HIGH);
}
