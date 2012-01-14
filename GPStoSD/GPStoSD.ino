#include <SoftwareSerial.h>
#include <SD.h>
#include <String.h>

//SoftwareSerial(RX,TX)
SoftwareSerial GPS = SoftwareSerial(2,3);

//var declaration
const int chipSelect = 4;
const int StatusLED = 12;

int countNMEA = 0;
char NMEA[100] = "";
String parsedNMEA;

void setup()
{
  //serial data configuration for pmb-248
  GPS.begin(4800); //baudrate: 4800 (fixed)
  //serial data configuration for computer
  Serial.begin(9600); //baudrate: 9600
  
  pinMode(StatusLED, OUTPUT);

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
  digitalWrite(StatusLED, HIGH);
  getGPSData();
  digitalWrite(StatusLED, LOW);
    /*
    logFile.println(dataChar);
    logFile.close();
    // print to the serial port too:

    Serial.write(dataChar);*/
    
}

void getGPSData()
{
    
    if (GPS.available()){
   
        NMEA[countNMEA] = GPS.read();
        /* // #dev print out every char
        Serial.print("[");
        Serial.print(countNMEA, DEC);
        Serial.print("]:");
        Serial.print(NMEA[countNMEA]);*/
        
        if (NMEA[countNMEA] == '$')
        {
           //if a dollarsign is received -> end of NMEA sentence
           //Serial.println("data receivd");  
           NMEA[countNMEA] = '\0'; //replace dollarsign with end of string
          
           //for(int x = 0; NMEA[x] != '\0';x++)Serial.print(NMEA[x]);
          
          parseNMEA(NMEA);
    
          for(int y = 0; y<100;y++)NMEA[y] = ' '; //empty NMEA[]
          
          NMEA[0] = '$';
          countNMEA = 0;
        }

    countNMEA++; 
  
    }
}

void parseNMEA(const char input[])
{
  parsedNMEA = input;
  //for(int x = 0; input[x] != '\0';x++)Serial.print(input[x]);
  //Serial.print(parsedNMEA);
  
  
  if(parsedNMEA.indexOf("$GPRMC") >= 0)
  {
    //if 
      Serial.print("found $GPRMC at:");
      Serial.print(parsedNMEA.indexOf("$GPRMC"));
      Serial.print(parsedNMEA);
  }

  
  if(parsedNMEA.indexOf("$GPGGA") >= 0)
  {
    //if 
      Serial.print("found $GPGGA at:");
      Serial.print(parsedNMEA.indexOf("$GPGGA"));
      Serial.print(parsedNMEA);
      
  }
}
