int buttonPins[] = {22, 24, 38, 40};
int ledPins[] = {23, 25, 39, 41};
boolean lastButtonsState[4];
boolean currentButtonsState[4];
boolean pressed = false;
float startTime;
boolean firstCicle = true;
float elapsedTime;
float timeReflection = 1000;
int score = 0;
int currentNumber = -1;
int lastNumber = -1;
int shot = 100;
boolean error = false;
int buzzerPin = 6;
int buzzerPin2 = 7;
int delayValue = 20;
void setup()
{
  randomSeed(analogRead(0));
  pinMode(buzzerPin, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
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

  if (firstCicle)
  {
    boolean led = HIGH;
    for (int i = 0; i < 6; i++) {

      for (int j = 0; j < sizeof(ledPins) / sizeof(ledPins[0]); j++)
      {
        digitalWrite(ledPins[j], led);
      }
      delay(500);
      led = !led;
      if (i % 2 == 0) {

        digitalWrite(buzzerPin, HIGH);
        digitalWrite(buzzerPin2, HIGH);
        delay(delayValue);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(buzzerPin2, LOW);
      }
    }
    start();
    firstCicle = false;
  }
  Serial.println("go!");
  while (pressed == false && error == false && timeElapsed() <= timeReflection) {
    for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[i]); i++) {
      currentButtonsState[i] = debounce(i);
      if (lastButtonsState[i] == LOW && currentButtonsState[i] == HIGH && i == currentNumber)
      {
        pressed = true;
      }
      if (lastButtonsState[i] == LOW &&  currentButtonsState[i] == HIGH && i != currentNumber) {
        error = true;
      }
      lastButtonsState[i] = currentButtonsState[i];
    }
  }
  Serial.println("finish check!");
  if (pressed == true) {
    digitalWrite(buzzerPin, HIGH);
    delay(delayValue);
    digitalWrite(buzzerPin, LOW);
    score++;
    Serial.println(score);
  }
  if (error == true) {
    timeReflection -= 50;
  }
  pressed = false;
  error = false;
  shot--;
  start();
  if (shot <= 0) {
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
    {
      digitalWrite(ledPins[i], LOW);
    }
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(buzzerPin2, HIGH);
    delay(25 * delayValue);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(buzzerPin2, LOW);
    exit(0);
  }
}



void start() {

  boolean a = true;
  while (a)
  {
    currentNumber = random(0, 4);

    if (currentNumber != lastNumber)
    {
      a = false;
    }
  }
  lastNumber = currentNumber;
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
  {
    digitalWrite(ledPins[i], LOW);
  }

  digitalWrite(ledPins[currentNumber], HIGH);
  //delay(1000);
  startTime = millis();
  Serial.println(startTime);

}

float timeElapsed() {
  elapsedTime = (millis() - startTime);
  elapsedTime = elapsedTime;
  return elapsedTime;
}

boolean debounce(int n)
{
  boolean current = digitalRead(buttonPins[n]);
  if (lastButtonsState[n] != current)
  {
    delay(1);
    current = digitalRead(buttonPins[n]);
  }
  return current;
}
