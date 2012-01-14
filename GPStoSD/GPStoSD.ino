#include <SoftwareSerial.h>
#include <SD.h>
#include <String.h>

//SoftwareSerial(RX,TX)
SoftwareSerial GPS = SoftwareSerial(2,3);

//Var declaration
const int chipSelect = 4;

int countNMEA = 0;
char NMEA[100] = "";
String bastelString;

void setup()
{
  //serial data configuration for pmb-248
  GPS.begin(4800); //baudrate: 4800 (fixed)
  //serial data configuration for computer
  Serial.begin(9600); //baudrate: 9600

/*
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
    
  Serial.println("card initialized.");
  }*/




}


void loop()
{
  
  //File logFile = SD.open("gps.txt", FILE_WRITE);
  
  if (GPS.available()){
   
    NMEA[countNMEA] = GPS.read();
    /* // #dev
    Serial.print("[");
    Serial.print(countNMEA, DEC);
    Serial.print("]:");
    Serial.print(NMEA[countNMEA]);*/
    
    if (NMEA[countNMEA] == '$')
    {
      //Dollarsign data received
      //Serial.println("data receivd");  
      NMEA[countNMEA] = '\0';
      
      
      for(int x = 0; NMEA[x] != '\0';x++)Serial.print(NMEA[x]);
      
      /*bastelString = NMEA;
     if((bastelString.indexOf("$GPRMC")) == 0)
     {
       if 
       Serial.print(bastelString);
     }*/

      for(int y = 0; y<100;y++)NMEA[y] = ' '; //empty NMEA
      NMEA[0] = '$';
      countNMEA = 0;
    }
    countNMEA++;  
    /*
    logFile.println(dataChar);
    logFile.close();
    // print to the serial port too:

    Serial.write(dataChar);*/
    
    
    
  }
  
  getGPSData
}
