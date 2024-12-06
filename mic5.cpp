#include <Arduino.h>
#include <TM1638plus.h>
#define STB 10
#define CLK 9
#define DIO 8

TM1638plus disp(STB, CLK, DIO);

int firstoperand = 0;
int secondoperand = 0;
char operation = '\0';
bool isSecondOperand = false;
bool clearFlag = false;

void setup() {
disp.displayBegin();
disp.reset();
}

void loop() {

byte buttons = disp.readButtons(); 
if (buttons & 0b10000000) {
   firstoperand = 0;
   secondoperand = 0;
   operation = '\0';
   isSecondOperand = false;
   disp.displayText("CLEAR");
 // Display "CLEAR" message
   delay(500);
   disp.reset();
  return;
}

for (int i=0; i < 4; i++) {
  if (buttons & (1 << i)) {
  int num = i+1; // Numbers 1-4
  if (!isSecondOperand) {
    firstoperand = firstoperand * 10 + num;
    disp.displayIntNum(firstoperand, false); 

  } else {
    secondoperand = secondoperand * 10 + num;
    disp.displayIntNum (secondoperand, false); // Display the second operand
  }
  delay(300); // Debounce delay
 }
}

if(buttons & 0b00100000) {
  operation = '+';
  isSecondOperand = true;
  disp.displayText("PLUS"); // Display operation
  delay(500);
}

if (buttons & 0b01000000){// Button 6 for Subtraction
  operation = '-';
  isSecondOperand = true;
  disp.displayText("MINUS"); // Display operation
  delay(500);
}
// Equals button (Button 7)

if (buttons & 0b00010000){
int result = 0;

// Perform the selected operation
if (operation == '+') {
  result = firstoperand + secondoperand; } 
else if (operation =='-') {
  result = firstoperand - secondoperand;
}
// Display the result tm.displayIntNum(result, false);
disp.displayIntNum(result,false);
// Reset variables for a new calculation

firstoperand = result;
secondoperand = 0;
operation= '\0'; 
isSecondOperand = false;
delay(1000); // wait
}
}



