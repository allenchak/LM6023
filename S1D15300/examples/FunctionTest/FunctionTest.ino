
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

//S1D15300 glcd(9, 8, 7, 6, 5); //Software SPI
S1D15300 glcd(7, 6, 5); // Hardware SPI with CS
//S1D15300 glcd(-1, -1, 7, 6, 5); // Hardware SPI with CS
//S1D15300 glcd(7, 6); // Hardware SPI without CS

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

// a bitmap of a 16x16 fruit icon
const static unsigned char __attribute__ ((progmem)) logo16_glcd_bmp[]={
0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0x30, 0xf8, 0xbe, 0x9f, 0xff, 0xf8, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 
0x20, 0x3c, 0x3f, 0x3f, 0x1f, 0x19, 0x1f, 0x7b, 0xfb, 0xfe, 0xfe, 0x07, 0x07, 0x07, 0x03, 0x00, };

// the buffer for the image display
extern uint8_t s1d15300_buffer[1024];

// The setup() method runs once, when the sketch starts
void setup(){
  Serial.begin(115200);

#ifdef __AVR__
  Serial.print(freeRam());
#endif

  pinMode(BACKLIGHT_LED, OUTPUT);
  digitalWrite(BACKLIGHT_LED, LOW);
  
  // initialize and set the contrast
  glcd.begin(16); //0-31


  glcd.display(); // show splashscreen
  delay(2000);
  glcd.clear();

  //print all char and symbol
  testdrawAllChars();

  // draw a single pixel
  glcd.setpixel(10, 10, BLACK);
  glcd.display();        // show the changes to the buffer
  delay(2000);
  glcd.clear();
  
  //draw single line
  glcd.drawline(0, 0, 63, 63, BLACK);
  glcd.drawstring(16, 0, "1");
  glcd.display();
  delay(2000);
  glcd.clear();

  //draw single line
  glcd.drawline(32, 0, 95, 63, BLACK);
  glcd.drawstring(16, 0, "2");
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw many lines
  testdrawline();
  glcd.display();       // show the lines
  delay(2000);
  glcd.clear();

  // draw rectangles
  testdrawrect();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw multiple rectangles
  testfillrect();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw mulitple circles
  testdrawcircle();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw a black circle, 10 pixel radius, at location (32,32)
  glcd.fillcircle(32, 32, 10, BLACK);
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw the first ~120 characters in the font
  testdrawchar();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw a string at location (0,0)
  glcd.drawstring(0, 0, "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation");
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}


void loop()                     
{}

#ifdef __AVR__
// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void)
{
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 
#endif

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
  randomSeed(666);     // whatever seed
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(128);
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      glcd.drawbitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, BLACK);
    }
    glcd.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      glcd.drawbitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, 0);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > 64) {
  icons[f][XPOS] = random(128);
  icons[f][YPOS] = 0;
  icons[f][DELTAY] = random(5) + 1;
      }
    }
  }
}


void printHead(int c, char line){
  switch(c){
    case 0:   glcd.drawstring(0, line, "0x00"); break;
    case 16:  glcd.drawstring(0, line, "0x10"); break;
    case 32:  glcd.drawstring(0, line, "0x20"); break;
    case 48:  glcd.drawstring(0, line, "0x30"); break;
    case 64:  glcd.drawstring(0, line, "0x40"); break;
    case 80:  glcd.drawstring(0, line, "0x50"); break;
    case 96:  glcd.drawstring(0, line, "0x60"); break;
    case 112: glcd.drawstring(0, line, "0x70"); break;
    
    case 128: glcd.drawstring(0, line, "0x80"); break;
    case 144: glcd.drawstring(0, line, "0x90"); break;
    case 160: glcd.drawstring(0, line, "0xA0"); break;
    case 176: glcd.drawstring(0, line, "0xB0"); break;
    case 192: glcd.drawstring(0, line, "0xC0"); break;
    case 208: glcd.drawstring(0, line, "0xD0"); break;
    case 224: glcd.drawstring(0, line, "0xE0"); break;
    case 240: glcd.drawstring(0, line, "0xF0"); break;
  }
  glcd.drawchar(24, line, 26);
}

void testdrawAllChars(void){
  char line = 0;
  for(char s=0; s < 4; s++){
    line = 0;
    for(int c=((s%2)*128); c<(((s%2)+1)*128); c++){
      printHead(c, line);
      glcd.drawchar(((c%16) * 6) + 30, line, c);
      
      if(c > 0 && (c+1)%16==0)
          line++;
    }
    digitalWrite(BACKLIGHT_LED, (s<2 ? HIGH : LOW) ); //Backlight ON and OFF
    
    glcd.display();
    delay(2000);
    glcd.clear(); 
  }
}

void testdrawchar(void) {
  for (uint8_t i=0; i < 168; i++) {
    glcd.drawchar((i % 21) * 6, i/21, i);
  }    
}

void testdrawcircle(void) {
  for (uint8_t i=0; i<64; i+=2) {
    glcd.drawcircle(63, 31, i, BLACK);
  }
}


void testdrawrect(void) {
  for (uint8_t i=0; i<64; i+=2) {
    glcd.drawrect(i, i, 128-i, 64-i, BLACK);
  }
}

void testfillrect(void) {
  for (uint8_t i=0; i<64; i++) {
      // alternate colors for moire effect
    glcd.fillrect(i, i, 128-i, 64-i, i%2);
  }
}

void testdrawline() {
  for (uint8_t i=0; i<128; i+=4) {
    glcd.drawline(0, 0, i, 63, BLACK);
  }
  for (uint8_t i=0; i<64; i+=4) {
    glcd.drawline(0, 0, 127, i, BLACK);
  }

  glcd.display();
  delay(1000);

  for (uint8_t i=0; i<128; i+=4) {
    glcd.drawline(i, 63, 0, 0, WHITE);
  }
  for (uint8_t i=0; i<64; i+=4) {
    glcd.drawline(127, i, 0, 0, WHITE);
  }
}