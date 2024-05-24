#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 64
#define SIZE 8
#define LONGPLATFORM 3
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

class Platform {
  public:
  int xP;
  int yP;
  public:
  Platform(int coordXPlat, int coordYPlat){
    xP = coordXPlat;
    yP = coordYPlat;
  }

  void show() {
    for(int i = xP - LONGPLATFORM / 2 ; i < LONGPLATFORM; i++){
      setPixelColor(i, yP);
    }
  }
};  

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

  void move(Platform & platform1, Platform & platform2) {
    if (x >= SIZE - 1 || x <= 0) {
      spX *= -1;
    }
    if (y == platform1.yP + 1 && x >= platform1.xP - LONGPLATFORM / 2 && x < platform1.xP + LONGPLATFORM ) {
      spY *= -1;
    }
    if (y == platform2.yP - 1 && x >= platform2.xP - LONGPLATFORM / 2 && x < platform2.xP + LONGPLATFORM ) {
      spY *= -1;
    }
    x += spX;
    y += spY;
  }

  void show() {
    setPixelColor(x, y);
  }
};









Ball ball(1, 3, -1, 1);
Platform platform1(1, 0);
Platform platform2(1, SIZE - 1);

void setup() {
  strip.begin(); 
  
  // Serial.begin(9600); //-вывод переменной на экран
}

void loop() {
  strip.clear();

  ball.move(platform1, platform2);

  // draw ball
  ball.show();
  platform1.show();
  platform2.show();

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

