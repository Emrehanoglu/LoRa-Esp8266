#include <SPI.h>
#include <LoRa.h>

#define ss 15
#define rst 16
#define dio0 2
#define gaz A0

float hava_kalitesi;
String LoRaMessage = "";
char device_id[15] = "Emrenin Lorasi";

void setup() 
{
  pinMode(gaz,INPUT);
  Serial.begin(115200);
  
  while (!Serial);
  Serial.println(F("LoRa Sender"));
  LoRa.setPins(ss, rst, dio0);
    if (!LoRa.begin(473E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
}
 
void loop() 
{
  hava_kalitesi = analogRead(gaz);

  Serial.print(("Device ID: "));
  Serial.println(device_id);
  
  Serial.print("Hava Kalitesi:  ");
  Serial.print(hava_kalitesi);
  Serial.println("ppm");
  Serial.println("");

  LoRaMessage = String(device_id) + "/" + String(hava_kalitesi) + "&";
  
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.println("ppm");  
  LoRa.endPacket(); 
  delay(3000);
}
