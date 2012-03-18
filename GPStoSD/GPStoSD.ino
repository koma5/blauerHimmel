//-------------------------------------------------------------------------------------------------------------------------------
// File     :  gpsv1_4.c
// Name     :  Stefan Steiner (@stektograph) & Marco Koch (@koma5)
// Date     :  07.02.2012
// Version  :  1.4
// Platform :  Arduino
// Function :  Get Data from the GPS modul pmb-248 and save them to a SD-Card
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Includes
//-------------------------------------------------------------------------------------------------------------------------------
#include <NewSoftSerial.h> //library for Serial connection
#include <SD.h> //library for SD Card
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Defines
//-------------------------------------------------------------------------------------------------------------------------------
#define pin_GPS_TX 3
#define pin_GPS_RX 2

#define pin_spi_cs 4
#define pin_spi_ss 10

#define array_NMEA 100
#define array_Data 15

#define GPRMC 0
#define GPGGA 1

#define server_name "drerscht"
#define server_apikey "4cdqfTqhL4SswTTeA4sOL4SswTTeA4sO"

//-------------------------------------------------------------------------------------------------------------------------------
//Hardware definitions 
//-------------------------------------------------------------------------------------------------------------------------------
NewSoftSerial GPS(pin_GPS_RX,pin_GPS_TX); //SoftwareSerial(RX,TX) 
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Flags
//-------------------------------------------------------------------------------------------------------------------------------
boolean GPSrecdata;    //is GPS receive data
boolean usefullData;   //are usefull Datas available
//-------------------------------------------------------------------------------------------------------------------------------
//Global Variables
//-------------------------------------------------------------------------------------------------------------------------------
char NMEA[array_NMEA]; //save NMEA sentence 
int NMEAcharcount;     //count 

//in char array -> we send string for calculating
char GPRMC_time[array_Data];              //long  //
char GPRMC_validity[array_Data];
char GPRMC_latitude[array_Data];          //float //
char GPRMC_northsouth[array_Data];
char GPRMC_longitude[array_Data];         //float //
char GPRMC_eastwest[array_Data];
char GPRMC_speed[array_Data];             //float // in knot -> 1 knot = 1,852 km/h
char GPRMC_direction[array_Data];
char GPRMC_date[array_Data];             //int   // day, month, year
char GPRMC_checksum[array_Data];

char GPGGA_altitude[array_Data];         //int   // above sea level

