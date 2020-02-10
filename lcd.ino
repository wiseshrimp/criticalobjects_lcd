/*
  LiquidCrystal Library - Hello World
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 This sketch prints "Hello World!" to the LCD
 and shows the time.
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

String textArr[] = {
   "MTA criminalizespoverty           ",
   "Go! We paid:    $249,000,000   ",
   "Don't snitch,   swipe               ",
   "Arrested for    $2.75             "
};

#define LIGHT_SENSOR_PIN 0

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int photocellReading;
int period = 7000;
bool isTriggered = false;
int lightThreshold = 1;
int idx = 0;
unsigned long time_now = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  photocellReading = analogRead(LIGHT_SENSOR_PIN); 
  int len = sizeof(textArr) / sizeof(textArr[0]);
      Serial.println(photocellReading);


  if (photocellReading > lightThreshold && !isTriggered) {
    isTriggered = true;
  }
  
  if (isTriggered) {
    int lengthOfArr = textArr[idx].length() > 16 ? 32 : textArr[idx].length();
    float space = (16 - textArr[idx].length()) / 2;
    int offset = round(space);
    lcd.setCursor(offset, 0); // Centers the text
    lcd.print(textArr[idx]);
    if (textArr[idx].length() > 16) {
      lcd.clear();
      lcd.setCursor(0, 0);
      String text = textArr[idx];

      String str1 = text.substring(0, 16);

      lcd.print(str1);
      String str = text.substring(16, 32);
      float spaceSecond = (16 - str.length()) / 2;
      int offsetSecond = round(spaceSecond);
      lcd.setCursor(offsetSecond, 1);
      lcd.print(str);
    }
    delay(7000);
    idx = (idx == len - 1) ? 0 : idx + 1;

    isTriggered = false;
    lcd.clear();
  }
}
