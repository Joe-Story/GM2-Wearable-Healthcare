int sensorPin = A0;
int ledPin = 13;
int sensorValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Begin Test!");
}

void loop() {
  
  sensorValue = analogRead(sensorPin);
//  if(sensorValue<810) {
//    Serial.println("Beat!");
//    Serial.println(millis());
//    Serial.println("");
//    delay(150);
//  }
  Serial.println(sensorValue);
  delay(8);  
//  digitalWrite(ledPin, HIGH);
//  delay(sensorValue/10);
//  digitalWrite(ledPin, LOW);
//  delay(sensorValue/10);
}
