const int pir = 1;
const int relay = 12;
const int temp_pin = A0;

void setup(void)
{
	pinMode(pir,INPUT);
  	pinMode(relay,OUTPUT);
  	pinMode(temp_pin, INPUT);
  
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
  
   if (temperature > 20) // Set this to an appropriate value
   {
  		switchOn();  
   }

}

void switchOn(void)
{
  
  if(digitalRead(relay) == LOW)
  {
    
	  digitalWrite(relay,HIGH);
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
