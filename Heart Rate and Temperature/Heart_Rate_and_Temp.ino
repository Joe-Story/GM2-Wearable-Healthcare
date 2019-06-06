//Authors: Joseph Story, Ana-Maria Marcu, Rose Humphry, Vidya Kanakaratnam

//HEART RATE SENSOR STARTUP
#include "MAX30100.h"

MAX30100* pulseOxymeter;

float Temperature;
float readTemperature();
float test = 0;
float BPM;
float spo2;
int dcarray[] = {0,0,0,0,0,0,0,0,0,0};

int total_av_values = 8;
float bpmarray[] = {0,0,0,0,0,0,0,0};
float spo2array[] = {0,0,0,0,0,0,0,0};

float bpmsum = 0;
float avbpm = 0;
float spo2sum = 0;
float avspo2 = 0;
int sensorValue = 0;

//TEMPERATURE SENSOR STARTUP
void getTemp(float * t, char pin, int Beta)
{

    // Converts input from a thermistor voltage divider to a temperature value.
    // The voltage divider consists of thermistor Rt and series resistor R0.
    // The value of R0 is equal to the thermistor resistance at T0.
    // You must set the following constants:
    //                  adcMax  ( ADC full range value )
    //                  analogPin (Arduino analog input pin)
    //                  invBeta  (inverse of the thermistor Beta value supplied by manufacturer).
    // Use Arduino's default reference voltage (5V or 3.3V) with this module.
    //

  const int analogPin = pin; // replace 0 with analog pin
  const float invBeta = 1.00 / Beta;   // 4300+- 3%

  const  float adcMax = 1023.00;
  const float invT0 = 1.00 / 298.15;   // room temp in Kelvin

  int adcVal, i, numSamples = 5;
  float  K, C, F;

  adcVal = 0;
  for (i = 0; i < numSamples; i++)
   {
     adcVal = adcVal + analogRead(analogPin);
     delay(100);
   }
  adcVal = adcVal/5;
  K = 1.00 / (invT0 + invBeta*(log ( adcMax / (float) adcVal - 1.00)));
  C = K - 273.15;                      // convert to Celsius
  F = ((9.0*C)/5.00) + 32.00;   // convert to Fahrenheit
  t[0] = K; t[1] = C; t[2] = F;
  return;
}

void getBPM() {
  pulseoxymeter_t result = pulseOxymeter->update();
  BPM = result.heartBPM;
  spo2 = result.SaO2;
  if(millis()<18000) {
    if( result.pulseDetected == true ) {
      Serial.println("Beat!");      
      Serial.print("Beat time: ");
      Serial.println(millis());
      Serial.println("");
      //Serial.print("BPM: ");
      //Serial.println(BPM);
      //Serial.print("SpO2: ");
      //Serial.print(spo2);
      //Serial.println("%");
      //Serial.println("");
  
      for (byte i = 0; i < (total_av_values); i = i+1) {
        bpmarray[i] = bpmarray[i+1];
        spo2array[i] = spo2array[i+1];
      }
      bpmarray[(total_av_values - 1)] = BPM;
      spo2array[(total_av_values - 1)] = spo2;
    }
      
    //Serial.print( "DCValue: " );
    //Serial.println( dcFiltIR );
    //Serial.println( dcFiltRed );
    //Serial.println( dcavprev );
    
    delay(10);
  }
  else {
    for (byte i = 0; i < (total_av_values); i = i+1) {
      bpmsum = bpmsum + bpmarray[i];
      spo2sum = spo2sum + spo2array[i];
    }
    avbpm = bpmsum / total_av_values;
    avspo2 = spo2sum / total_av_values;

    Serial.print("Average BPM: ");
    Serial.println(avbpm);
    Serial.print("Average Blood Oxygen Content: ");
    Serial.print(avspo2);
    Serial.println("%");
    Serial.println("");
    delay(2000);
    Serial.println("Temperature Experiment!");
    Serial.println("");
    delay(500);
  }

}





int average_temperature(float previous_temp[5])
{
  float total;
  for (int i=0; i<5; i++)
    {
      total += previous_temp[i];
    }
  float average = total/5;

  return average;
}

 
 
 
 
 
 
 
void setup() {
  //HEART RATE SENSOR SETUP
  Wire.begin();
  Serial.begin(9600);
  Serial.println("PPG Pulse Detection!");
  delay(1000);

  pulseOxymeter = new MAX30100();
  pinMode(2, OUTPUT);
  
  
  //TEMPERATURE SENSOR SETUP
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  analogReference(DEFAULT);
 
}
 
