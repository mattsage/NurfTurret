/* Basic_PIR_Servo
  by romand
  based upon: http://www.instructables.com/id/Arduino-PIR-Motion-Sensor
  and Sweep example from http://www.arduino.cc/en/Tutorial/sweep
*/

#include <Servo.h>

Servo myservo;                  // create servo object to control a servo
int posMotion = 80;             // variable to store the servo position when movement detected
int posNoMotion = 120;          // variable to store the servo position when movement stoped
int servoOutputPin = 7;         // choose the output pin for the servo
int pirInputPin = 2;            // choose the input pin (for PIR sensor)
int val = 0;                    // variable for reading the pin status
int pirState = LOW;             // we start, assuming no motion detected
int delayTime = 2000;           // variable to set delay time

void setup()
{
  //pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(servoOutputPin);  // attaches the servo on servoOutputPin to the servo object
  pinMode(pirInputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);              // Sets the data rate in bits per second (baud) for serial data transmission
}

void loop()
{
    //delay(delayTime);  
    //digitalWrite(LED_BUILTIN, HIGH);       // Light LED
    val = digitalRead(pirInputPin);          // read input value
    if ((val == HIGH)&&(pirState == LOW)) {  // check if the input is HIGH and currently we are LOW - check if PIR detected motion, and check that its not still the previous loop motion so we wouldn't ask the servo to move again to the same location
    // we have just turned on
    Serial.println("Motion detected!");    // print test
    pirState = HIGH;                       // motion detected, so pirState currently set to high - the servo is in the "motion detected" state
    myservo.write(posMotion);              // tell servo to go to position in variable 'posMotion'
    delay(delayTime);                      // waits delayTime for until we are ready for the next motion signal (should also consider the time screw on the PIR sensor itself)
  }
  else if(pirState == HIGH){               // anyway when servo is in posMotion state, and delayTime is passed, enter this else-if
    // we have just turned off
    Serial.println("Motion ended!");       // print test
    pirState = LOW;                        // return pirState value to wait until next movement
    myservo.write(posNoMotion);            // tell servo to go to position in variable 'pos'
    delay(delayTime);                      // waits 15ms for the servo to reach the pos
  }
}

