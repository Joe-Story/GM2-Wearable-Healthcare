#include "MAX30100.h"
MAX30100* pulseOxymeter;
float dcFiltIR;

int sensorPin = A0;
int ledPin = 13;
int sensorValue = 0;
int ecgarray[500];
int ppgarray[500];
int i = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Begin Test!");
  delay(500);

  pulseOxymeter = new MAX30100();
  pinMode(2, OUTPUT);
}

void loop() {

  for(i = 0; i<2000; i = i+1) {
    sensorValue = analogRead(sensorPin);
    //Serial.println(sensorValue);
    ecgarray[i] = sensorValue;
    
    pulseoxymeter_t result = pulseOxymeter->update();
    dcFiltIR = -(result.dcFilteredIR);
    ppgarray[i] = dcFiltIR;
    Serial.println(dcFiltIR);
    Serial.println(sensorValue);
    Serial.println(millis());
    
    delay(4);
  }

//  for(i = 0; i<250; i=i+1) {
//    //Serial.println("Break!");
//    Serial.print("ECG Value ");
//    Serial.print(i+1);
//    Serial.print(": ");
//    Serial.println(ecgarray[i]);
//    delay(2);
//  }

//  for(i = 0; i<250; i=i+1) {
//    //Serial.println("Break!");
//    Serial.print("PPG Value ");
//    Serial.print(i+1);
//    Serial.print(": ");
//    Serial.println(ppgarray[i]);
//    delay(2);
//  }
   
  delay(5000000);
}


//Serial.println(sensorValue);




//  digitalWrite(ledPin, HIGH);
//  delay(sensorValue/10);
//  digitalWrite(ledPin, LOW);
//  delay(sensorValue/10);



//  if(sensorValue<810) {
//    Serial.println("Beat!");
//    Serial.println(millis());
//    Serial.println("");
//    delay(150);
//  }
