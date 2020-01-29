
#include <S1D15300.h>
#include <glcdfont.c>

#define BACKLIGHT_LED  4

// D9 - Serial data out (SID), Pin 18
// D8 - Serial clock out (SCLK), Pin 17
// D7 - Data/Command select (RS or A0), Pin 8
// D6 - LCD reset (RST), Pin 3
// D5 - LCD chip select (CS), Pin 5
// GND - LCD P/S (Interface), Pin 4
// 3v3 - LCD CS2, Pin 6
S1D15300 glcd(9, 8, 7, 6, 5);

// the buffer for the image display
extern uint8_t s1d15300_buffer[1024];

// The setup() method runs once, when the sketch starts
void setup(){
  //Serial.begin(115200);
  pinMode(BACKLIGHT_LED, OUTPUT);
  digitalWrite(BACKLIGHT_LED, LOW);
  
  // initialize and set the contrast
  glcd.begin(16); //0-31

  glcd.display(); // show splashscreen
  delay(3000);
  glcd.clear();
  
  glcd.drawstring(0, 0, "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation");
  glcd.display();
}

void loop()
{
  digitalWrite(BACKLIGHT_LED, HIGH);
  delay(3000);
  digitalWrite(BACKLIGHT_LED, LOW);
  delay(1000);
}
