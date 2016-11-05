/* BlueBlock1750v3.ino
 by: Ho Yun "Bobby" Chan @ SparkFun Electronics
 November 1st, 2016
 
 Code to connect/disconnect a source device to the
 BC127 audio bluetooth (sink) @ Block1750.
 
 Name is BlueBlock1750:
 set name=BlueBlock1750
 Bluetooth is set to sink:
 set classic_role=0
 The autoconnect is turned off:
 set autoconn=1
 HFP is turned off:
 set enable_hfp=off
 
 This code turns the BC127's default volume to the max.
 THe BC127's volume is different from the source device's volume.
 
 Modes:
 1.) Reset Mode will reset the BC127.
 2.) Discover Mode will disconnect any device currently 
 connected w/ BC127 and make the audio bluetooth discoverable.
 */

#include <SparkFunbc127.h> //include library to communicate with BC127
#include <SoftwareSerial.h> // include software serial library

SoftwareSerial swPort(10, 11); // RX, TX
BC127 BTModu(&swPort);

//buttons
const int buttonResetPin = 2; //reset button
const int resetLEDPin = 8;    //red LED
int buttonResetState = HIGH; //set reset button HIGH, so not pressing
//keep track if reset button press when held down
boolean prev_buttonResetState = false;
boolean current_buttonResetState = false;



const int buttonDiscoverPin = 3; //discover button
const int DiscoverLEDPin = 9; //blue LED
int buttonDiscoverState = HIGH; //set Discover button HIGH, so not pressing.
//keep track if discovery mode button press when held down
boolean prev_buttonDiscoverState = false;
boolean current_buttonDiscoverState = false;

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

  //restore configuration for BlueBlock1750 in case VREGEN pressed...
  /*1.) Name is BlueBlock1750:
   set name=BlueBlock1750
   2.) Bluetooth is set to sink:
   set classic_role=0
   3.) The autoconnect is turned off:
   set autoconn=1
   4.) HFP is turned off:
   set enable_hfp=off
   */
  BTModu.stdCmd("restore");
  delay(300);
  BTModu.stdCmd("set name=BlueBlock1750");//name
  delay(300);
  BTModu.stdCmd("set classic_role=0");//set to sink
  delay(300);
  BTModu.stdCmd("set autoconn=1"); //set autoconn
  delay(300);
  BTModu.stdCmd("set enable_hfp=off");//turn off hfp
  delay(300);
  BTModu.stdCmd("write");
  delay(300);
  BTModu.reset();//send command to reset
  delay(1000);

  /*Bluetooth volume default will be 11 (i.e. A2DP=11)
   so turn volume up to max on startup*/
  BTModu.stdCmd("VOLUME UP");//turn volume up
  delay(300);//add delay so BC127 take commands
  BTModu.stdCmd("VOLUME UP");
  delay(300);
  BTModu.stdCmd("VOLUME UP");
  delay(300);
  BTModu.stdCmd("VOLUME UP");
  delay(300);

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

  buttonResetState = digitalRead(buttonResetPin);//check state of reset button
  buttonDiscoverState = digitalRead(buttonDiscoverPin); //check state of discover button

    //----------Reset Mode----------
  //if reset button pressed, reset BC127
  if(buttonResetState == LOW){
    current_buttonResetState = true; //button has been pressed

    if(prev_buttonResetState != current_buttonResetState){
      digitalWrite(resetLEDPin, LOW);//turn LED OFF
      BTModu.stdCmd("restore");
      delay(300);
      BTModu.stdCmd("set name=BlueBlock1750");//name
      delay(300);
      BTModu.stdCmd("set classic_role=0");//set to sink
      delay(300);
      BTModu.stdCmd("set autoconn=1"); //set autoconn
      delay(300);
      BTModu.stdCmd("set enable_hfp=off");//turn off hfp
      delay(300);
      BTModu.stdCmd("write");
      delay(300);
      BTModu.reset();//send command to reset
      delay(1000);

      BTModu.stdCmd("VOLUME UP");//turn volume up
      delay(300);//add delay so BC127 take commands
      BTModu.stdCmd("VOLUME UP");
      delay(300);
      BTModu.stdCmd("VOLUME UP");
      delay(300);
      BTModu.stdCmd("VOLUME UP");
      delay(300);
      BTModu.stdCmd("TONE TE 400 V 64 TI 0 N C5 L 8 N R0 L 32 N E5 L 8 N R0 L 32 N G5 L 8 N R0 L 32 N B5 L 4 N R0 L 1 N C6 L 2 TN C6 L 8");
      Serial.println("Reset BC127");
    }
    prev_buttonResetState = current_buttonResetState;//update Reset button's state
  }
  else if(buttonResetState == HIGH){
    current_buttonResetState = false;//button has not been pressed
    if(prev_buttonResetState != current_buttonResetState){
      digitalWrite(resetLEDPin, HIGH);//turn LED back on
      Serial.println("turn led back on");
    }
    prev_buttonResetState = current_buttonResetState;//update Reset button's state
  }



  //----------Advertising/Discover Mode----------
  //if button is pressed, switch to advertising/discover mode
  if(buttonDiscoverState == LOW){
    current_buttonDiscoverState = true; //button has been pressed

    if(prev_buttonDiscoverState != current_buttonDiscoverState){
      digitalWrite(DiscoverLEDPin, HIGH);//turn LED ON
      BTModu.stdCmd("DISCOVERABLE ON");// //use discover command to turn ON
      //this will disconnect any that is currently paired
      BTModu.stdCmd("TONE TE 400 V 64 TI 0 N C6 L 8 N R0 L 32 N B5 L 8 N R0 L 32 N G5 L 8 N R0 L 32 N E5 L 4 N R0 L 1 N C5 L 2 TN C5 L 8");
      Serial.println("Make BC127 Discoverable");
      //Note: If discoverable OFF (blue LED1 is blinking), you are not able to pair/connect
      //but you can still connect if you have previously paired
      //you might not see it when scanning
    }
    prev_buttonDiscoverState = current_buttonDiscoverState;//update Discover button's state
  }
  else if(buttonDiscoverState == HIGH){
    current_buttonDiscoverState = false;// button has not been pressed
    if(prev_buttonDiscoverState != current_buttonDiscoverState){
      digitalWrite(DiscoverLEDPin, LOW);//turn LED OFF
    }
    prev_buttonDiscoverState = current_buttonDiscoverState;//update Discover button's state
  }

}//end loop

/*check...
 OPEN_OK A2DP
 OPEN_OK AVRCP
 
 connected...
 STATE CONNECTED
 LINK 2 CONNECTED A2DP 281878D6E826 SBC 44100
 LINK 4 CONNECTED AVRCP 281878D6E826 PLAYING
 
 disable OPEN_OK HFP....
 set enable_hfp=off
 write
 reset
 */





