#include "font.h"

int clk = 2; // Clock
int ser = 3; // Serial

// Array of pins the rows coorespond to
int rows[] = { 8, 9, 10, 11, 7, 6, 5 };
int rowCount = 5; //Actually 7, but only 5 wired up atm

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the serial and clock pins as outputs.
  pinMode(clk, OUTPUT);     
  pinMode(ser, OUTPUT);

  // setup the row pins, make sure they're off
  for (int row = 0; row < rowCount; row++)  {
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], HIGH);
  }

  // Shift 75 0s onto the register to clear it, doing 
  // it this way because even in decimal, that's a big number
  for (int clear = 0; clear <= 15; clear++) {
    shiftOut(ser, clk, MSBFIRST, 00000);
  }
}

// the loop routine runs over and over again forever:
void loop() {

  // Count to some number, but put a buffer of blank bits in between
  for (int bits = 0;  bits < 2048; bits++) {
    shiftOut(ser, clk, MSBFIRST, bits);
    shiftOut(ser, clk, MSBFIRST, B00000000);

    // show this on each row once before moving on
    for (int row = 0; row < rowCount; row++) {
      digitalWrite(rows[row], LOW);
      delay(100);
      digitalWrite(rows[row], HIGH);
    }

  // Iterate through the rows, turning one on at a time
  for (int row = 0; row < rowCount; row++) {
    digitalWrite(rows[row], LOW);
    delay(100);
    digitalWrite(rows[row], HIGH);
  }
}

/* lights up the display so you can see the message */

void light_up_display() {
  for (int row = 0; row < rowCount; row++) {
    digitalWrite(rows[row], LOW);
    delay(2);
    digitalWrite(rows[row], HIGH);
  }
}

/* print a single character 
 * from: http://code.google.com/p/ht1632c/source/browse/ht1632c.cpp?r=f32a1046dbffe7417cc068d186b0bd3c17a28271
*/

byte putchar (int x, int y, char c, byte color, byte attr)
{
  byte dots, width = 5;

  Serial.println(c, DEC);
  c -= 32;

  for (char col=0; col < width; col++) {
    // some math with pointers... don't try this at home ;-)
    prog_char *addr = font + c * width + col;
    dots = pgm_read_byte_near(addr);

    if (dots) {
      for (char row = 0; row < font_height; row++) {
        if (dots & (128>>row))
          plot(x+col, y+row, color);
        else 
          plot(x+col, y+row, BLACK);

      }
    } else if (attr & PROPORTIONAL) {
      width--;
      x--;
    }
  }
  return width;
}
