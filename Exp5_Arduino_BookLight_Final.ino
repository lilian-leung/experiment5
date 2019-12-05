#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>
 
SdFat sd;
SFEMP3Shield MP3player;

//BOOK PINS 
int convo1 = 0;
int convo2 = 1;
int convo3 = 3;
int convo4 = 4;
int convo5 = 5;

int convoState1 = 0;
int convoState2 = 0;
int convoState3 = 0;
int convoState4 = 0;
int convoState5 = 0;

//LAMP AND CHAINR PINS
int lampPin = 10; //digital pin

int lampBrightness;
int lampMin = 20;
int lampMax = 255;

int chairPin = A5; 
int chairVal;

int trackNumber = 7;
int prevTrack = 7;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

pinMode (chairPin, INPUT);
pinMode (lampPin, OUTPUT);

pinMode (convo1, INPUT_PULLUP); 
pinMode (convo2, INPUT_PULLUP); 
pinMode (convo3, INPUT_PULLUP); 
pinMode (convo4, INPUT_PULLUP); 
pinMode (convo5, INPUT_PULLUP); 



////start the shield
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();


}

void loop() {

convoState1 = digitalRead (convo1);
convoState2 = digitalRead (convo2);
convoState3 = digitalRead (convo3);
convoState4 = digitalRead (convo4);
convoState5 = digitalRead (convo5);

chairVal = analogRead(5);
analogWrite(lampPin, lampBrightness);


//CHAIR SENSOR - LAMP BRIGHTNESS
  if (chairVal < 350) {
  lampBrightness = lampMax; 
  } else {
    lampBrightness = lampMin;
  }

//TRACKLIST SETTINGS

  if (convoState1 == HIGH && convoState5 == LOW) {
    trackNumber = 1;
  }
   else if (convoState1 == LOW && convoState2 == HIGH && convoState3 == LOW && convoState5 == LOW) {
    trackNumber = 2;
  }
  else if (convoState1 == LOW && convoState3 == HIGH && convoState4 == HIGH && convoState5 == LOW ) {
    trackNumber = 3;
  }
  else if (convoState1 == LOW && convoState3 == LOW && convoState4 == HIGH && convoState5 == LOW) {
    trackNumber = 4;
  }
  else if (convoState1 == LOW && convoState3 == LOW && convoState5 == HIGH) {
    trackNumber = 5;
  }
  else
  {
    trackNumber = 7;
  }



if(trackNumber!=prevTrack)
{
  if (MP3player.isPlaying())
  {
        MP3player.stopTrack();
  }
}


MP3player.playTrack(trackNumber); 

//Serial.print ("page1:");
//Serial.print (convoState1);
//Serial.print ("\t");
//
//Serial.print ("page2:");
//Serial.print (convoState2);
//Serial.print ("\t");
//
//Serial.print ("page3:");
//Serial.print (convoState3);
//Serial.print ("\t");
//
//Serial.print ("page4:");
//Serial.print (convoState4);
//Serial.print ("\t");
//
//Serial.print ("page5:");
//Serial.print (convoState5);
//Serial.print ("\t");
//
//Serial.println (trackNumber);
//Serial.print ("\t");

Serial.print ("chairvvalue");
Serial.println (chairVal);


delay(100);

prevTrack = trackNumber;
  
}
