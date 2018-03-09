#include <SPI.h>
#include <Ethernet2.h>

int count = 0;
String score = "0";
String modality = "0";
String data = "";

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x11, 0x1D, 0x55 };
  
IPAddress ip(192, 168, 5, 16); //(192,168,5,16);
IPAddress server(192,168,5,17);

EthernetClient client;

void setup() {
  Serial.begin(9600);
  modality = "18";
  Ethernet.begin(mac, ip);

  int conn = client.connect(server, 3600);
      Serial.println("conn:");

  if (conn) {
    Serial.println("connesso");
    client.println("GET /reactiongame/update_modality.php?modality="+modality+" HTTP/1.1");
    client.println("Host: 192.168.5.17");
    client.println("Connection: close");
    client.println();
  }
 else {
    Serial.println("--> connection failed\n");
    Serial.println(0);
 }
}

void loop() {
}  










