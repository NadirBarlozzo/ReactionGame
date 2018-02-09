#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

int count = 0;
String score = "0";
String modality = "0";
String data = "";

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x10, 0x25, 0xFE };
  
byte ip[] = {192, 168, 5, 16}; //(192,168,5,16);
IPAddress server(192,168,5,17);

EthernetClient client;

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  score = "10";
  modality = "18";
  Ethernet.begin(mac, ip);
  int conn = client.connect(server, 444);
  if (conn) {
    Serial.println("connesso");
    client.println("GET /reactiongame/insert.php?score="+score+"&modality="+modality+" HTTP/1.1");
    client.println("Host: 192.168.5.17");
    client.println("Connection: close");
    client.println();
  }
 else {
    Serial.println("--> connection failed\n");
    Serial.println(conn);
 }
}

void receiveEvent(int howMany) {
  if(count == 0)
    score = Wire.read();
  else if(count == 1)
    modality = Wire.read();

  count++;
}

void loop() {
}  










