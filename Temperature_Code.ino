/*
SparkFun Inventor's Kit
Example sketch 15

LIQUID CRYSTAL DISPLAY (LCD)

  A Liquid Crystal Display (LCD) is a sophisticated module
  that can be used to display text or numeric data. The display
  included in your SIK features two lines of 16 characters, and
  a backlight so it can be used at night.

  If you've been using the Serial Monitor to output data,
  you'll find that a LCD provides many of the same benefits
  without needing to drag a large computer around.

  This sketch will show you how to connect an LCD to your Arduino
  and display any data you wish.


This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn about the Arduino.

Version 1.0 2/2013 MDG
*/

// Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:

#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int temperaturePin = A0;

void setup()
{

	lcd.begin(16, 2); //Initialize the 16x2 LCD


	lcd.clear();	//Clear any old data displayed on the LCD


}

void loop()
{

  float voltage, degreesC, degreesF; //Declare 3 floating point variables

  voltage = getVoltage(temperaturePin); //Measure the voltage at the analog pin

  degreesC = (voltage - 0.5) * 100.0; // Convert the voltage to degrees Celsius

  degreesF = degreesC * (9.0 / 5.0) + 32.0; //Convert degrees Celsius to Fahrenheit
  
  //Now print to the Serial monitor. Remember the baud must be 9600 on your monitor!
  // These statements will print lines of data like this:
  // "voltage: 0.73 deg C: 22.75 deg F: 72.96"
  
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("  deg C: ");
  Serial.print(degreesC);
  Serial.print("  deg F: ");
  Serial.println(degreesF);


  delay(1000);
  lcd.clear();


  lcd.print("Temperature");
	lcd.setCursor(0, 1); 	//Set the (invisible) cursor to column 0,
							// row 1.

	lcd.print(degreesC); //Print the number of seconds
								//since the Arduino last reset.
  lcd.print("C   ");
  lcd.print(degreesF);
  lcd.print("F");
}

float getVoltage(int pin)   //Function to read and return
              //floating-point value (true voltage)
              //on analog pin 
{

  return (analogRead(pin) * 0.004882814); 
  // This equation converts the 0 to 1023 value that analogRead()
  // returns, into a 0.0 to 5.0 value that is the true voltage
  // being read at that pin.
}

// Other things to try with this code:

//   Turn on an LED if the temperature is above or below a value.

//   Read that threshold value from a potentiometer - now you've
//   created a thermostat!

