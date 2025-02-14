code1
#include <Arduino.h>
#include <LiquidCrystal.h>

// put function declarations here:
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int potPin = A1;

void setup() {
    lcd.begin(16, 2);
    lcd.print("ADC Test Ready!");
    delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
    int adcValue = analogRead(potPin);
    float voltage = adcValue * (0.5/1023.0);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ADC: ");
    lcd.print(adcValue);

    lcd.setCursor(0, 1);
    lcd.print("Voltage: ");
    lcd.print(Voltage, 2);
    lcd.print("V");

    delay(500);
}


code2
#include <Arduino.h>
#include <LiquidCrystal.h>

// put function declarations here:
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int buttonPin = A0;

String getButton(int adcValue){
    if (adcValue < 50) return "RIGHT";
    if (adcValue < 150) return "UP";
    if (adcValue < 300) return "DOWN";
    if (adcValue < 500) return "LEFT";
    if (adcValue < 800) return "SELECT";
    return "NONE";
}

void setup() {
    lcd.begin(16, 2);
    lcd.print("ADC Test Ready!");
    delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
    int adcValue = analogRead(potPin);
    float voltage = adcValue * (0.5/1023.0);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ADC: ");
    lcd.print(adcValue);

    lcd.setCursor(0, 1);
    lcd.print("Voltage: ");
    lcd.print(Voltage, 2);
    lcd.print("V");

    delay(500);
}

 code1.2
 #include <Arduino.h>
#include <LiquidCrystal.h>


// put function declarations here:
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int analongPin = A0;
int digital_val = 0;
float analong_val;
const int potPin = A1;

void setup() {
    lcd.begin(16, 2);
    lcd.print("Valentine's day ");
    lcd.setCursor(0, 1);
    lcd.print("     <baby> ");
    delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
    digital_val = analogRead(potPin);
    analong_val = digital_val * (5.0/1023.0);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("digital: ");
    lcd.print(digital_val);

    lcd.setCursor(0, 1);
    lcd.print("analong: ");
    lcd.print(analong_val);
    lcd.print("V");

    delay(250);
}


test1
#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
const int analogpin = A0;
int currentMenu = 0;
const int menuNo = 4;
String menuItems[menuNo] = {"Fan Speed", "Temperature", "Humidity",
"Blood Pressure"};
//String stores menu items
 
int menuValues[menuNo] = {30, 55, 70, 220};

String getButton(int analogValue) {
if (analogValue < 50) return "RIGHT";
if (analogValue < 150) return "UP";
if (analogValue < 300) return "DOWN";
if (analogValue < 500) return "LEFT";
if (analogValue < 800) return "SELECT";
return "NONE";
}

void displayMenu() {
lcd.clear ();
lcd.setCursor(0, 0);
lcd.print ("Menu:");
lcd.setCursor(0, 1);
lcd.print (menuItems[currentMenu]);
}

void displaySubMenu() {
lcd.clear ();
lcd.setCursor(0, 0);
lcd.print (menuItems[currentMenu]);
lcd.setCursor(0, 1);
lcd.print("Value: " + String(menuValues[currentMenu]));
}


void setup() {
lcd.begin(16, 2);
lcd.print ("Menu Navigation");
delay (2000) ;
lcd.clear ();
displayMenu ( ) ;
}


void loop() {
  int analogValue = analogRead (analogpin);
  String button = getButton (analogValue);
//User interface section
//using button "UP" to go up selections
//decreasing count to go down selections
if (button == "UP") {
currentMenu = (currentMenu - 1+ menuNo) % menuNo;
displayMenu ();
delay (500) ;
 } else if (button == "DOWN") {
currentMenu = (currentMenu + 1) & menuNo;
displayMenu () ;
delay (500);
} else if (button =="SELECT") {
displaySubMenu ();
// Show the sub-menu when SELECT is pressed
delay (500);
// Sub-menu interaction to modify the value
 

while (true) {
analogValue = analogRead(analogpin);
button = getButton(analogValue);
if (button == "UP") {
//menuValues[currentMenu]+++;
displaySubMenu();
delay (2000) ;
 } else if (button == "DOWN") {
//menuValues[currentMenu]---;
displaySubMenu ();
delay (2000) ;
  } else if (button == "LEFT") {
displayMenu(); // Return to the main menu
delay (2000) ;
break;
     }
   }
  }
}

