int ledPins[] = {23,25,27,29,31,33,35,37,39,41, 43, 45};
int buttonPins[] = {22,24,26,28,30,32,34,36,38,40, 42,44};

void setup() {
  // put your setup code here, to run once:
  
  for(int i = 0; i < 12; i++){
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
    }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 12; i++){
    digitalWrite(ledPins[i], HIGH);
    Serial.print("bottone corrente:  ");
    Serial.println(i);
    Serial.print("stato bottone:  ");
    Serial.println((digitalRead(buttonPins[i])));
    }
    delay(100);
  
}
