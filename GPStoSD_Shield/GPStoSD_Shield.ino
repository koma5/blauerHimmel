#include <SoftwareSerial.h>
SoftwareSerial GPS = SoftwareSerial(1,0);


void setup()
{
  
  GPS.begin(38400); //serial data configuration for pmb-248, baudrate 4800
  Serial.begin(9600); //serial data configuration for computer, baudrate: 9600

}


void loop()
{ 
  Serial.print(GPS.read());
  
  
}