test1.2
#include <Arduino.h>
#include <LiquidCrystal.h>

// กำหนดขาของ LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// กำหนดขาสำหรับอ่านค่าปุ่มกด
const int buttonPin = A0;

// ค่าตัวอย่าง (สามารถต่อ Load Cell เพื่อใช้ค่าจริงได้)
float weight = 70.5;
float muscleMass = 30.2;
float fatMass = 15.8;
float bmr = 1600;

// ตำแหน่งของตัวเลขที่เลือก
int cursorX = 3;  // เริ่มที่ "1"
int cursorY = 0;  // แถวบน
bool isBlinking = false; // สถานะกระพริบ
bool inSubMenu = false; // อยู่ในเมนูย่อยหรือไม่

// ฟังก์ชันตรวจจับปุ่มกด
int getButtonValue(int adcValue) {
    if (adcValue < 50) return 1;   // RIGHT
    if (adcValue < 150) return 2;  // UP
    if (adcValue < 300) return 3;  // DOWN
    if (adcValue < 500) return 4;  // LEFT
    if (adcValue < 800) return 5;  // SELECT
    return 0;
}

// ฟังก์ชันแสดงเมนูหลัก
void showMainMenu(bool blink = false) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("[ ");

    lcd.setCursor(3, 0);
    if (cursorX == 3 && cursorY == 0 && blink) lcd.print(" ");
    else lcd.print("1");

    lcd.setCursor(6, 0);
    if (cursorX == 6 && cursorY == 0 && blink) lcd.print(" ");
    else lcd.print("2");

    lcd.setCursor(8, 0);
    lcd.print(" ]");

    lcd.setCursor(1, 1);
    lcd.print("[ ");

    lcd.setCursor(3, 1);
    if (cursorX == 3 && cursorY == 1 && blink) lcd.print(" ");
    else lcd.print("3");

    lcd.setCursor(6, 1);
    if (cursorX == 6 && cursorY == 1 && blink) lcd.print(" ");
    else lcd.print("4");

    lcd.setCursor(8, 1);
    lcd.print(" ]");
}

// ฟังก์ชันแสดงเมนูย่อย
void showSubMenu(int menu) {
    lcd.clear();
    lcd.setCursor(0, 0);
    
    switch (menu) {
        case 1: lcd.print("Weight: "); lcd.print(weight); lcd.print(" kg"); break;
        case 2: lcd.print("Muscle: "); lcd.print(muscleMass); lcd.print(" kg"); break;
        case 3: lcd.print("Fat: "); lcd.print(fatMass); lcd.print(" kg"); break;
        case 4: lcd.print("BMR: "); lcd.print(bmr); lcd.print(" kcal"); break;
    }
    lcd.setCursor(0, 1);
    lcd.print("Press SELECT Back");
}

void setup() {
    lcd.begin(16, 2);
    showMainMenu();
}

void loop() {
    int adcValue = analogRead(buttonPin);
    int buttonValue = getButtonValue(adcValue);

    if (!inSubMenu) {
        // อัปเดตตำแหน่งตามปุ่มที่กด
        if (buttonValue == 1 && cursorX == 3) cursorX = 6; // RIGHT (3 → 6)
        if (buttonValue == 4 && cursorX == 6) cursorX = 3; // LEFT (6 → 3)
        if (buttonValue == 2 && cursorY == 1) cursorY = 0; // UP (1 → 0)
        if (buttonValue == 3 && cursorY == 0) cursorY = 1; // DOWN (0 → 1)

        // กระพริบตัวเลขที่เลือก
        isBlinking = !isBlinking;
        showMainMenu(isBlinking);

        // กด SELECT -> แสดงเมนูย่อย
        if (buttonValue == 5) {
            inSubMenu = true;
            int menu = (cursorY == 0) ? ((cursorX == 3) ? 1 : 2) : ((cursorX == 3) ? 3 : 4);
            showSubMenu(menu);
            delay(500);
        }
    } else {
        // กด SELECT ในเมนูย่อย -> กลับหน้าหลัก
        if (buttonValue == 5) {
            inSubMenu = false;
            showMainMenu();
            delay(500);
        }
    }

    delay(300);
}

