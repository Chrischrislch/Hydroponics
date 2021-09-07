const int waterPumpPin = 6; /*Water Pump*/
void waterPump() {
 digitalWrite(waterPumpPin, HIGH);
}
void waterPumpOff() {
 digitalWrite(waterPumpPin, LOW);
}
void setup() {
  // put your setup code here, to run once:
   pinMode(waterPumpPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
     waterPump();
     delay(3000);
     waterPumpOff();
     delay(3000);
}
