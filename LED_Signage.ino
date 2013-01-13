int clk = 2; // Clock
int ser = 3; // Serial
 

// Array of pins the rows coorespond to
int rows[] = { 8, 9, 10, 11, 7, 6, 5 };
int rowCount = 7; 
int columnCount = 71;

const char font[2][6] PROGMEM = //this font doesn't work because it is layered left-to-right instead of top to bottom
{
 
	{0x00,0x00,0x00,0x00,0x00,0x00},	// SPACE (33)
 
	{0x00,0x7E,0x11,0x11,0x11,0x7E},	// A
};

char a[] = {0x1C,0x22,0x22,0x3E,0x22,0x22,0x00}; //letter layer from top to bottom

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the serial and clock pins as outputs.
  pinMode(clk, OUTPUT);     
  pinMode(ser, OUTPUT);

  // setup the row pins, make sure they're off
  for (int row = 0; row < rowCount; row++)  {
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);
  }

  clear_display(columnCount);

  Serial.begin(9600);
  Serial.println("Hello");
}

// the loop routine runs over and over again forever:
void loop() {

  print_letter();
  clear_display(75);

}


// Count in binary on the display
void count_binary(int n)
{
  // Count to some number, but put a buffer of blank bits in between
  for (int bits = 0;  bits < n; bits++) {
    shiftOut(ser, clk, MSBFIRST, bits);
    shiftOut(ser, clk, MSBFIRST, B00000000);

    // show this on each row once before moving on
    for (int row = 0; row < rowCount; row++) {
      digitalWrite(rows[row], HIGH);
      delay(100);
      digitalWrite(rows[row], LOW);
    }
  }
}

// Print a letter onto the display
void print_letter() //(char c)
{
  int i;

  for (i=0; i<rowCount; i++)
  {
//    write_data(pgm_read_byte(&font[(int)c][i]));
    shiftOut(ser, clk, MSBFIRST, a[i]);
    digitalWrite(rows[i], HIGH);
    delay(2);
    digitalWrite(rows[i], LOW);
    clear_display(70);
  }

}

// Clear the display
void clear_display(int i)
{
  // Shift 75 0s onto the register to clear it, doing 
  // it this way because even in decimal, that's a big number
  for (int clear = 0; clear <= i; clear++) {
    shiftOut(ser, clk, MSBFIRST, 0b0);
  }
}

// Create a blank buffer of space
void buffer_display()
{
  shiftOut(ser, clk, MSBFIRST, 00000);
}
