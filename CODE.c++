#include <LiquidCrystal.h>
int pressurePin = A0; //pressure reading pin
int pressureRead; //for reading pressure pin
const int buttonPin = 8; // pin for CPR count
unsigned long time; //to display time for compressions
const int pressGood = 10;
const int pressBad = 9;
int BPM; //final output calculated beats per min
float bpmCount; // to calculate BPM
int cprCount = 0; // counter for the number of button presses, changed from int,
changed from float
int buttonState = 0; // current state of the button
int lastButtonState = 0; // previous state of the button
int cprTotal = 0; //total of the 5 stored values
int cprCycle = 0; //keeps track of CPR cycle
int timeSec, timeCPR, BPM_1; //calculating cpr time
float totalTime;
unsigned long timeBegin, timeEnd;
LiquidCrystal lcd(12, 11, 2, 3, 4, 5); //LCD pins
void setup()
{
 pinMode(buttonPin, INPUT); //CPR button
 pinMode(pressGood, OUTPUT); //for good release, led on Green
 pinMode(pressBad, OUTPUT); // for bad release, led on Red
 Serial.begin(9600); // start serial communication / uncomment to debug
 Serial.println("Begin CPR");
 lcd.begin(16, 2); //start LCD
 lcd.home();
 lcd.print("Begin CPR");
}
void loop()
{
 pressureRead = analogRead(pressurePin);
 time = millis(); //start time
 buttonState = digitalRead(buttonPin);
 if (buttonState != lastButtonState)
 {
if (buttonState == HIGH)
 { //depth of at least 2in per AHA guidelines
 lcd.clear();
 lcd.home();

 cprCount++; //add 1 to the running total
 Serial.println(cprCount);
 lcd.setCursor(0, 0);
 lcd.print("Count=");
 lcd.setCursor(7, 0);
 lcd.print(cprCount);
 lcd.setCursor(10, 0);
 lcd.print("R="); //rate BPM
 if (cprCount == 1)
 {
 timeBegin = millis(); //beginning time
 }
 }
 }
 //pressureRead = analogRead(pressurePin);
 if (pressureRead < 500)
 {
 digitalWrite(pressGood, HIGH);
 digitalWrite(pressBad, LOW);
 }
 else if (pressureRead > 501)
 {
 digitalWrite(pressBad, HIGH);
 digitalWrite(pressGood, LOW);

 }
if (cprCount == 30)
 { // 30:2 ratio for CPR, 30 total
 cprCount = 0; //restart count
 timeEnd = millis(); //capture end time for set
 //Serial.println(timeEnd);
 totalTime = (timeEnd - timeBegin) / 1000; //convert Ms to seconds
 Serial.print("Total Time= ");
 Serial.println(totalTime);
 bpmCount = (30.0 / totalTime); //bpmCount = float
 Serial.print("BPM Count= ");
 Serial.println(bpmCount);
 BPM = (bpmCount * 60.0);
 Serial.print("Total time in sec= ");
 Serial.println(totalTime);
 lcd.home();
 lcd.print("Rate (BPM)= ");
 lcd.setCursor(12, 0);
 lcd.print(BPM);
 Serial.print("BPM is= ");
 Serial.println(BPM);
 lcd.setCursor(0, 1);
 lcd.print("Total Time= ");
 lcd.setCursor(12, 1);
 lcd.print(totalTime);
 cprCycle++;
 Serial.print("CPR Cycle #= ");
 Serial.println(cprCycle);
 if (cprCycle == 5)
 {
 cprCycle = 0;
 }
 }
 if (cprCount > 1 && cprCount <= 30)
 {
 float rateTime = (millis() - timeBegin) / 1000; //changed int rateTime to
unsigned long
 //Serial.println(rateTime);
 int rate = (cprCount / rateTime) * 60; //changed int to unsigned int
 Serial.print("BPM is= ");
 Serial.println(rate);
 lcd.home();
 lcd.setCursor(0, 1);
 lcd.print("BPM IS= ");
 lcd.setCursor(10, 1);
 lcd.print(rate);
 if (rate >= 100 && rate <= 120)
 { //AHA guidelines 100-120 CPM
 lcd.setCursor(12, 0);
 lcd.print("Good");
}
else
{
lcd.setCursor(12, 0);
lcd.print("Bad");
}
}
delay(25);
lastButtonState = buttonState;
}
