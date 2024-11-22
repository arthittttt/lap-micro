#include <Arduino.h>

const int buttonpin = 2;
const int redpin = 8;
const int yellowpin = 9;
const int greenpin = 10;
void updateTrafficLights();

int buttonState = 0;
int lastButtonState = 0;
int trafficState = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(redpin, OUTPUT);
  pinMode(yellowpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(buttonpin, INPUT);
  digitalWrite(redpin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonpin);
  if (reading != lastButtonState){
    lastDebounceTime = millis();

  } 
  if ((millis()-lastDebounceTime)>debounceDelay) {
  if (reading !=buttonState)
  {buttonState = reading;
  if (buttonState == HIGH)
  { trafficState = (trafficState + 1) % 3 ;
    updateTrafficLights();
  
  }
  
}
  
  }
  
  
    
  lastButtonState = reading;
}
void updateTrafficLights(){
  digitalWrite(redpin,LOW);
  digitalWrite(yellowpin,LOW);
  digitalWrite(greenpin,LOW);
  switch (trafficState) {
  case 0:
   digitalWrite(redpin, HIGH);
    break;
  case 1:
    digitalWrite(greenpin, HIGH);
    break;
  case 2:
   digitalWrite(yellowpin, HIGH);
   break;
  }
}

