#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

int count = 0;
int score = 0;
int modality = 0;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  
IPAddress ip(192,168,0,16);

char server[] = "localhost"; 

EthernetClient client;

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Ethernet.begin(mac, ip);
  Serial.begin(9600); 
}

void receiveEvent(int howMany) {
  if(count == 0)
    score = Wire.read();
  else if(count == 1)
    modality = Wire.read();

  count++;
}

void loop() {
  delay(1000);
  if (client.connect(server, 3600) && count == 2) {
    client.print("GET /reactiongame/insert.php?"); 
    client.print("score="); // This
    client.print(score);
    client.print("&modality="); 
    client.print(modality);
    client.println(" HTTP/1.1"); // Part of the GET request
    client.println("Host: localhost:3600"); // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here (it is explained in previous article). If you have a web page, enter its address (ie.Host: "www.yourwebpage.com")
    client.println("Connection: close"); // Part of the GET request telling the server that we are over transmitting the message
    client.println();
    client.println();
    client.stop();
  }
 else {
    Serial.println("--> connection failed\n");
 }
  delay(10000);
}








