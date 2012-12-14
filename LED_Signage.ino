int clk = 11;
int ser = 12;
byte count = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(clk, OUTPUT);     
  pinMode(ser, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  digitalWrite(clk, LOW);
  
    if (count%4 == 0) 
    { 
      digitalWrite(ser, LOW);
    //  count = 1;
    } else {
      digitalWrite(ser, HIGH);
    //  count = 0;
    }
  
  delay(1);  
  digitalWrite(clk, HIGH);
  count++;
  delay(200);
}
