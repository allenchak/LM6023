# LM6023
TOPWAY LM6023 is 128x64 LCD display using S1D15300 controller, accepting 8080, 6800 and serial interface.
I would like say thankyou to ladyada, because this library based on [ST7565-LCD](https://github.com/adafruit/ST7565-LCD/) version.


## Important Notes
- Strongly recommended using Hardware SPI, have a significant speed up, up to 93% faster than software SPI.
- Do *NOT* recommended enable the flag `enablePartialUpdate` but Hardware SPI, there are wasting 4 Bytes SRAM.


## How to use
* `S1D15300 glcd(LCD_A0, LCD_RST, LCD_CS);`
* `glcd.begin(16);` // initialize and set the contrast to 16 (Range: 0-31)
* `glcd.display();` // show splashscreen


## Demo video
[![LM6023 function test](https://img.youtube.com/vi/LYUDzZLhVGs/0.jpg)](https://www.youtube.com/watch?v=LYUDzZLhVGs "LM6023 function test")


## Pinout
| Pin | Description | Arduino HW SPI | Arduino |
| --- | --- | --- | --- |
| 1 | VSS | GND | GND |
| 2 | VDD | 3.3v | 3.3v |
| 3 | /RES | D6 | D6 |
| 4 | P/S | GND | GND |
| 5 | /CS1 | D5 (or GND) | D5 (or GND) |
| 6 | CS2 | 3.3v | 3.3v |
| 7 | C86 | NC | NC |
| 8 | A0 | D7 | D7 |
| 9 | /WR (R/W) | NC | NC |
| 10 | /RD (E) | NC | NC |
| 11 | DB0 | NC | NC |
| 12 | DB1 | NC | NC |
| 13 | DB2 | NC | NC |
| 14 | DB3 | NC | NC |
| 15 | DB4 | NC | NC |
| 16 | DB5 | NC | NC |
| 17 | DB6 (SCL) | D13 | D8 |
| 18 | DB7 (SI) | D11 | D9 |
| 19 | BLA | 3.3v | 3.3v |
| 20 | BLK | D4* | D4* |

Remark \*: with 1K ohm and NPN to GND


## Schematic
![](https://github.com/allenchak/LM6023/blob/master/resources/LM6023.png?raw=true)


## TODO
- More detail of this readme file
- Test and allow to config the SPI clock speed
