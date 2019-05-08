//    
//        glcdlib.c
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

#include "glcdlib.h"
#include "stdlib.h"
#include "stdbool.h"

// Font 5x5 ( variable width, max 5px )
const u8 Font5x5[] = {
0,                 // Code for char Espaço   
23,             // Code for char !  
3,0,3,             // Code for char "  
10,31,10,31,10, // Code for char #  
4,14,27,10,     // Code for char $  
9,4,2,9,         // Code for char %  
10,21,17,         // Code for char &  
3,4,             // Code for char '  
14,27,17,         // Code for char (  
17,27,14,         // Code for char )  
21,14,14,21,     // Code for char *  
4,14,4,         // Code for char +  
16,8,             // Code for char ,  
4,4,4,             // Code for char -  
16,             // Code for char .  
16,12,3,         // Code for char "/"  
31,17,31,         // Code for char 0  
18,31,16,         // Code for char 1  
25,21,18,         // Code for char 2  
17,21,14,         // Code for char 3  
14,8,30,         // Code for char 4  
23,21,9,         // Code for char 5  
31,21,29,         // Code for char 6  
18,10,6,         // Code for char 7  
10,21,10,         // Code for char 8  
23,21,31,         // Code for char 9  
10,             // Code for char :  
16,10,             // Code for char ;  
4,10,17,         // Code for char <  
10,10,10,         // Code for char =  
17,10,4,         // Code for char >  
1,21,2,         // Code for char ?  
14,19,22,         // Code for char @  
30,9,30,         // Code for char A  
31,21,10,         // Code for char B  
14,17,17,         // Code for char C  
31,17,14,         // Code for char D  
31,21,21,         // Code for char E  
31,5,5,         // Code for char F  
14,17,29,         // Code for char G  
31,4,31,         // Code for char H  
17,31,17,         // Code for char I  
24,16,31,         // Code for char J  
31,4,27,         // Code for char K  
31,16,16,         // Code for char L  
31,2,4,2,31,     // Code for char M  
31,1,30,         // Code for char N  
14,17,14,         // Code for char O  
31,5,2,         // Code for char P  
31,17,31,16,     // Code for char Q  
31,5,26,         // Code for char R  
18,21,9,         // Code for char S  
1,31,1,         // Code for char T  
15,16,15,         // Code for char U  
31,8,7,         // Code for char V  
15,16,12,16,15, // Code for char W  
27,4,27,         // Code for char X  
3,28,3,         // Code for char Y  
25,21,19,         // Code for char Z  
31,17,17,         // Code for char [  
1,6,24,         // Code for char "\"  
17,17,31,         // Code for char ]  
2,1,2,             // Code for char ^  
16,16,16,         // Code for char _  
1,2,             // Code for char `  
8,26,28,         // Code for char a  
31,20,8,         // Code for char b  
12,18,18,         // Code for char c  
8,20,31,         // Code for char d  
12,22,20,         // Code for char e  
30,5,1,         // Code for char f  
20,26,12,         // Code for char g  
31,4,24,         // Code for char h  
29,             // Code for char i  
16,16,13,         // Code for char j  
31,8,20,         // Code for char k  
17,31,16,         // Code for char l  
30,2,12,2,28,     // Code for char m  
30,2,28,         // Code for char n  
12,18,12,         // Code for char o  
30,10,4,         // Code for char p  
4,10,30,         // Code for char q  
30,4,2,         // Code for char r  
20,22,10,         // Code for char s  
4,30,4,         // Code for char t  
14,16,14,         // Code for char u  
30,8,6,         // Code for char v  
14,16,12,16,14, // Code for char w  
18,12,18,         // Code for char x  
22,20,14,         // Code for char y  
26,22,22,         // Code for char z  
4,14,17,         // Code for char {  
27,             // Code for char |  
17,14,4,         // Code for char }  
1,2,1,2,         // Code for char ~  
14,14,14,14     // Code for char " "
};

