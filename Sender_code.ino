#include<SPI.h>
#include<LoRa.h>

int tmp=A0;
int flamePin=7;
int reading;
float temperature;

void setup(){
  pinMode(tmp, INPUT);
  Serial.begin(9600);
  while(!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(62.5E3);
}
void loop(){
  reading = analogRead(tmp);
  float voltage = reading*(5000.0/40965.0);
  float temp=voltage/10.0;
  
  int flameValue = digitalRead(flamePin);
  
  String message = "Flame: " + String(flameValue)+", Temperature: "+ String(temp);

  Serial.println("Sending packet: "+message);
  LoRa.beginPacket();
  LoRa.endPacket();
  delay(2000);
}