//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//setup & loop
//-------------------------------------------------------------------------------------------------------------------------------
void setup(){}        //program starts at Main
void loop(){Main();}  //
//-------------------------------------------------------------------------------------------------------------------------------
//Main
//-------------------------------------------------------------------------------------------------------------------------------
void Main(void)
{
  initSerial(); //initialize serial interface
  initVar();    //initialize every variables  
  Serial.println(initSD());     //initialize SD Card
  
  while(1)
  {
     if ((GPS.available()) && (GPSrecdata == true)) //GPS data are available and are allowed to receive
     {
        getGPSData(); //receive GPS data and parse them
     }
  
    if(usefullData == true) //usefull Data ready to save to SD
    {
  
      Serial.println("----------------------------------");
      Serial.print("time:");
      Serial.println(GPRMC_time);
            
      Serial.print("validity:");
      Serial.println(GPRMC_validity);

      Serial.print("latitude:");
      Serial.println(GPRMC_latitude);

      Serial.print("northsouth:");
      Serial.println(GPRMC_northsouth);

      Serial.print("longitude:");
      Serial.println(GPRMC_longitude);

      Serial.print("eastwest:");
      Serial.println(GPRMC_eastwest);

      Serial.print("speed:");
      Serial.println(GPRMC_speed);

      Serial.print("direction:");
      Serial.println(GPRMC_direction);

      Serial.print("date:");
      Serial.println(GPRMC_date);

      Serial.print("checksum:");
      Serial.println(GPRMC_checksum);
      //Serial.println("----------------------------------");    
   
       writetoSD();
       usefullData = false; //wait for next Data
    }
  }
}

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : int initSerial(void)
//task         : initialize Serial Interface 
//Parameter    : void
//Return       : 0 : Error
//               1 : Succesfull
//-------------------------------------------------------------------------------------------------------------------------------
int initSerial(void)
{
   GPS.begin(4800); //serial data configuration for pmb-248, baudrate 4800
   Serial.begin(9600); //serial data configuration for computer, baudrate: 9600
   return 1;
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : void initVar(void)
//task         : initialize Variables
//Parameter    : void
//Return       : 0 : Error
//               1 : Succesfull
//-------------------------------------------------------------------------------------------------------------------------------
int initVar(void)
{
   for(int x = 0; x<array_NMEA;x++) NMEA[x] = ' '; //empty NMEA
   NMEAcharcount = 0;
      
   GPSrecdata = true;
   usefullData = false;

   return 1;
}

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : void initSD(void)
//task         : initialize SD Card
//Parameter    : void
//Return       : 0 : Error
//               1 : Succesfull
//-------------------------------------------------------------------------------------------------------------------------------
int initSD(void)
{
   pinMode(pin_spi_ss, OUTPUT);
   
   if(!SD.begin(pin_spi_cs))
      return 0;  //Errorcase
   
  /* if(!SD.exists("archive"))
   {
     SD.mkdir("archive");
   }
   
   if(!SD.exists("archive/descript.txt"))
   {
     File dataFile = SD.open("archive/descript.txt", FILE_WRITE);
     dataFile.println("GPS logger, Marco Koch & Stefan Steiner");
     dataFile.println("The archive dir includes all Data that were sent to the server");
     dataFile.close();
   }
   
   
   writetoSD();/////to test!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   
   */
   return 1;     //initializing was a success
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : void getGPSData(void)
//task         : get an NMEA string 
//Parameter    : void
//Return       : 0 : Error
//               1 : Succesfull
//-------------------------------------------------------------------------------------------------------------------------------
int getGPSData()
{   
   while(GPS.available()) //get all sended data not just one char
   {
      NMEA[NMEAcharcount] = GPS.read(); //Get one char
        
      if (NMEA[NMEAcharcount] == '$') //if a dollarsign is received -> end of NMEA sentence
      {
         NMEA[NMEAcharcount] = '\0';  //replace dollarsign with end of string
         
         Serial.println(NMEA);              
         getDataNMEA();//get data from the String
  
         for(int x = 0; x<array_NMEA;x++)NMEA[x] = ' '; //prepare for filling new NMEA sentence
          
         NMEA[0] = '$'; //new String beginns with $
         NMEAcharcount = 0;            
      }

         NMEAcharcount++;                 
   }
   
   return 1;
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : int getDataNMEA(void)
//task         : get Datafrom an NMEA string and save these Data
//Parameter    : void
//Return       : 0 : Error
//               1 : Succesfull
//-------------------------------------------------------------------------------------------------------------------------------
int getDataNMEA(void)
{ 
   if(kindNMEAsent(GPRMC)) 	//check if it's a $GPRMC nmeastring
   {
         getdatastr(GPRMC);              
         //if(validdata)
         usefullData = true;  //usefull data 
      

   }

   if(kindNMEAsent(GPGGA))//check if it's a $GPGGA nmeastring
   {

      getdatastr(GPGGA);      
   }
   
  return 1;
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : int kindNMEAsent(int NMEAtype)
//task         : search if specifice type of NMEA sentence is received
//Parameter    : GPRMC
//               GPGGA                 
//Return       : 0 : Error
//               1 : Succesfull
//-------------------------------------------------------------------------------------------------------------------------------
int kindNMEAsent(int NMEAtype)
{ 
  int wheredollar = -1; //place of dollar sign
  
  for(int x = 0; x<array_NMEA; x++) //check where's the dollar sign
  {
    if(NMEA[x] == '$')//found
    {
      if(wheredollar ==-1)wheredollar = x;//just one dollarsign in the string is allowed
      else return 0;                      //
    }
  }
  if(wheredollar == -1) return 0; //no dollar sign found
  
  if(NMEAtype == GPRMC)
  {
    if(NMEA[wheredollar+1] == 'G')
    if(NMEA[wheredollar+2] == 'P')
    if(NMEA[wheredollar+3] == 'R')
    if(NMEA[wheredollar+4] == 'M')
    if(NMEA[wheredollar+5] == 'C')    
    return 1;
  }
  
  if(NMEAtype == GPGGA)
  {
    if(NMEA[wheredollar+1] == 'G')
    if(NMEA[wheredollar+2] == 'P')
    if(NMEA[wheredollar+3] == 'G')
    if(NMEA[wheredollar+4] == 'G')
    if(NMEA[wheredollar+5] == 'A')    
    return 1;
  }
  
  return 0;  
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Function     :
//task         : 
//Parameter    :    
//Return       : 0 : Error
//               1 : Succesfull
//-------------------------------------------------------------------------------------------------------------------------------

int getdatastr(int NMEAtype)
{
  int startplace = 0; //startplace of copied part of String startplace is on a comma
 
  if(nextcommaNMEA(0))
     startplace = nextcommaNMEA(0);//index of first ','
  else return 0;
  
  
  //Serial.print("first comma");
  //Serial.println(cursorNMEA);


  if(NMEAtype == GPRMC)
  {
    partdata(startplace, GPRMC_time);
    startplace = nextcommaNMEA(startplace);
    
    partdata(startplace, GPRMC_validity);
    startplace = nextcommaNMEA(startplace);

    partdata(startplace, GPRMC_latitude);
    startplace = nextcommaNMEA(startplace);

    partdata(startplace, GPRMC_northsouth);
    startplace = nextcommaNMEA(startplace);

    partdata(startplace, GPRMC_longitude);
    startplace = nextcommaNMEA(startplace);

    partdata(startplace, GPRMC_eastwest);
    startplace = nextcommaNMEA(startplace);

    partdata(startplace, GPRMC_speed);
    startplace = nextcommaNMEA(startplace);

    partdata(startplace, GPRMC_direction);
    startplace = nextcommaNMEA(startplace);

    partdata(startplace, GPRMC_date);
    startplace = nextcommaNMEA(startplace);
    startplace = nextcommaNMEA(startplace);
    startplace = nextcommaNMEA(startplace);
    
    partdata(startplace, GPRMC_checksum);  
  }
  if(NMEAtype == GPGGA)
  {
  }
  
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : 
//task         : 
//Parameter    : 
//Return       : 0 : Error
//               1 : Success
//-------------------------------------------------------------------------------------------------------------------------------
int partdata(int startposition, char *result)
{
    int stopposition = 0;  //stopplace of copied part of String, stoppplace is on a comma or a end string termination sign
    int count = 0;

   if(nextcommaNMEA(startposition))
   {
     stopposition = nextcommaNMEA(startposition);
     startposition++; //comma is not included in data
     while(stopposition > startposition)
     {
       result[count] = NMEA[startposition];
       count++;
       startposition++;
     }
     return 1;
   }
   else return 0;//error
  
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : 
//task         : 
//Parameter    : 
//Return       : 0 : Error
//               int position; position of next comma in NMEA string
//-------------------------------------------------------------------------------------------------------------------------------
int nextcommaNMEA(int curserposition)
{
  curserposition++; //search next comma, not the actuall one 
   while(NMEA[curserposition] != ',' && curserposition<array_NMEA && NMEA[curserposition] != '\n')curserposition++; //find next comma in sentence
  if(curserposition >= array_NMEA-1) return 0;// errorcase no comma in the string
  else return curserposition;
     
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Function     : 
//task         : 
//Parameter    : 
//Return       : 0 : Error
//               int position; position of next comma in NMEA string
//-------------------------------------------------------------------------------------------------------------------------------
int writetoSD(void)
{
   if(!SD.exists("readytosend.txt"))
   {
     File dataFile = SD.open("readytosend.txt", FILE_WRITE);
     dataFile.println("{");
     dataFile.print("  \"name\":");
     dataFile.print(server_name);
     dataFile.print(",\naöslfdölasdjasfdj");
	 
	 //fileaufbau noch einfügen... no problem
     dataFile.close();
   }
 
}
//-------------------------------------------------------------------------------------------------------------------------------

