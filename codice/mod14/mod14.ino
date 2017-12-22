int buttonPins[] = {1,2,3,4};
int ledPins[] = {5,6,7,8};
boolean lastButtonsState[4];
boolean currentButtonsState[4];
boolean pressed = false;
long startTime;
long endTime;
float elapsedTime;
float timeReflection = 1;
int score = 0;
int currentNumber = -1;
int lastNumber = -1;
int shot = 50;
boolean error;

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
  Start();
  while((pressed == false && error == false)){
    for(int i = 0; i < sizeof(buttonPins);i++){
      currentButtonsState[i] = debounce(i);
      if(lastButtonsState[i] == LOW && currentButtonsState[i] == HIGH && i == currentNumber)
      {
        pressed = true;
      }
      if((lastButtonsState[i] == LOW &&  currentButtonsState[i] == HIGH && i != currentNumber)){
        error = true;
      }
      elapsedTime = Time();
      lastButtonsState[i] = currentButtonsState[i];
    }
  }
  if(pressed == true && elapsedTime < timeReflection){
    score++;  
  }
  if(error == true || elapsedTime >= timeReflection){
    timeReflection -= 0.05;  
  }
  pressed = false;
  error = false;
  shot--;
  if(shot <= 0){
    exit(0);
  }
}

  

void Start(){

  boolean a = true;
  while(a)
  {
    currentNumber = random(0,3); 
    
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
    delay(1000);
    digitalWrite(ledPins[currentNumber], HIGH);
  startTime = millis();

}

float Time(){
   endTime = millis();
   elapsedTime = (endTime - startTime);
   elapsedTime = elapsedTime/1000;
   return elapsedTime;
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
