#include <Adafruit_NeoPixel.h>

#define PIN_r 8
#pragma once

const int buttonPin = 4; //pushbutton's pin
  
int buttonState = 0;

#define RINGPIXELS      16

Adafruit_NeoPixel ring = Adafruit_NeoPixel(RINGPIXELS, PIN_r, NEO_GRB + NEO_KHZ800);

int delayval = 100;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;
const int relay = 12;
const int temp_pin = A0;

void setup(void)
{
  pinMode(relay,OUTPUT);
  pinMode(temp_pin, INPUT);
	
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(13, OUTPUT); // built-in led for button status: pressed or not
  ring.begin();
  Serial.begin(115200);
}

void loop(void)
{
  
  int sensorValue = analogRead(temp_pin); // Read analog value from the TMP36
  float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog value to voltage (if using a 5V microcontroller)
  float temperature = (voltage - 0.5) * 100.0; // Convert the voltage to temperature in degrees Celsius

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
   if (temperature > 5) // Set this to an appropriate value
   {
  		switchOn();
     	
      buttonState = digitalRead(buttonPin);
 
      setColor();

      for (int i=0; i < RINGPIXELS; i++)
      {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

        if (buttonState == HIGH)
        {
          digitalWrite(13, HIGH);

          if (i % 2 == 0)
          {
            ring.setPixelColor(i, ring.Color(255, 0, 0));
          }
          else
          {
            ring.setPixelColor(i, ring.Color(0, 0, 0));
          }

          }
          else
          {
            digitalWrite(13, LOW); // turn built-in LED off

            if (i % 2 == 1)
            {
                ring.setPixelColor(i, ring.Color(0, 255, 0));
            }
            else
            {
                ring.setPixelColor(i, ring.Color(0, 0, 0));
          }  
        }  
    
    ring.show();

    delay(delayval);
  }
 }
}
	


void switchOn(void)
{
  
  if(digitalRead(relay) == LOW)
  {
    
    digitalWrite(relay, HIGH);
    
  	delay(5000);  
    SwitchOff();
    
  }
  else
  {
  	// Do nothing
  }

  	
}

void SwitchOff()
{
	digitalWrite(relay,LOW);
}

void setColor(void)
{
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);
}
