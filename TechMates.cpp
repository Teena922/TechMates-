#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Sensor pins
int gasPin = 34;
int moisturePin = 35;
int oxygenPin = 32;
int buzzerPin = 25;

void setup() {
  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Bluetooth start
  SerialBT.begin("Coal_Mine_Rover");
  Serial.println("Bluetooth Started");
}

void loop() {

  // Read sensors
  int gasValue = analogRead(gasPin);
  int moistureValue = analogRead(moisturePin);
  int oxygenValue = analogRead(oxygenPin);

  // Safety status
  String status = "SAFE";

  if (gasValue > 600 || oxygenValue < 200) {
    status = "DANGER";
    digitalWrite(buzzerPin, HIGH);
  } 
  else {
    digitalWrite(buzzerPin, LOW);
  }

  // Data format for App
  // gas,moisture,oxygen,status
  String sendData = String(gasValue) + "," +
                    String(moistureValue) + "," +
                    String(oxygenValue) + "," +
                    status;

  // Send via Bluetooth
  SerialBT.println(sendData);
  Serial.println(sendData);

  delay(1000); // 1 second delay
}