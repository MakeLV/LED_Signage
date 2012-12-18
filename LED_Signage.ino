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
}

// the loop routine runs over and over again forever:
void loop() {

  // Prepare to set the next bit
  digitalWrite(clk, LOW);
  
    // Decide if bit should be on or off
    if (count%2 == 0) 
    { 
      digitalWrite(ser, LOW);
    } else {
      digitalWrite(ser, HIGH);
    }

  // Push the bit onto the shift register
  digitalWrite(clk, HIGH);


  // Iterate through the rows, turning one on at a time
  for (int row = 0; row < rowCount; row++) {
    digitalWrite(rows[row], HIGH);
    delay(100);
    digitalWrite(rows[row], LOW);
  }

  count++;
  delay(100);
}
