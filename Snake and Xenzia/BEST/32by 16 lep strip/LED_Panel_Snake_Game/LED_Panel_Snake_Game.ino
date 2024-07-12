/*
   Version 1.0 August, 2021
   Copyright (c) 2021 Korneel Verraes
   https://lego-projecten.webnode.nl/

   LED Panel Snake Game:
   A joystick  with analog output VRx and VRy is respectively connected to pin A3 and A4
   An  LED Panel 16x32 is connected according to the general scheme (see: https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/new-wiring)

   Accompanying video: https://youtu.be/G16ej5IbYTQ
*/

#include <RGBmatrixPanel.h>

//#define  CLK  8  // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4  // USE THIS ON METRO M4 (not M0)
#define CLK 11    // USE THIS ON ARDUINO MEGA
#define  OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

#define  F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

const int VRx =  A3;
const int VRy = A4;
const char str[] PROGMEM = "GAME OVER";
const  char str2[] PROGMEM = "YOUR SCORE WAS:";

int xPosition = 0;
int yPosition  = 0;
int mapX = 0;
int mapY = 0;

//snake start x-coordinates
int  x[512] = {5, 4, 3, 2};

//snake start y-coordinates
int y[512] = {7, 7,  7, 7};
int snakeDirection = 0;
int lastDirection = 0;

//snake start  length
int snakeLength = 4;
boolean food = false;
int foodX = 0;
int  foodY = 0;
unsigned long previousTime = 0;
int score = 0;

//declare  a lower value to make the snake move faster
int difficulty = 150;

RGBmatrixPanel  matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  Serial.begin(9600);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.fillScreen(0);

  //to make sure that totally random food is generated,  A15 is a disconnected pin!
  randomSeed(analogRead(A15));
}

void loop()  {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  mapX  = map(xPosition, 0, 1023, -10, 10);
  mapY = map(yPosition, 0, 1023, -10, 10);
  if (mapX > 4 && lastDirection != 2) snakeDirection = 1;
  if (mapX < -4 &&  lastDirection != 1) snakeDirection = 2;
  if (mapY < -4 && lastDirection != 4)  snakeDirection = 3;
  if (mapY > 4 && lastDirection != 3) snakeDirection = 4;

  //turn off the last pixel
  matrix.drawPixel(x[snakeLength - 1], y[snakeLength  - 1], matrix.Color333(0, 0, 0));
  if (millis() - previousTime >= difficulty)  {
    //snake moves right
    if (snakeDirection == 1) {
      //check  if the snake doesn't exceed the right edge
      if (x[0] == 31) {
        gameOver();
        return;
      }
      snakeCalculator();
      x[0]++;
    }
    //snake moves left
    if (snakeDirection == 2) {
      //check if the  snake doesn't exceed the left edge
      if (x[0] == 0) {
        gameOver();
        return;
      }
      snakeCalculator();
      x[0]--;
    }
    //snake moves down
    if (snakeDirection == 3) {
      //check if the  snake doesn't exceed the bottom edge
      if (y[0] == 0) {
        gameOver();
        return;
      }
      snakeCalculator();
      y[0]--;
    }
    //snake moves up
    if (snakeDirection == 4) {
      //check if the snake  doesn't exceed the top edge
      if (y[0] == 15) {
        gameOver();
        return;
      }
      snakeCalculator();
      y[0]++;
    }
    lastDirection = snakeDirection;
    previousTime = millis();
  }

  //the snake is generated here
  for (int i = 0; i < snakeLength; i++) {
    matrix.drawPixel(x[i], y[i], matrix.Color333(0, 7, 0)); //green
  }

  //check if the snake eats food
  if (foodX == x[0] && foodY == y[0]) {
    snakeLength++;
    food = false;
  }

  //check if there is food  on the display
  if (food == false) foodGenerator();

  //check if the  snake doesn't touch himself
  for (int i = 1; i < snakeLength; i++) {
    if  (x[0] == x[i] && y[0] == y[i]) gameOver();
  }
}

//calcultate the new  coordinates
void snakeCalculator() {
  for (int i = snakeLength; i > 0; i--)  {
    //shift every x-coordinate in the array
    x[i] = x[i - 1];
  }
  for (int i = snakeLength; i > 0; i--) {
    //shift every y-coordinate in the  array
    y[i] = y[i - 1];
  }
}

//generate food in random places
void  foodGenerator() {
  foodX = random(32);
  foodY = random(16);

  //check  if food isn't generated on the snake, otherwise try again (return)
  for (int  i = 0; i < snakeLength; i++) {
    if (foodX == x[i] && foodY == y[i]) return;
  }
  matrix.drawPixel(foodX, foodY, matrix.Color333(7, 0, 0)); //red
  food  = true;
}

//game over screen
void gameOver() {
  //blink the current  snake and food position 5 times
  for (int j = 0; j < 5; j++) {
    matrix.fillScreen(0);
    delay(200);
    for (int i = 0; i < snakeLength; i++) {
      matrix.drawPixel(x[i],  y[i], matrix.Color333(0, 7, 0)); //green
    }
    matrix.drawPixel(foodX,  foodY, matrix.Color333(7, 0, 0)); //red
    delay(200);
  }

  //scroll  "GAME OVER" over the display
  for (int i = 31; i > -120; i--) {
    matrix.fillScreen(0);
    matrix.setTextSize(2);
    matrix.setCursor(i, 1);
    matrix.setTextColor(matrix.Color333(7,  2, 0)); //orange
    matrix.print(F2(str));
    delay(10);
  }

  //scroll "YOUR SCORE WAS" over the display
  for (int i = 31; i > -192; i--)  {
    matrix.fillScreen(0);
    matrix.setTextSize(2);
    matrix.setCursor(i,  1);
    matrix.setTextColor(matrix.Color333(7, 2, 0)); //orange
    matrix.print(F2(str2));
    delay(10);
  }
  scoreCalculator();
  delay(5000);
  newGame();
}

//calculate  your score
void scoreCalculator() {
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7,  2, 0)); //orange

  //if the score exists of only 1 digit
  if (snakeLength  / 10 == 0) {
    matrix.setCursor(13, 4);
    matrix.print(snakeLength);
  }

  //if the score exists of 2 digits
  else if (snakeLength / 100 ==  0) {
    matrix.setCursor(10, 4);

    //separate the first digit and display
    matrix.print(snakeLength / 10);
    matrix.setCursor(17, 4);

    //separate  the second digit and display
    matrix.print(snakeLength % 10);
  }

  //if the score exists of 3 digits
  else {
    //separate the first digit  and display
    score = snakeLength / 100;
    snakeLength -= score * 100;
    matrix.setCursor(7, 4);
    matrix.print(score);

    //separate the  second digit and display
    score = snakeLength / 10;
    snakeLength -=  score * 10;
    matrix.setCursor(13, 4);
    matrix.print(score);

    //separate the third digit and display
    score = snakeLength;
    matrix.setCursor(19,  4);
    matrix.print(score);
  }
}

//reset all variables to start  a new game
void newGame() {
  matrix.fillScreen(0);
  x[0] = 5; x[1] =  4; x[2] = 3; x[3] = 2;
  y[0] = 7; y[1] = 7; y[2] = 7; y[3] = 7;
  snakeDirection  = 0;
  lastDirection = 0;
  snakeLength = 4;
  food = false;

  //  to make sure that totally random food is generated, A15 is a disconnected pin!
  randomSeed(analogRead(A15));
}
