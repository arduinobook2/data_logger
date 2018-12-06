//Connections:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4

#include <SD.h>
#include <SPI.h>

// Set Chip Select to pin four
int cs = 4;  

int analogIn = A0;
int RawValue= 0;
double tempC = 0;

/***** Parameters *****/
// In milliseconds
int SampleRate = 1000;
  

// How many measurements to make
int NumOfSamples = 60; 


// The name of the file we will create
char myLogName[] = "MyLog.txt";  



// a File Object
File myLog;  

void setup()
{  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
  }
  
  Serial.println("Initializing SD card...");
  Serial.println();
  
  pinMode(cs, OUTPUT);
  
  // Documentation says you're supposed to do this
  // even if you don't use it:
  pinMode(SS, OUTPUT);
   
  // see if the card is present and can be initialized:
  if (!SD.begin(cs)) 
  {
    Serial.println("SD did not initiliaze");   
    while (1) ;
  }
  
  Serial.println("SD initialized.");
  Serial.println(); 
  
  myLog = SD.open(myLogName, FILE_WRITE);
  getData();
  
  Serial.print("DONE");
}

void loop()
{
}

void getData()
{  
  for(long x = 0; x < NumOfSamples; x++)
  {    
    RawValue = analogRead(analogIn);
    tempC = (RawValue / 1023.0) * 500;   
    myLog.print(x * SampleRate);
    // Seperates the data points
    myLog.print(","); 
    
    // println gives us a newline that will separate our samples     
    myLog.println(tempC); 
    
    
    delay(SampleRate);
  }
  
  // Saves the file
  myLog.flush();  
  
  myLog.close();
}
