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

const int buttonPins[8] = {6, 7, 8, 14, 5, 4, 3, 2};
int buttonStates[8] = { };
String binaryDigits[8];

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  for(int x = 0; x < 8; x++) {
    pinMode(buttonPins[x], INPUT);
  }
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  display.setCursor(0,0);
  
  for (int x = 0; x < 8; x++) {
    buttonStates[x] = digitalRead(buttonPins[x]);
    
    if (buttonStates[x] == HIGH) {
      binaryDigits[x] = "0";
    } else {
      binaryDigits[x] = "1";
    }
    
  }
    
  display.clearDisplay();
  
  for (int x = 0; x < 8; x++) {
    display.print(binaryDigits[x]);
  }
  
  display.display();
  
}
