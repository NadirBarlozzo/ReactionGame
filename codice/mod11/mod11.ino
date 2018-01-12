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
int shot = 25;
boolean error;
int buzzerPin = 10;
int delayValue = 10;
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
  Start();
  while((pressed == false && error == false) && Time() <= timeReflection){
    for(int i = 0; i < (sizeof(buttonPins) / sizeof(buttonPins[0]));i++){
      currentButtonsState[i] = debounce(i);
      if(lastButtonsState[i] == LOW && currentButtonsState[i] == HIGH && i == currentNumber)
      {
        pressed = true;
      }
      if(lastButtonsState[i] == LOW &&  currentButtonsState[i] == HIGH && i != currentNumber){
        error = true;
      }
      lastButtonsState[i] = currentButtonsState[i];
    }
  }
  if(pressed == true){
    score++;
    digitalWrite(buzzerPin, HIGH); 
      delay(delayValue); 
      digitalWrite(buzzerPin, LOW);  
  }
  if(error == true){
    timeReflection -= 0.05;  
  }
  pressed = false;
  error = false;
  shot--;
  //Stampa dei dati
  Cifre(shot, a,b,c,d,e,f,g);
  Cifre(score, a2,b2,c2,d2,e2,f2,g2);
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
    for(int i = 0; i < (sizeof(ledPins) / sizeof(ledPins[0])); i++)
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

//Metodo Per la stampa delle cifre
void Cifre(float numero, int a1, int b1, int c1, int d1, int e1, int f1, int g1){
  if(numero == 1){
    digitalWrite(a1, LOW);
    digitalWrite(b1, HIGH);
    digitalWrite(c1, HIGH);
    digitalWrite(d1, LOW);
    digitalWrite(e1, LOW);
    digitalWrite(f1, LOW);
    digitalWrite(g1, LOW);
  }
  else if(numero == 2){
    digitalWrite(a1, HIGH);
    digitalWrite(b1, HIGH);
    digitalWrite(c1, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(e1, HIGH);
    digitalWrite(f1, LOW);
    digitalWrite(g1, HIGH);
  }
  else if(numero == 3){
    digitalWrite(a1, HIGH);
    digitalWrite(b1, HIGH);
    digitalWrite(c1, HIGH);
    digitalWrite(d1, HIGH);
    digitalWrite(e1, LOW);
    digitalWrite(f1, LOW);
    digitalWrite(g1, HIGH);
  }
  else if(numero == 4){
    digitalWrite(a1, LOW);
    digitalWrite(b1, HIGH);
    digitalWrite(c1, HIGH);
    digitalWrite(d1, LOW);
    digitalWrite(e1, LOW);
    digitalWrite(f1, HIGH);
    digitalWrite(g1, HIGH);
  }
  else if(numero == 5){
    digitalWrite(a1, HIGH);
    digitalWrite(b1, LOW);
    digitalWrite(c1, HIGH);
    digitalWrite(d1, HIGH);
    digitalWrite(e1, LOW);
    digitalWrite(f1, HIGH);
    digitalWrite(g1, HIGH);
  }
  else if(numero == 6){
    digitalWrite(a1, HIGH);
    digitalWrite(b1, LOW);
    digitalWrite(c1, HIGH);
    digitalWrite(d1, HIGH);
    digitalWrite(e1, HIGH);
    digitalWrite(f1, HIGH);
    digitalWrite(g1, HIGH);
  }
  else if(numero == 7){
    digitalWrite(a1, HIGH);
    digitalWrite(b1, HIGH);
    digitalWrite(c1, HIGH);
    digitalWrite(d1, LOW);
    digitalWrite(e1, LOW);
    digitalWrite(f1, LOW);
    digitalWrite(g1, LOW);
  }
  else if(numero == 8){
    digitalWrite(a1, HIGH);
    digitalWrite(b1, HIGH);
    digitalWrite(c1, HIGH);
    digitalWrite(d1, HIGH);
    digitalWrite(e1, HIGH);
    digitalWrite(f1, HIGH);
    digitalWrite(g1, HIGH);
  }
  else if(numero == 9){
    digitalWrite(a1, HIGH);
    digitalWrite(b1, HIGH);
    digitalWrite(c1, HIGH);
    digitalWrite(d1, HIGH);
    digitalWrite(e1, LOW);
    digitalWrite(f1, HIGH);
    digitalWrite(g1, HIGH);
  }
}
