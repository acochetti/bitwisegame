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
int answerDigits[8], firstBinary[8], secondBinary[8], resultBinary[8];
int x, operation, mask;
String opString;

unsigned long startTime, elapsedTime;
//unsigned int firstInt = 0, secretInt = 0, resultsInt = 0; //these will be generated from the arrays 
                                                          //and used for the actual bitwise arithmetic 
                                                          //so that we can reduce our reliance on for loops
                                                          //not being used yet

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(23));
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  //setup loop
  for(x = 0; x < 8; x++) {
    //mask = 1;
    pinMode(buttonPins[x], INPUT);
    
    firstBinary[x] = random(2); //assigns either a 0 or 1 to each index
    /*if (firstBinary[x]) {
      mask = mask << x;
      firstInt = firstInt | mask;
    }*/
    
    secondBinary[x] = random(2);
    /*if (secretBinary[x]){
      mask = mask << x;
      secretInt = secretInt | mask;
    }*/
  }
  
  operation = random(2); //assigns either a 0, representing AND, or a 1, representing OR, to the variable operation
  if (operation) {
    opString = "|";

    for(x = 0; x < 8; x++) {
      if(firstBinary[x] || secondBinary[x]) {
        resultBinary[x] = 1;
      } else {
        resultBinary[x] = 0;
      }
    }
  } else {
    opString = "&";

    for(x = 0; x < 8; x++) {
      if(firstBinary[x] && secondBinary[x]) {
        resultBinary[x] = 1;
      } else {
        resultBinary[x] = 0;
      }
    }
  }

  //resultsInt = firstInt | secretInt;  //we'll use arrays and for loops first to get the functionality in place

  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  startTime = millis();
  display.setCursor(0,0);

  
  
  for (x = 0; x < 8; x++) {
    buttonStates[x] = digitalRead(buttonPins[x]);
    
    if (buttonStates[x] == HIGH) {
      answerDigits[x] = 0;
    } else {
      answerDigits[x] = 1;
    }
    
  }
    
  display.clearDisplay();

  for(x = 0; x < 8; x++) {
    display.print(firstBinary[x]);
  }

  display.println();

  for(x = 0; x < 8; x++) {
    display.print(secondBinary[x]);
  }

  display.println(opString);

  for (x = 0; x < 8; x++) {
    display.print(answerDigits[x]);
  }  

  if (startTime >= 20000) {
    if (binaryCompare(answerDigits, resultBinary) == 0) {
      display.println("Correct!");
    } else {
      display.println("Incorrect!");
    }
  } else {
      display.println(startTime / 1000);
  }

  
  
  display.display();
  
  
}

int binaryCompare(int *answer, int *result) {
  int x;
  
  for(x = 0; x < 8; x++) {
    if(answer[x] != result[x]) {
      return 1;
    }
  }

  return 0;
}

