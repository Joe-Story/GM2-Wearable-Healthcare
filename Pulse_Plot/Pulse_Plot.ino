#include "MAX30100.h"

MAX30100* pulseOxymeter;
float Temperature;
float readTemperature();
float dcFiltIR;
float dcFiltRed;
float dcavcurrent;
float dcavprev;
float dcdifference;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("PPG Pulse Plot!");
  delay(1000);

  pulseOxymeter = new MAX30100();
  pinMode(2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  pulseoxymeter_t result = pulseOxymeter->update();
  dcavprev = dcavcurrent;
  dcFiltIR = -(result.dcFilteredIR);
  dcFiltRed = -(result.dcFilteredRed);
  dcavcurrent = ((dcFiltIR + dcFiltRed)/2);


  dcdifference = dcavcurrent - dcavprev;  
  
  //Serial.print( "DCValue: " );
  //Serial.println( dcFiltIR );
  //Serial.println( dcFiltRed );
  Serial.println( dcavprev );
  
  delay(15);
}
