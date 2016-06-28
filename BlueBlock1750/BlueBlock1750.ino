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
int buttonResetState = HIGH; //set reset button HIGH, so not pressing.

const int buttonDiscoverPin = 3; //discover button
int buttonDiscoverState = HIGH; //set Discover button HIGH, so not pressing.

void setup() {
  Serial.begin(9600);  //init serial monitor
  Serial.println("Start BlueBlock1750");
  swPort.begin(9600); //init software serial port with BC127

  pinMode(buttonResetPin, INPUT_PULLUP); //use internal pullup resistor w/ reset button
  pinMode(buttonDiscoverPin, INPUT_PULLUP);//use internal pullup resistor w/ discover button

  //*********SET DEFAULT VOLUME HERE**********


  //******************************************
}

void loop() {
  //Reset Mode
  //if reset buttonpressed, reset BC127
  buttonResetState = digitalRead(buttonResetPin);//check state of reset button
  buttonDiscoverState = digitalRead(buttonDiscoverPin); //check state of discover button

  if (buttonResetState == LOW) {
    BTModu.reset();//send command to reset
    Serial.println("Reset BC127");
  }

  //Advertising/Discover Mode
  //if button is pressed, switch to advertising/discover mode
  if (buttonDiscoverState == LOW) {
    BTModu.stdCmd("DISCOVERABLE ON");// //use discover command to turn ON
    //this will disconnect any that is currently paired
    Serial.println("Make BC127 Discoverable");
    //Note: If discoverable OFF (blue LED1 is blinking), you are not able to pair/connect
    //but you can still connect if you have previously paired
    //you might not see it when scanning
  }

}
