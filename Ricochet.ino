#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 64
#define SIZE 8
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Matrix ledMatrix(SIZE, SIZE);

void setPixelColor(int x, int y) {
    if (y%2==1){
      int serialNumber =  y * SIZE + x;
      strip.setPixelColor(serialNumber, strip.Color(0, 250, 0));
    }
    else {
      int serialNumber = y * SIZE + (SIZE - 1) - x; 
      strip.setPixelColor(serialNumber, strip.Color(0, 250, 0));
    }
}

class Ball {
public:
  int x;
  int y;
  int spX;
  int spY;
public:
  Ball(int coordX, int coordY, int speedX, int speedY) {
    setPosition(coordX, coordY);
    spX = speedX;
    spY = speedY;
    
  }

  void setPosition(int coordX, int coordY) {
    x = coordX;
    y = coordY;
  }

  void move() {
    if (x >= SIZE - 1 || x <= 0) {
      spX *= -1;
    }
    if (y >= SIZE - 1 || y <= 0) {
      spY *= -1;
    }
    x += spX;
    y += spY;
  }
};

Ball ball(1, 3, -1, 1);

void setup() {
  strip.begin(); 
  
  // Serial.begin(9600); //-вывод переменной на экран
}

void loop() {
  strip.clear();

  ball.move();

  // draw ball
  setPixelColor(ball.x, ball.y);

   //draw platform1
  //setPixelColor(platform1.x, platform1.y);
  //setPixelColor(platform1.x - 1, platform1.y);
  //setPixelColor(platform1.x + 1, platform1.y);

  strip.show();

  delay(500);  
}
//   if (yBall <= 7){
//     yBall = yBall++;
//     //Serial.println(yBall);
//     if (yBall%2==1){
//       int serialNumber =xBall * SIZE + yBall;
//       strip.setPixelColor(serialNumber, strip.Color(250, 250, 250));
//       strip.show();
//     }
//     else {
//       int serialNumber = SIZE*xBall+(SIZE-1)-yBall; 
//       strip.setPixelColor(serialNumber, strip.Color(250, 250, 250));
//       strip.show();
//     }
//     delay(50);
//   }
// }
/*if (yBall%2==1){
    int serialNumber =xBall * size + yBall;
    strip.setPixelColor(serialNumber, strip.Color(250, 0, 0));
    strip.show();
  }
  else {
    int serialNumber = size*xBall+(size-1)-yBall; 
    strip.setPixelColor(serialNumber, strip.Color(250, 0, 0));
    strip.show();
  }
*/

