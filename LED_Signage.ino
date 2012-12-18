int clk = 11;
int ser = 12;
byte count = 0;

// Array of pins the rows coorespond to
int rows[] = { 8, 9, 10, 13, 7, 6, 5 };
int rowCount = 7;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(clk, OUTPUT);     
  pinMode(ser, OUTPUT);

  for (int row = 0; row < rowCount; row++)  {
    pinMode(rows[row], OUTPUT);
  }

  // Shift 75 0s onto the register to clear it  
  for (int clear = 0; clear <= 15; clear++) {
    shiftOut(ser, clk, MSBFIRST, 00000);
  }
}

// the loop routine runs over and over again forever:
void loop() {

  // Count to 256, but put a buffer of 4 bits in between
  for (int bits = 0;  bits < 256;  bits++) {
    shiftOut(ser, clk, MSBFIRST, bits);
    shiftOut(ser, clk, MSBFIRST, 0000);
    delay(1000);
  }
}
