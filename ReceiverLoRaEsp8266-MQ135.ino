#include <SPI.h>
#include <LoRa.h>
 
#define ss 15
#define rst 16
#define dio0 4

String device_id;
String hava_kalitesi;
int pos1, pos2;
 
void setup() {
  Serial.begin(115200);
  while (!Serial);
 
  Serial.println("LoRa Receiver Callback");
 
  LoRa.setPins(ss, rst, dio0);
 
  if (!LoRa.begin(473E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // register the receive callback
  //LoRa.onReceive(onReceive);
 
  // put the radio into receive mode
  //LoRa.receive();
}
 
void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    String LoRaData = LoRa.readString();

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

 
    pos1 = LoRaData.indexOf('/');
    pos2 = LoRaData.indexOf('&');

    device_id = LoRaData.substring(0, pos1);
    hava_kalitesi = LoRaData.substring(pos1 + 1, pos2);

    Serial.print(F("Device ID: "));
    Serial.println(device_id);
 
    Serial.print(F("Hava Kalitesi: "));
    Serial.print(hava_kalitesi);
    Serial.println(F("ppm"));
    Serial.println("");

    }
}
 
