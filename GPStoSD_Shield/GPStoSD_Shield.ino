/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */
#include "TinyGPS.h"
TinyGPS gpsParser;

long lat, lon;
unsigned long fix_age, time, date;
unsigned long chars;
unsigned short sentences, failed_checksum;

boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    gpsParser.get_position(&lat, &lon, &fix_age);
    gpsParser.stats(&chars, &sentences, &failed_checksum);
    gpsParser.get_datetime(&date, &time, &fix_age);
    Serial.print("lat: ");
    Serial.println(lat);
    Serial.print("lon: ");
    Serial.println(lon);
    Serial.print("date: ");
    Serial.println(date);
    Serial.print("time: ");
    Serial.println(time);
    Serial.print("chars: ");
    Serial.print(chars);
    Serial.print(" sentences: ");
    Serial.print(sentences);
    Serial.print(" failed_checksum: ");
    Serial.println(failed_checksum);
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (gpsParser.encode(inChar)) {
      stringComplete = true;
    } 
  }
}


