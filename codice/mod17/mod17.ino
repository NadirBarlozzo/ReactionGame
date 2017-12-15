boolean lastButtonsState[6];
boolean currentButtonsState[6];
boolean firstCicle = true;
int buttonPins[] = {1,2,3,4,5,6};
int ledPins[] = {7,8,9,10,11,12};
int countdown = 0;
int lastNumber = -1;
int currentNumber = -1;
int score = 0;

void setup() 
{
  for(int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
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
      lightLed();
    }
    
    lastButtonsState[i] = currentButtonsState[i];
    countdown++;
    delay(1);
    
    if(countdown == 100000 || score == 25)
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
  delay(1000);
  digitalWrite(ledPins[currentNumber], HIGH);
}