// Char position and char size table
//
// CharSize = Font5x5WidthPos["2"] - Font5x5WidthPos["2" - 1]
// CharPos  = Font5x5WidthPos["2" - 1]
//
const u16 Font5x5WidthPos[] = {
1,2,5,10,14,18,21,23,26,29,33,36,38,41,
42,45,48,51,54,57,60,63,66,69,72,75,76,
78,81,84,87,90,93,96,99,102,105,108,111,
114,117,120,123,126,129,134,137,140,143,
147,150,153,156,159,162,167,170,173,176,
179,182,185,188,191,193,196,199,202,205,
208,211,214,217,218,221,224,227,232,235,
238,241,244,247,250,253,256,259,264,267,
270,273,276,277,280,284,289
};



/*
*    Init GPIO Port B for Output
*/
void SetBPortOut( void ) {
    // Init Pin Port B - LCD Data D0..D7
    GPIO_Init(GPIOB, 
            GPIO_PIN_0 | GPIO_PIN_1 | 
            GPIO_PIN_2 | GPIO_PIN_3 | 
            GPIO_PIN_4 | GPIO_PIN_5 | 
            GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST); // D0..D7
    
}

/*
*    Init GPIO Port B for Input
*/
void SetBPortIn( void ) {
    // Init Pin Port B - LCD Data D0..D7
    GPIO_Init(GPIOB, 
            GPIO_PIN_0 | GPIO_PIN_1 | 
            GPIO_PIN_2 | GPIO_PIN_3 | 
            GPIO_PIN_4 | GPIO_PIN_5 | 
            GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_IN_FL_NO_IT); // D0..D7
}

/*
*    Send command to LCD
*/
void sendCMD( u8 cmd ) {
    GPIO_WriteHigh(GPIOE, GPIO_PIN_7); // CS2 = Enable
    GPIO_WriteLow(GPIOE, GPIO_PIN_6);  // A0 = Low ( Cmd )        
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); // RD    
    GPIO_Write(GPIOB, cmd);
    GPIO_WriteLow(GPIOE, GPIO_PIN_5);  // WR
    GPIO_WriteHigh(GPIOE, GPIO_PIN_5); // WR
    GPIO_WriteLow(GPIOE, GPIO_PIN_7);  // CS2 = Disable
}

/*
*    Send Data to the LCD
*/
void sendData( u8 data ) {
    GPIO_WriteHigh(GPIOE, GPIO_PIN_7); // CS2 = Enable
    GPIO_WriteHigh(GPIOE, GPIO_PIN_6); // A0 = High ( Data )    
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); // RD    
    GPIO_Write(GPIOB, data);
    GPIO_WriteLow(GPIOE, GPIO_PIN_5);  // WR
    GPIO_WriteHigh(GPIOE, GPIO_PIN_5); // WR
    GPIO_WriteLow(GPIOE, GPIO_PIN_7);  // CS2 = Disable
}


void readDataDummy( void ) {

    SetBPortIn();
    GPIO_WriteHigh(GPIOE, GPIO_PIN_7); // CS2 = Enable
    GPIO_WriteHigh(GPIOE, GPIO_PIN_6); // A0 = High ( Data )
    GPIO_WriteHigh(GPIOE, GPIO_PIN_5); // WR
    GPIO_WriteLow(GPIOC, GPIO_PIN_1);  // RD
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); // RD
    GPIO_WriteLow(GPIOE, GPIO_PIN_7);  // CS2 = Disable
    SetBPortOut();
    
}


/*
*    Read data from the LCD
*/
u8 readData( void ) {
    u8 data = 0;    
    SetBPortIn();
    GPIO_WriteHigh(GPIOE, GPIO_PIN_7); // CS2 = Enable
    GPIO_WriteHigh(GPIOE, GPIO_PIN_6); // A0 = High ( Data )
    GPIO_WriteHigh(GPIOE, GPIO_PIN_5); // WR
    GPIO_WriteLow(GPIOC, GPIO_PIN_1);  // RD
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); // RD    
    data = GPIO_ReadInputData(GPIOB);                
    GPIO_WriteLow(GPIOE, GPIO_PIN_7);  // CS2 = Disable
    SetBPortOut();
    return data;
}

