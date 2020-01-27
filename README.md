# LM6023
TOPWAY LM6023 128x64 LCD Display

## Pinout
| Pin | Description | Arduino | Arduino HW SPI |
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
| 17 | DB6 (SCL) | D8 | D13 |
| 18 | DB7 (SI) | D9 | D11 |
| 19 | BLA | 3.3v | 3.3v |
| 20 | BLK | D4* | D4* |

Remark *: with 1K ohm and NPN to GND

## TODO
- more detail of this readme file
- schematic
- detail of the CD4050 & NPN schematic
- hardware SPI
