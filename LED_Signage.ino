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

  // Count to 256, but put a buffer of 4 bits in between
  for (int bits = 0;  bits < 256;  bits++) {
    shiftOut(ser, clk, MSBFIRST, bits);
    shiftOut(ser, clk, MSBFIRST, B0000);

    // show this on each row once before moving on
    for (int row = 0; row < rowCount; row++) {
      digitalWrite(rows[row], LOW);
      delay(100);
      digitalWrite(rows[row], HIGH);
    }

    delay(1000);
  }
}
