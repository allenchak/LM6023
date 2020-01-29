//    
//      glcdlib.h
//      
//      Copyright 2010 joaquim <mail@joaquim.org>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#ifndef __GLCDLIB_H
#define __GLCDLIB_H

#include "stm8s.h"

/*********************************************************/
/*  Configuration for LCD panel specific configuration   */
/*********************************************************/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64


#define LCD_PIXEL_OFF   0
#define LCD_PIXEL_ON    1
#define LCD_PIXEL_INV   2
#define LCD_CHAR_INV       3

#define FONT_WIDTH      5
#define FONT_HEIGHT     5


/* Exported functions ------------------------------------------------------- */

void LCDInit(void);
void ClearScr(void);
void FillScr( u8 v );
void LcdSetPos( u16 x, u16 y );
void DrawPoint( u16 x, u16 y, u8 v );
void DrawLine(int x, int y, int x2, int y2, int v);
void DrawRectangle( u8 left, u8 top, u8 right, u8 bottom, u8 linestate );
u8 DrawChar5x5(u8 x, u8 y, char character, u8 v);
void DrawText(u8 x, u8 y, char str[], u8 v);

#endif /* __GLCDLIB_H */