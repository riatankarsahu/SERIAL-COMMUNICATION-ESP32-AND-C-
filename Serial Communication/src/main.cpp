#include <Arduino.h>

const int LedPin = 19;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";
boolean isConnected = false;

void setup() 
{
  Serial.begin(115200);
  inputString.reserve(200);
  pinMode(LedPin, OUTPUT);
}

void serialEvent() 
{
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char) Serial.read();    
    inputString += inChar;    
    if (inChar == '\n') 
    {
      stringComplete = true;
    }
  }
}
boolean getLedState()
{
  boolean state = false;
  if(inputString.substring(5,7).equals("ON"))
  {
    state = true;
  }else
  {
    state = false;
  }
  return state;
}
void getCommand()
{
  if(inputString.length()>0)
  {
     commandString = inputString.substring(1,5);
  }
}
void turnLedOn()
{
  digitalWrite(LedPin, HIGH);
}

void turnLedOff()
{
  digitalWrite(LedPin, LOW);
}
void loop() 
{
  if(stringComplete)
{
  //Serial.println(inputString);
  stringComplete = false;
  getCommand();
  
   if(commandString.equals("STOP"))
  {
    turnLedOff();        
  }
   else //if(commandString.equals("LED1"))
  {
    boolean LedState = getLedState();
    if(LedState == true)
    {
      turnLedOn();
    }else
    {
      turnLedOff();
    }   
  }
  inputString = "";
 }
}