/*
*    Init the LCD LM6023B ( S1D15300 )
*/
void LCDInit( void ) {
    
    // Reset GPIO port B, C and E for LCD usage
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOE);
    GPIO_DeInit(GPIOC);
    
    SetBPortOut(); // Set Port B for Output
    
    // Init Pin Port E - LCD Control CS A0 WR
    GPIO_Init(GPIOE, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST); // WR - Low Active
    GPIO_Init(GPIOC, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST); // RD - Low Active
    GPIO_Init(GPIOE, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST); // A0 - High = Data | Low = Cmd
    GPIO_Init(GPIOE, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST); // CS - High = Enable | Low = Disable
    
    // LCD Init 
    GPIO_WriteHigh(GPIOE, GPIO_PIN_7);  // CS2
    GPIO_WriteHigh(GPIOE, GPIO_PIN_5);  // WR
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);  // RD
    GPIO_WriteHigh(GPIOE, GPIO_PIN_6);  // A0
    

    sendCMD( 0x00 ); // 
    sendCMD( 0xA2 ); // LCD Bias = 1/8
    sendCMD( 0xA0 ); // ADC = Normal
    sendCMD( 0xC0 ); // Output Status Register = Normal
    sendCMD( 0x40 ); // Init Display Line = 0x00
    sendCMD( 0x90 ); // Electronic Control Register = 0b1000
    sendCMD( 0x2F ); // Power Control
    sendCMD( 0xAF ); // Display ON
    sendCMD( 0xB0 ); // Page Address = 0x0
    sendCMD( 0x10 ); // Set Column upper 4bits
    sendCMD( 0x00 ); // Set Column lower 4bits

}

/*
*     Set Column ( X )
*/
void SetColumn( u8 Column ) {   
    u8 temp;   
    
    temp = Column;   
    Column = Column & 0x0f;   
    Column = Column | 0x00;   
    sendCMD( Column );   
    
    temp = temp >> 4;   
    Column = temp & 0x0f;   
    Column = Column | 0x10;   
    sendCMD( Column ); 
} 

/*
*     Set Page ( Y - Row )
*/
void SetPage( u8 Page ) {   
    Page = Page & 0x0f;   
    Page = Page | 0xb0;   
    sendCMD( Page );  
} 

/*
*     Clear the LCD
*/
void ClearScr( void ) {   
    FillScr( LCD_PIXEL_OFF );
}

/*
*     Fill the LCD
*/
void FillScr( u8 v ) {   
    u8 i;
    u8 j;
    for( i = 0; i < DISPLAY_HEIGHT / 8; i++ ) {
        SetColumn( 0x00 );
        SetPage(i);
        for( j = 0; j < DISPLAY_WIDTH; j++ ) {
            sendData( v );
        }
    } 
}

/*
*     Set Position for Read or Write
*/
void LcdSetPos( u16 x, u16 y ) {
    SetColumn( x );
    SetPage( y );
}



/*
*     Draw a point in the LCD
*    x
*    y
*   v      LCD_PIXEL_OFF/LCD_PIXEL_ON/LCD_PIXEL_INV
*/
void DrawPoint( u16 x, u16 y, u8 v ) {
    u8 ty = 0, tval, bit;

    if ( y >= DISPLAY_HEIGHT ) return;

    if ( x >= DISPLAY_WIDTH ) return;

    if ( y ) ty = ( y / 8 );

    bit = y - ( ty * 8 );

    LcdSetPos( x, ty );

    readDataDummy();
    tval = readData();

    if ( v == LCD_PIXEL_INV ) {
        v = ( ( ( ~tval ) >> bit ) & 1 );
    }
    if ( v == LCD_PIXEL_ON ) {
        tval |= ( 1 << bit );
    } else {
        tval &= ~( 1 << bit );
    }

    LcdSetPos( x, ty );
    sendData( tval );
}

/*
 * draw_line
 * 
 * v      LCD_PIXEL_OFF/LCD_PIXEL_ON/LCD_PIXEL_INV
 * 
 */
// Extremely Fast Line Algorithm Var E (Addition Fixed Point PreCalc ModeX)
// Copyright 2001-2, By Po-Han Lin


