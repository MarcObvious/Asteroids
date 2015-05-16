#include <SerialLCD.h>
#include <SoftwareSerial.h>

SerialLCD slcd(11,12);
int ledPin = 13;
//led for visualization (use 13 for built-in led)
 
int speakerPin = 9;
//speaker connected to one of the PWM ports
 
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

int xPin = A1;
int yPin = A0;
int buttonPin = 2;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;
int Position =0;

char inData[8]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup() {
    // initialize serial communications at 9600 bps:
    Serial.begin(9600); 
    
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    
    //activate pull-up resistor on the push-button pin
    pinMode(buttonPin, INPUT_PULLUP); 
    
    // For versions prior to Arduino 1.0.1
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin, HIGH);
     
    slcd.begin();
    // Print a message to the LCD.
   // slcd.print("Pium Pium Pium! Just SHOT!");
   // slcd.scrollDisplayLeft();
   // slcd.setCursor(0,1);
   // slcd.print("Player 0 dir_key ,1 asdw, 0 Joystic.");
    slcd.noBacklight();
    pinMode(ledPin, OUTPUT);
  // sets the ledPin to be an output
  pinMode(speakerPin, OUTPUT);
  //sets the speakerPin to be an output

}
void Joystic() {
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    Serial.print(xPosition,DEC);
    Serial.print(yPosition,DEC);
    Serial.print('\n');
    delay(70);
}
            

void loop() {

   
    
    while (Serial.available() > 0) {
           //char inByte = Serial.read();
        
            

             //if(index < 7)  {// One less than the size of the array
         
                  inChar = Serial.read(); // Read a character
                  /*inData[index] = inChar; // Store it
                  index++; // Increment where to write next
                  inData[index] = '\0'; // Null terminate the string
              }*/
              
                 
              if ( inChar != 'N' ){
                  char sortida ='N';
                  if (inChar == 'Z')
                     sortida = '0';
                  if (inChar == 'U')
                     sortida = '1';
                   if (inChar == 'D')
                     sortida = '2';
                   if (inChar == 'T')
                     sortida = '3';
                   if (inChar == 'Q')
                     sortida = '4';
                   if (sortida != 'N') {
                      slcd.backlight();
                      slcd.scrollDisplayLeft();
                      slcd.setCursor(0, 0);
                       // slcd.print(inByte);
                      slcd.print("Winner Player ");
                      slcd.print(sortida);
                      slcd.print(",  Your're The BOSS");
                      slcd.setCursor(0,1);
                      
                      slcd.print("Press r to restart! Keep KILLING    ");
                      //march();
                   }
                }
                else {
                    slcd.scrollDisplayLeft();
                    slcd.noBacklight();
                    slcd.setCursor(0, 0);
                    slcd.print("Pium Pium Pium! Just SHOT!          ");
                    slcd.setCursor(0,1);
                    slcd.print("Player 0 dir_key ,1 asdw, 0 Joystic.");

                }
               /* if (index==7) 
                  index = 0;*/
                  Joystic();
                

    }
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{
    digitalWrite(ledPin, HIGH);
    //use led to visualize the notes being played
 
    int x;
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)
    {
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    }
 
    digitalWrite(ledPin, LOW);
    //set led back to low
 
    delay(20);
    //a little delay to make all notes sound separate
}
 
void march()
{
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note
 
    beep(speakerPin, a, 500);
    beep(speakerPin, a, 500);
    beep(speakerPin, a, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
 
    beep(speakerPin, a, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);
    //first bit
 
    beep(speakerPin, eH, 500);
    beep(speakerPin, eH, 500);
    beep(speakerPin, eH, 500);
    beep(speakerPin, fH, 350);
    beep(speakerPin, cH, 150);
 
    beep(speakerPin, gS, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);
    //second bit...
 
   /* beep(speakerPin, aH, 500);
    beep(speakerPin, a, 350);
    beep(speakerPin, a, 150);
    beep(speakerPin, aH, 500);
    beep(speakerPin, gSH, 250);
    beep(speakerPin, gH, 250);
 
    beep(speakerPin, fSH, 125);
    beep(speakerPin, fH, 125);
    beep(speakerPin, fSH, 250);
    delay(250);
    beep(speakerPin, aS, 250);
    beep(speakerPin, dSH, 500);
    beep(speakerPin, dH, 250);
    beep(speakerPin, cSH, 250);
    //start of the interesting bit
 
    beep(speakerPin, cH, 125);
    beep(speakerPin, b, 125);
    beep(speakerPin, cH, 250);
    delay(250);
    beep(speakerPin, f, 125);
    beep(speakerPin, gS, 500);
    beep(speakerPin, f, 375);
    beep(speakerPin, a, 125);
 
    beep(speakerPin, cH, 500);
    beep(speakerPin, a, 375);
    beep(speakerPin, cH, 125);
    beep(speakerPin, eH, 1000);
    //more interesting stuff (this doesn't quite get it right somehow)
 
    beep(speakerPin, aH, 500);
    beep(speakerPin, a, 350);
    beep(speakerPin, a, 150);
    beep(speakerPin, aH, 500);
    beep(speakerPin, gSH, 250);
    beep(speakerPin, gH, 250);
 
    beep(speakerPin, fSH, 125);
    beep(speakerPin, fH, 125);
    beep(speakerPin, fSH, 250);
    delay(250);
    beep(speakerPin, aS, 250);
    beep(speakerPin, dSH, 500);
    beep(speakerPin, dH, 250);
    beep(speakerPin, cSH, 250);
    //repeat... repeat
 
    beep(speakerPin, cH, 125);
    beep(speakerPin, b, 125);
    beep(speakerPin, cH, 250);
    delay(250);
    beep(speakerPin, f, 250);
    beep(speakerPin, gS, 500);
    beep(speakerPin, f, 375);
    beep(speakerPin, cH, 125);
 
    beep(speakerPin, a, 500);
    beep(speakerPin, f, 375);
    beep(speakerPin, c, 125);
    beep(speakerPin, a, 1000);*/
    //and we're done \ó/
}
