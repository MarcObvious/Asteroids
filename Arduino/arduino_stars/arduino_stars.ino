#include <SerialLCD.h>
#include <SoftwareSerial.h>
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


SerialLCD slcd(11,12);

int ledPin = 13;
int buttonPin = 2; 

int speakerPin = 9;
//speaker connected to one of the PWM ports
 
int xPin = A1;
int yPin = A0;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;
bool guanyador = false;

char inData[1]; // Allocate some space for the string

void setup() {
    // initialize serial communications at 9600 bps:
    Serial.begin(9600); 
    
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    
    pinMode(buttonPin, INPUT);
     
    slcd.begin();
    pinMode(ledPin, OUTPUT);
    // sets the ledPin to be an output
    pinMode(speakerPin, OUTPUT);
    //sets the speakerPin to be an output
}

void printVal(int val) {
    byte highByte = ((val >> 8) & 0xFF);
    byte lowByte = ((val) & 0xFF);
    Serial.write(highByte);
    Serial.write(lowByte);
    //delay(40);
}

void Joystic() {
    xPosition = analogRead(xPin);
    printVal(xPosition);
    yPosition = analogRead(yPin);
    printVal(yPosition);
    //delay(70);
}

void winner (char w) {
    slcd.setCursor(0, 0);
    slcd.print("Winner Player ");
    slcd.print(w);
    slcd.print(",  Your're The BOSS");
    slcd.setCursor(0,1); 
    slcd.print("Press r to restart! Keep KILLING    ");
    guanyador = true;     
} 

void finish() {
    slcd.setCursor(0, 0);
    slcd.print(" Thx For Playing!");
    slcd.setCursor(0,1); 
    slcd.print(" Yeah, it's a Loop");
    march();
}

void loop() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
        printVal(000);
        printVal(000);
    }
    slcd.scrollDisplayLeft();
    if(Serial.readBytes(inData,1) > 0) { 
        if (inData[0] == 'Z') 
          winner('0');
        else if (inData[0] == 'U') 
          winner('1');
        else if (inData[0] == 'D') 
          winner('2');
        else if (inData[0] == 'T') 
          winner('3');
        else if (inData[0] == 'Q') 
          winner('4');  
        else if (inData[0]== 'A')
          guanyador = false;
        else if (inData[0] == 'F')
          finish();
    }
    if (!guanyador) {
        slcd.setCursor(0,0);
        slcd.print("Pium Pium Pium! Just SHOT!          ");
        slcd.setCursor(0,1);
        slcd.print("Player 0 dir_key ,1 asdw, 2 Joystic.");
    }
    Joystic();
    
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{
    if (guanyador == true) {
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
    beep(speakerPin, a, 1000);
    //and we're done \ó/*
}
