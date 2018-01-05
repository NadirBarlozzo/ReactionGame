boolean lastButtonsState[10];
boolean currentButtonsState[10];
boolean firstCicle = true;
int buttonPins[] = {1,2,3,4,5,6,7,8,9,10};
int ledPins[] = {13,14,15,16,17,18,19,20,21,22};
int countdown = 0;
int lastNumber = -1;
int currentNumber = -1;
int score = 0;
int buzzerPin = 10;
int delayValue = 10;

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
      digitalWrite(buzzerPin, HIGH); 
      delay(delayValue); 
      digitalWrite(targetPin, LOW);
      lightLed();
    }
    
    lastButtonsState[i] = currentButtonsState[i];
    countdown++;
    delay(1);
    
    if(countdown == 100000 || score == 50)
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
