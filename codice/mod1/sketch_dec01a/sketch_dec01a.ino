boolean lastButtonsState[12];
boolean currentButtonsState[12];
int buttonPins[] = {1,2,3,4,5,6,7,8,9,10,11,12};
int ledPins[] = {13,14,15,16,17,18,19,20,21,22,23,24};
int countdown = 60000;
int lastNumber = -1;
int n;

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
  for(int i = 0; i < sizeof(buttonPins); i++)
  {
    currentButtonsState[i] = debounce(i); 
    lightLed();
    digitalRead(buttonPins[n]);
  
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
  boolean a = false;
  while(a)
  {
    n = random(0,9); 
    
    if(n != lastNumber)
    {
      a = true;
    }
  }
  lastNumber = n;

  for(int i = 0; i < sizeof(ledPins); i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[n], HIGH);
}

