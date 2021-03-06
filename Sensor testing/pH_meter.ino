#define phSensorPin         A0    //pH meter Analog output to Arduino Analog Input 0
#define VREF                5.0
#define phOffset            0.42  //deviation compensate
#define phPrintInterval     100
#define phNoSamples         20    //times of collection

int phSamples[phNoSamples];       //Store the average value of the sensor feedback
int phSamplesIndex = 0;
float phTotal = 0;
float phAverage = 0;
float phValue, phVoltage;
void pH() {
 // subtract the last reading/reset the array:
 phTotal = phTotal - phSamples[phSamplesIndex];
 phSamples[phSamplesIndex] = analogRead(phSensorPin); // read from the sensor:
 // add the reading to the total:
 phTotal = phTotal + phSamples[phSamplesIndex];
 // advance to the next position in the array:
 phSamplesIndex = phSamplesIndex + 1;
 // if the end of the array is reached
 if (phSamplesIndex >= phNoSamples) {
   phSamplesIndex = 0;
 }
 phAverage = phTotal / phNoSamples; // calculate the average:
 phVoltage = phAverage * VREF / 1023;
 phValue = 3.5 * phVoltage + phOffset;
}
void setup() {
 Serial.begin(115200);
 pinMode(phSensorPin, INPUT);
 
 // initialising all the readings to 0:
 for (int thisReading = 0; thisReading < phNoSamples; thisReading++) {
   phSamples[thisReading] = 0;
 }
}
void loop() {
 static unsigned long pHPrintTime = millis();
 if (millis() - pHPrintTime > phPrintInterval) {
   pH();
   Serial.println(phValue);
   pHPrintTime = millis();
 }
}
