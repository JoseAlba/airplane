// Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:

#include <LiquidCrystal.h>

// Initialize the library with the pins

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int trigPin=9; //Sensor Trig pin connected to Arduino pin 13
int echoPin=8;  //Sensor Echo pin connected to Arduino pin 11
float pingTime;  //time for ping to travel from sensor to target and return
float targetDistance; //Distance to Target in inches
float speedOfSound=776.5; //Speed of sound in miles per hour when temp is 77 degrees.
int LEDpin=13;

void setup() 
{
  //Open serial for reading, set VOD rate -- VERY IMPORTANT to
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDpin, OUTPUT);
	lcd.begin(16, 2); //Initialize the 16x2 LCD


	lcd.clear();	//Clear any old data displayed on the LCD


	lcd.print("Distance in inches"); // Display a message on the LCD!
}

void loop()
{
  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in low state
  
  pingTime = pulseIn(echoPin, HIGH);  //pingTime is presented in microceconds
  pingTime=pingTime/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //convert pingtime to hourse by dividing by 3600 (seconds in an hour)
  targetDistance= speedOfSound * pingTime;  //This will be in miles, since speed of sound was miles per hour
  targetDistance=targetDistance/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  targetDistance= targetDistance*63360;    //Convert miles to inches by multipling by 63360 (inches per mile)
  
  Serial.println(targetDistance);
  
  delay(100); //delay tenth of a  second to slow things down a little.
	lcd.setCursor(0, 1); 	//Set the (invisible) cursor to column 0, // row 1.

  if(targetDistance < 15) //Checks distance to make sure it's low enough to read -- makes sure it ignores large numbers that are hard to format
  {
	lcd.print(targetDistance); //Print the distance from the ultrasound to the object
  if(targetDistance < 3)
    digitalWrite(LEDpin, HIGH);
  else
    digitalWrite(LEDpin, LOW);
  }
}
