String measurement;
#define TDSSensorPin         A1   //TDS meter Analog output to Arduino Analog Input 0
#define VREF                 5.0  //analog reference voltage(Volt) of the ADC
#define TDSNoSamples         30   //times of collection
float TDSVoltage, TDSCompensationCoefficient, TDSCompensationVoltage;
int TDSValue, TDSTotal, TDSAverage;
float temperature = 25;
void TDS() {
  for (int thisReading = 0; thisReading < TDSNoSamples; thisReading++) {
    TDSTotal = TDSTotal + analogRead(TDSSensorPin);
  }// calculate the average:
  TDSAverage = TDSTotal / TDSNoSamples;
  TDSTotal = 0;
  TDSVoltage = TDSAverage * VREF / 1023.0;
  // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  TDSCompensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
  TDSCompensationVoltage = TDSVoltage / TDSCompensationCoefficient; // temperature compensation
  TDSValue = (133.42 * pow(TDSCompensationVoltage, 3) - 255.86 * pow(TDSCompensationVoltage, 2) + 857.39 * TDSCompensationVoltage) * 0.5;
}
void setup() {
  Serial.begin(9600);
  pinMode(TDSSensorPin, INPUT);
}

void loop() {
    TDS();
    Serial.println(TDSValue);
    delay(5000);
  }
