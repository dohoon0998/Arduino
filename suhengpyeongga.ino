#include <LiquidCrystal.h>
#include <Keypad.h>

#define ROWS 4
#define COLS 4

LiquidCrystal lcd{13, 12, 11, 10, 9, 8};
char customKey;
char keys[ROWS][COLS] = {                                                                                                                       
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {14, 15, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

double NUM1 = 0;
double NUM2 = 0;
double RESULT = 0;
char cal;

void setup() {
pinMode(14, OUTPUT);
pinMode(15, OUTPUT);

Serial.begin(9600);
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
}

void loop() {

customKey = customKeypad.getKey();
operation1();
Operator();
operation2();
Calculate();


if(customKey == '#')
{
  lcd.setCursor(0,2);
  lcd.print("= ");  
  lcd.print(RESULT);
}
}

void Cleaning()
{
NUM1 = 0;
NUM2 = 0;
RESULT = 0;
lcd.clear();
cal = NULL;
} 

long operation1()
{
  while(1) {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9') {
      NUM1= NUM1 * 10 + (customKey - '0');
     Serial.print("키값1 : ");
     Serial.println(customKey);
      lcd.print(customKey);
    }
    if(customKey == 'A') break;
    else if(customKey == 'B') break;
    else if(customKey == 'C') break;
    else if(customKey == 'D') break;
    else if(customKey == '*') Cleaning();

  }
  return NUM1;
}
long operation2()
{
  while(1) {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9') {
      NUM2 = NUM2  * 10 + (customKey - '0');
     // Serial.print("키값2 : ");
      //Serial.println(customKey);
      lcd.print(customKey);
  }
  if (customKey == '#') break;
  else if(customKey == '*') Cleaning();
}
return NUM2;
}
void Calculate() {
  switch(cal) {
    case 'A':
    RESULT = NUM1 + NUM2;
   // Serial.print("+ : ");
   // Serial.println(RESULT);
    break;
    case 'B':
    RESULT = NUM1 - NUM2;
    break;
    case 'C':
    RESULT = NUM1 * NUM2;
    break;
    case 'D':
    RESULT = NUM1 / NUM2;
    break;
  }
}

void Operator()
{
  switch(customKey) {
    customKey = customKeypad.getKey();
    case 'A':
    lcd.print("+");
    cal = 'A';
    break;
    case 'B':
    lcd.print("-");
    cal = 'B';
    break;
    case 'C':
    lcd.print("*");
    cal = 'C';
    break;
    case 'D':
    lcd.print("/");
    cal = 'D';
    break;
  }
}
