/* BlueBlock1750.ino
 by: Ho Yun "Bobby" Chan @ SparkFun Electronics
 June 28th, 2016

 Code to control the BC127 Audio Bluetooth at Block1750.

*/

#include <SparkFunbc127.h> //include library to communicate with BC127
#include <SoftwareSerial.h> // include software serial library

SoftwareSerial swPort(11, 10); // RX, TX
BC127 BTModu(&swPort);

//buttons
const int buttonResetPin = 2; //reset button
const int resetLEDPin = 8;    //red LED
int buttonResetState = HIGH; //set reset button HIGH, so not pressing.

const int buttonDiscoverPin = 3; //discover button
const int DiscoverLEDPin = 9; //blue LED
int buttonDiscoverState = HIGH; //set Discover button HIGH, so not pressing.

void setup() {
  Serial.begin(9600);  //init serial monitor
  Serial.println("Start BlueBlock1750");
  swPort.begin(9600); //init software serial port with BC127

  pinMode(buttonResetPin, INPUT_PULLUP); //use internal pullup resistor w/ reset button
  pinMode(resetLEDPin, OUTPUT);//big dome pushbutton LED
  digitalWrite(resetLEDPin, HIGH);//turn LED ON

  pinMode(buttonDiscoverPin, INPUT_PULLUP);//use internal pullup resistor w/ discover button
  pinMode(DiscoverLEDPin, OUTPUT);//big dome pushbutton LED
  digitalWrite(DiscoverLEDPin, LOW);//turn LED OFF since BC127 is in AUTOCONNECT MODE


  //Bluetooth volume default will be 11 (i.e. A2DP=11)
  //Example Tone to connect using Tone pg 26
  /*TONE TE 400 V 64 TI 0 N C5 L 8
                          N R0 L 32
                          N E5 L 8
                          N R0 L 32
                          N G5 L 8
                          N R0 L 32
                          N B5 L 4
                          N R0 L 1
                          N C6 L 2
                          TN C6 L 8*/
  BTModu.stdCmd("TONE TE 400 V 64 TI 0 N C5 L 8 N R0 L 32 N E5 L 8 N R0 L 32 N G5 L 8 N R0 L 32 N B5 L 4 N R0 L 1 N C6 L 2 TN C6 L 8");
  delay(5000);//try not to overload buffer, wait until done playing before playing next tone
  BTModu.stdCmd("TONE TE 400 V 64 TI 0 N C6 L 8 N R0 L 32 N B5 L 8 N R0 L 32 N G5 L 8 N R0 L 32 N E5 L 4 N R0 L 1 N C5 L 2 TN C5 L 8");
}

void loop() {
  //Reset Mode
  //if reset buttonpressed, reset BC127
  buttonResetState = digitalRead(buttonResetPin);//check state of reset button
  buttonDiscoverState = digitalRead(buttonDiscoverPin); //check state of discover button

  if (buttonResetState == LOW) {
    digitalWrite(resetLEDPin, LOW);//turn LED OFF
    BTModu.reset();//send command to reset
    BTModu.stdCmd("TONE TE 400 V 64 TI 0 N C5 L 8 N R0 L 32 N E5 L 8 N R0 L 32 N G5 L 8 N R0 L 32 N B5 L 4 N R0 L 1 N C6 L 2 TN C6 L 8");
    Serial.println("Reset BC127");

    delay(500);//short delay to see LED turn off when button pressed
    digitalWrite(resetLEDPin, HIGH);//turn LED ON
  }

  //Advertising/Discover Mode
  //if button is pressed, switch to advertising/discover mode
  else if (buttonDiscoverState == LOW) {
    //check if in discover mode...

    digitalWrite(DiscoverLEDPin, HIGH);//turn LED ON
    BTModu.stdCmd("DISCOVERABLE ON");// //use discover command to turn ON
    BTModu.stdCmd("TONE TE 400 V 64 TI 0 N C6 L 8 N R0 L 32 N B5 L 8 N R0 L 32 N G5 L 8 N R0 L 32 N E5 L 4 N R0 L 1 N C5 L 2 TN C5 L 8");
    //this will disconnect any that is currently paired
    Serial.println("Make BC127 Discoverable");
    //Note: If discoverable OFF (blue LED1 is blinking), you are not able to pair/connect
    //but you can still connect if you have previously paired
    //you might not see it when scanning

    delay(500);//short delay to see LED turn off when button pressed
    digitalWrite(DiscoverLEDPin, LOW);//turn LED OFF
  }

}
