#include <SPI.h>
#include <LoRa.h>

int nss = 10;
int dio0 = 2;
String full_string;
String inString = "";
int rssi;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  LoRa.setPins(nss, dio0);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(62.5E3);
}

void loop() {
  int packetSize = LoRa.parsePacket();
  full_string = "";

  if (packetSize) {
    // received a packet
    Serial.println("");
    Serial.println("Received packet: ");
    
    while (LoRa.available()) {
      char incoming = (char)LoRa.read();
      full_string += incoming;
      rssi = LoRa.packetRssi();
    }
    
    Serial.println("Data: " + full_string);
    Serial.print("RSSI: ");
    Serial.println(rssi);
    
    // Check for the presence of "Flame: 1" in the received packet
    if (full_string.indexOf("Flame: 1") != -1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2000);
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Flame detected");
    } else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("No flame");
    }
  }
}
