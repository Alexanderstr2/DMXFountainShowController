#include <dmxserial.h>
#include <Arduino.h>
#include <DMXSerial.h>
#include <LiquidCrystal.h>

// Setup Control Pins
//------------------------------------------------------------------------------
//Fountain Pins
const unsigned int pump1 =   3;  // PWM output for pump1
const unsigned int pump2 =   5;  // PWM output for pump2
const unsigned int pump3 =   6;  // PWM output for pump3
const unsigned int pump4 =   9;  // PWM output for pump4

//Button Pins
const unsigned int enter =   4;  // Enter button
const unsigned int up =      7;  // up button
const unsigned int down =    8;  // down button
//------------------------------------------------------------------------------

// Setup DMX
//------------------------------------------------------------------------------
unsigned int DMXSTART = 1;

// number of DMX channels used
#define DMXLENGTH (4)
//------------------------------------------------------------------------------

//Setup LCD
//------------------------------------------------------------------------------

//LCD Pins
const int rs = 12, en = 11, d4 = 13, d5 = 14, d6 = 15, d7 = 16;

//LCD Configuration
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//------------------------------------------------------------------------------

void setup () {
  // Start DMXSerial
  DMXSerial.init(DMXProbe);

  //Enable Button Inputs
  pinMode(enter, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);


  //Enable Pwm Outputs
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(pump3, OUTPUT);
  pinMode(pump4, OUTPUT);
  
  //Set Max DMX channel length
  DMXSerial.maxChannel(DMXLENGTH);

  //Set up the LCD columns and rows:
  lcd.begin(16, 2);
  
  //Set the DMX Channel
  changeDMXChannel();
}

//Get DMX data and update pumps
void loop() {
  //Wait to see if channel change is entered
  if (digitalRead(enter) == true) {
        delay(50);
        changeDMXChannel();
    }
  //Wait for an incomming DMX packet.
  if (DMXSerial.receive()) {
    analogWrite(pump1, DMXSerial.read((DMXSTART + 1));
    analogWrite(pump2, DMXSerial.read((DMXSTART + 2)));
    analogWrite(pump3, DMXSerial.read((DMXSTART + 3)));
    analogWrite(pump4, DMXSerial.read((DMXSTART + 4)));

  } else {
    //If no signal received, turn off pumps
    analogWrite(pump1, 0);
    analogWrite(pump2, 0);
    analogWrite(pump3, 0);
    analogWrite(pump4, 0);
  }
  
}

//Function to change DMX channel
void changeDMXChannel () {
    //Print DMX change to LCD
    lcd.setCursor(0, 0);
    lcd.print("DMX Channel:");
    lcd.setCursor(0, 1);

    white (true) {
        //Print DMX Channel
        lcd.print(DMXSTART);
        //Change Channel
        if (digitalRead(up) == true) {
            ++DMXSTART;
        }
        if (digitalRead(down) == true) {
            --DMXSTART;
        }
        //Exit Menu
        if (digitalRead(enter) == true) {
            delay(50);
            //Print Main Screen
           lcd.print("Enter To Set DMX");
           lcd.setCursor(0,1);
           lcd.print("DMX: ");
           lcd.setCursor(6,1);
           lcd.print(DMXSTART);

           return;
        }
    }
}