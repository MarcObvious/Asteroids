        /*
Ultra-simple sketch to demonstrate the use of Arduino with 
openFrameworks.

This sketch is written to be used with the serialExample program 
that comes with the openFrameworks library. It initializes a serial 
port with a speed of 9600 baud, then waits for serialExample to send
a character ('a' by default), then responds with three dollar signs.

To use this sketch with oF, program your Arduino, make sure the 
Arduino is the only vitual COM device in use, and then build and run
the serialExample example
in openFrameworks.

Released under the Creative Commons Share-Alike License 10/2011
*/
void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
}

void loop()
{
  char inByte = 0;
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    
    // byte read, send three characters
    Serial.print("$");
    Serial.print("$");
    Serial.print("$");
        
  }
}
