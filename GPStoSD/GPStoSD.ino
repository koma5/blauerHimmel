#include <SoftwareSerial.h>
#include <SD.h>
#include <string.h>

//SoftwareSerial(RX,TX)
SoftwareSerial GPS = SoftwareSerial(2,3);

//Var declaration
const int chipSelect = 4;
char dataString;

void setup()
{
  GPS.begin(4800);
  Serial.begin(9600);


  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
    
  Serial.println("card initialized.");
  }




}


void loop()
{
  
  File logFile = SD.open("gps.txt", FILE_WRITE);
  
  if (GPS.available() && logFile){
    
    dataString = GPS.read();
    
    logFile.println(dataString);
    logFile.close();
    // print to the serial port too:

    Serial.write(dataString);
  }
}