// Freely useable in non-commercial applications as long as credits 
// to Po-Han Lin and link to http://www.edepot.com is provided in 
// source code and can been seen in compiled executable.  
// Commercial applications please inquire about licensing the algorithms.
//
// Lastest version at http://www.edepot.com/phl.html
// Note: This version is for small displays like on cell phones.
// with 256x256 max resolution.  For displays up to 65536x65536
// please visit http://www.edepot.com/linee.html
void DrawLine(int x, int y, int x2, int y2, int v) {
       bool yLonger=false;
    int shortLen=y2-y;
    int longLen=x2-x;
    int decInc,j;
    
    if (abs(shortLen)>abs(longLen)) {
        int swap=shortLen;
        shortLen=longLen;
        longLen=swap;                
        yLonger=true;
    }
    
    if (longLen==0) decInc=0;
    else decInc = (shortLen << 8) / longLen;

    if (yLonger) {
        if (longLen>0) {
            longLen+=y;
            for (j=0x80+(x<<8);y<=longLen;++y) {
                DrawPoint(j >> 8,y,v);    
                j+=decInc;
            }
            return;
        }
        longLen+=y;
        for (j=0x80+(x<<8);y>=longLen;--y) {
            DrawPoint(j >> 8,y,v);    
            j-=decInc;
        }
        return;    
    }

    if (longLen>0) {
        longLen+=x;
        for (j=0x80+(y<<8);x<=longLen;++x) {
            DrawPoint(x,j >> 8,v);
            j+=decInc;
        }
        return;
    }
    longLen+=x;
    for (j=0x80+(y<<8);x>=longLen;--x) {
        DrawPoint(x,j >> 8,v);
        j-=decInc;
    }

}

/*
*     Draw a Rectangle
*/
void DrawRectangle( u8 left, u8 top, u8 right, u8 bottom, u8 linestate ) {
  DrawLine( left, top, right, top, linestate );
  DrawLine( left, top, left, bottom, linestate );
  DrawLine( right, top, right, bottom, linestate );
  DrawLine( left, bottom, right, bottom, linestate );  
}

/*
*    Draw a Char
*   v      LCD_PIXEL_OFF/LCD_PIXEL_ON/LCD_PIXEL_INV
*/
u8 DrawChar5x5(u8 x, u8 y, char character, u8 v) {
    u16 fontIndex, i, j, fontWidth, fontPos = 0;    
    
    fontIndex = character-32;
    if ( character < 32 ) return;
    if ( fontIndex > 96 ) return;
    
    if ( fontIndex > 0 ) {
        fontPos = Font5x5WidthPos[ fontIndex - 1];
    }
    fontWidth = Font5x5WidthPos[ fontIndex ] - fontPos;
    
    for (i = 0; i < fontWidth; i++) {
        for (j = 0; j < FONT_HEIGHT; j++) {                        
            if ( ValBit( Font5x5[ fontPos + i ], j ) ) {
                DrawPoint( x + i, y + j, v );
            }
        }       
    }
    return fontWidth;
}


/*
* v      LCD_PIXEL_OFF/LCD_PIXEL_ON/LCD_PIXEL_INV
*
/
void DrawText(u8 x, u8 y, char str[], u8 v) {
    u8 origin_X, fontWidth;

    /* Preserve the origin X, in case of a new line */
    origin_X = x;

    /* Continue through the string until we encounter a null character */
    while (*str != '\0') {
        /* If the character is a newline, then prepare our x and y
         * coordinates for the next character on the new line. */
        if (*str == '\n') {
            /* Reset x to its origin */
            x = origin_X;
            /* Move y one character down */
            y += FONT_HEIGHT;

            str++;
            continue;
        }

        fontWidth = DrawChar5x5(x, y, *str++, v);
        
        /* Add a 1-pixel spacing between the characters */
        x += fontWidth + 1;

        /* In case we are putting this character out of bounds,
         * move the character to the next line on the display */
        if ((x+fontWidth) > DISPLAY_WIDTH) {
            /* Reset x to its origin */
            x = origin_X;
            /* Move y one character down */
            y += FONT_HEIGHT;
        }
    }
}