void loop() {
  //HEART RATE SENSOR LOOP
  //pulseoxymeter_t result = pulseOxymeter->update();
  //delay(100);
  //pulseoxymeter_t result = pulseOxymeter->update();
  //delay(100);
  //pulseoxymeter_t result = pulseOxymeter->update();
  //delay(100);
  //pulseoxymeter_t result = pulseOxymeter->update();
  //delay(100);
  
  if(millis()<20000) {
    getBPM();
    
//    pulseoxymeter_t result = pulseOxymeter->update();
//    BPM = result.heartBPM;
//    SpO2 = result.SaO2;

    
  delay(10);  //40 for wrist, 10 for finger
  
  }

  else if(millis()<45000) {
    
    //Serial.print( "DCValue: " );
    //Serial.println( dcFiltIR );
    //Serial.println( dcFiltRed );
    //Serial.println( dcavprev );
    
    //delay(1);
    
    
    //TEMPERATURE SENSOR LOOP

    //Setup
    int i, n, m;
    float input_mc, input_skin;
    float previous_temp_mc[5], previous_temp_skin[5], previous_temp_re[5];
  
  
     
     float temp_mc[3];
     getTemp(temp_mc, A0, 4106);
     input_mc = temp_mc[1];
  
     float temp_skin[3];    
     getTemp(temp_skin, A3, 4119);
     input_skin = temp_skin[1];
     
     float temp_re = temp_mc[1]*0.022453 + temp_skin[1]*0.11698 + 32.416;
  
  
  
     for (i = 0; i < 4; i++) //only up to n-2 as don't need to keep the oldest value
       {
         previous_temp_mc[4-i] = previous_temp_mc[3-i]; 
         previous_temp_skin[4-i] = previous_temp_skin[3-i]; 
         previous_temp_re[4-i] = previous_temp_re[3-i]; 
       }
        
       previous_temp_mc[0] = input_mc;
       previous_temp_skin[0] = input_skin;
       previous_temp_re[0] = temp_re;
        
  
     float average_mc = average_temperature(previous_temp_mc);
     float average_skin = average_temperature(previous_temp_skin);
     float average_re = average_mc*0.022453 + average_skin*0.11698 + 32.416;
  
   /*   
     Serial.println(temp_mc[1]); //Serial.print("- Current Micro-Climate  deg. C      \n"); 
     Serial.print(" ");   
     Serial.print(average_mc); Serial.print("Average Micro-Climate deg. C     \n"); 
      
     Serial.println(temp_skin[1]); //Serial.print("- Current Skin  deg. C      \n");
     Serial.print(" ");   
     Serial.print(average_skin); Serial.print("Average Skin deg. C     \n");
  
     Serial.println(temp_re); //Serial.print("- Current Rectal deg. C     \n");
     Serial.print(average_re); Serial.print("Average Rectal deg. C     \n\n");
  */
  
      Serial.print("Current Micro-Climate  deg. C: "); 
      Serial.println(temp_mc[1]);//Serial.print(" \n");
      Serial.print("Current Insulated Skin  deg. C: "); 
      Serial.println(temp_skin[1]);//Serial.print(" \n");
      Serial.print("Current Core  deg. C: "); 
      Serial.println(temp_re);//Serial.print(" \n");
      Serial.println("");
  
  
      //Serial.print(previous_temp_skin[0]);Serial.print(" "); Serial.print(previous_temp_skin[1]);Serial.print(" "); Serial.print(previous_temp_skin[2]);Serial.print(" "); Serial.print(previous_temp_skin[3]);Serial.print(" "); Serial.print(previous_temp_skin[4]);
      //Serial.print("\n"); Serial.println(average_skin);
  
  
    
  
     if (average_re > 30){
      digitalWrite(10, HIGH);
      digitalWrite(13, LOW);
     }
     else if (temp_re <20){
      digitalWrite(10, HIGH);
      digitalWrite(13, LOW);
     }
     else if (temp_re = temp_skin[1]){
      digitalWrite(10, HIGH);
      digitalWrite(13, LOW);
     }
     else{
      digitalWrite(10, LOW);
      digitalWrite(13, HIGH);
     }
  } 

  else if(millis()<47000) {
    Serial.println("Blood Pressure Calculations!");
    Serial.println("");
    delay(2000);
  }
  
  else if(millis()<60000) {
    Serial.println("Calculations");
    delay(2000);
    //sensorValue = analogRead(A5);
    //Serial.println(sensorValue);
    //delay(4);
  }

      
     //delay(2000);
  
}
