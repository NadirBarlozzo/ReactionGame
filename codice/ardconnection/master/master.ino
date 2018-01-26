#include <Wire.h>

int count = 0;

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(8); 
  if(count == 0)
    Wire.write(1000);
  else if(count == 1)
    Wire.write(10);  
  Wire.endTransmission(); 

  count++;
  delay(500);
}

