#include "DHT.h"
#include "SimpleTimer.h"


const int waterPumpPin = 6; /*Water Pump*/
const int mixturePin = 7; /*Water Pump for mix the water*/

/*Water level , temp and humidity */

#define DHTPIN 4        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define waterlvlPin A2
DHT dht(DHTPIN, DHTTYPE);
int waterLevel;
SimpleTimer timer;
float humidity, temperature;

/*TDS Sensor*/
String measurement;
#define TDSSensorPin         A1   //TDS meter Analog output to Arduino Analog Input 0
#define VREF                 5.0  //analog reference voltage(Volt) of the ADC
#define TDSNoSamples         30   //times of collection
float TDSVoltage, TDSCompensationCoefficient, TDSCompensationVoltage;
int TDSValue, TDSTotal, TDSAverage;

/*
//pH Sensor
#define phSensorPin         A2    //pH meter Analog output to Arduino Analog Input 0
#define VREF                5.0
#define phOffset            -0.15  //deviation compensate
#define phNoSamples         40     //times of collection
float phTotal = 0;
float phAverage = 0;
float phValue, phVoltage;
*/


#define phSensorPin A0            //pH meter Analog output to Arduino Analog Input 2
#define Offset 21.677           //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;







void TemperatureHumidity() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperature)) {
    // Serial.println(F("Failed to read from the DHT sensor!"));
    temperature = 25;
    humidity = 50;
    return;
  }
}

void TDS() {
  for (int thisReading = 0; thisReading < TDSNoSamples; thisReading++) {
    TDSTotal = TDSTotal + analogRead(TDSSensorPin);
  }

  // calculate the average:
  TDSAverage = TDSTotal / TDSNoSamples;
  TDSTotal = 0;
  TDSVoltage = TDSAverage * VREF / 1023.0;
  // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  TDSCompensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
  TDSCompensationVoltage = TDSVoltage / TDSCompensationCoefficient; // temperature compensation
  TDSValue = (133.42 * pow(TDSCompensationVoltage, 3) - 255.86 * pow(TDSCompensationVoltage, 2) + 857.39 * TDSCompensationVoltage) * 0.5;
}

void waterLvl() {
  waterLevel = analogRead(waterlvlPin);
  // map the analog values to percentages
  //waterLevel = map(waterLevel, 0, 600, 0, 100);
}

/*
void pH() {
  for (int thisReading = 0; thisReading < phNoSamples; thisReading++) {
    phTotal = phTotal + analogRead(phSensorPin);
  }

  // calculate the average:
  phAverage = phTotal / phNoSamples;
  phTotal = 0;
  phVoltage = phAverage * VREF / 1023;
  phValue = 3.5 * phVoltage + phOffset;
}
*/

void waterPump() {
  digitalWrite(waterPumpPin, HIGH);
}
void waterPumpOff() {
  digitalWrite(waterPumpPin, LOW);
}

void miturePump() {
  digitalWrite(mixturePin, HIGH);
}
void mixturePumpOff() {
  digitalWrite(mixturePin, LOW);
}

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}


void setup() {
  Serial.begin(115200);
  pinMode(waterlvlPin, INPUT);
  pinMode(waterPumpPin, OUTPUT);
  pinMode(mixturePin, OUTPUT);
  pinMode(TDSSensorPin, INPUT);
  pinMode(phSensorPin, INPUT);
  //pinMode(LED,OUTPUT);
  dht.begin();

}


void loop() {
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(phSensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = -5.8887*voltage+Offset;
      if(pHValue<=0.0){pHValue=0.0;}
      if(pHValue>14.0){pHValue=14.0;}
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
  //Serial.print("Voltage:");
  //Serial.print(voltage,2);
  //Serial.print("    pH value: ");
  //Serial.println(pHValue,2);
  digitalWrite(LED,digitalRead(LED)^1);
  printTime=millis();
  }
  if (Serial.available() > 0) {
  String data = Serial.readStringUntil('\n');
  if (data == "S") {
  //timer.run();
  TemperatureHumidity();
  waterLvl();
  TDS();
  //pH();
  //waterPump();
  measurement = String(humidity) + "-" + String(temperature) + "-" + String(waterLevel)+ "-" + String(TDSValue)+ "-" + String(pHValue);
  Serial.println(measurement);
  
  }
  
  if (pHValue < 5.5) {
    //Serial.println("pH is too low! Change the water!");
  } 
  else if (pHValue > 8.5) { //adjust the pH solution
      //waterPump();
      //delay(1000);
      //waterPumpOff();
      //miturePump();
      //delay(5000);
      //mixturePumpOff();
    }
  } 
}
