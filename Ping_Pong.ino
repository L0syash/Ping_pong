#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 256
#define SIZE 16
#define LONGPLATFORM 5
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Matrix ledMatrix(SIZE, SIZE);

void setPixelColor(int x, int y, int r, int g, int b) {
  if (y % 2 == 1) {
    int serialNumber = y * SIZE + x;
    strip.setPixelColor(serialNumber, strip.Color(r, g, b));
  } else {
    int serialNumber = y * SIZE + (SIZE - 1) - x;
    strip.setPixelColor(serialNumber, strip.Color(r, g, b));
  }
}

class Platform {
public:
  int xP;
  int yP;
public:
  Platform(int coordXPlat, int coordYPlat) {
    xP = coordXPlat;
    yP = coordYPlat;
  }

  void show() {
    for (int i = xP; i < xP + LONGPLATFORM; i++) {
      setPixelColor(i, yP, 0, 250, 0);
    }
  }

  void moveLeft() {
    if (xP < SIZE - LONGPLATFORM) {
      xP++;
    }
  }

  void moveRight() {
    if (xP > 0) {
      xP--;
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

  void move(Platform& platform1, Platform& platform2) {
    if (x >= SIZE - 1 || x <= 0) {
      spX *= -1;
    }
    if (y == platform1.yP + 1 && x >= platform1.xP - LONGPLATFORM / 2 && x <= platform1.xP + LONGPLATFORM) {
      spY *= -1;
    } else if (y == platform1.yP + 1) {
      gameover();
    }
    if (y == platform2.yP - 1 && x >= platform2.xP - LONGPLATFORM / 2 && x <= platform2.xP + LONGPLATFORM) {
      spY *= -1;
    } else if (y == platform2.yP - 1) {
      gameover();
    }
    x += spX;
    y += spY;
  }

  void show() {
    setPixelColor(x, y, 0, 0, 250);
  }
};


Ball ball(SIZE / 2, SIZE / 2, -1, -1);
Platform platform1(5, 0);
Platform platform2(5, SIZE - 1);

void gameover() {
  for(int i = 0; i <= SIZE; i++){
    for(int k = 0; k <= SIZE; k++){
      setPixelColor(i, k, 200, 0, 0);
    }
  }
  strip.show();
  delay(2000);
  strip.clear();
  ball.x = SIZE / 2;
  ball.y = SIZE / 2;
  ball.spX = -1;
  ball.spY = -1;
}






void setup() {
  strip.begin();
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  // Serial.begin(9600); //-вывод переменной на экран
}

void loop() {
  strip.clear();

  ball.move(platform1, platform2);

  // draw ball
  ball.show();
  platform1.show();
  platform2.show();




  int buttonStateR1 = digitalRead(2);
  int buttonStateL1 = digitalRead(3);
  int buttonStateR2 = digitalRead(4);
  int buttonStateL2 = digitalRead(5);

  if (buttonStateR1 == 1) {
    platform1.moveRight();
  }
  if (buttonStateL1 == 1) {
    platform1.moveLeft();
  }
  if (buttonStateR2 == 1) {
    platform2.moveLeft();
  }
  if (buttonStateL2 == 1) {
    platform2.moveRight();
  }

  //draw platform1
  //setPixelColor(platform1.x, platform1.y);
  //setPixelColor(platform1.x - 1, platform1.y);
  //setPixelColor(platform1.x + 1, platform1.y);

  strip.show();

  delay(250);
}
