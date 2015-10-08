#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const int buttonPin1 = 2;
int buttonState1 = 0;

const int buttonPin2 = 3;
int buttonState2 = 0;

const int buttonPin3 = 4;
int buttonState3 = 0;

const int buttonPin4 = 5;
int buttonState4 = 0;
String str1, str2, str3, str4;

void setup() {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  //display.print("donuts");
  //display.display();
  

}

void loop() {
  
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  
  display.setCursor(0,0);
  
  if (buttonState1 == HIGH) {
    str1 = "0";
  } else {
    str1 = "1";
  }
  if (buttonState2 == HIGH) {
    str2 = "0";
  } else {
    str2 = "1";
  }
  if (buttonState3 == HIGH) {
    str3 = "0";
  } else {
    str3 = "1";
  }
  if (buttonState4 == HIGH) {
    str4 = "0";
  } else {
    str4 = "1";
  }
  display.clearDisplay();
  display.print(str1 + str2 + str3 + str4);
  display.display();
  
}
