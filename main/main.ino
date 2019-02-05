#include <IRLib.h>   // In {path_of_installation}/Digispark-Arduino-1.0.x/libraries/DigisparkIRLib/IRLib.h, set MY_PROTOCOL to NEC, SONY, RC5 to find the one used by your own IR Remote Control
#include "DigiKeyboard.h"
/*
   _____     ____      __    _    ____    _    _   _     _ 
  |  __ \   / __ \    |  \  | |  / __ \  | |  | | | |   | |
  | |__| | | /  \_|   | . \ | | / /  \ \ | |  | |  \ \ / /
  |  _  /  | |   _    | |\ \| | | |__| | | |  | |   \ ' /
  | | \ \  | \__/ |   | | \ ' | |  __  |  \ \/ /     | |
  |_|  \_\  \____/    |_|  \__| |_|  |_|   \__/      |_| 2013

                http://p.loussouarn.free.fr

         *************************************************
         *      Optimized <IRLib> library Dump Demo      *
         *************************************************

This sketch allows you to discover the protocol used by your own IR Remote Control and the code of each key when pressed.
You will see the decoded key codes in the DigiUSB console.

IMPORTANT:
=========
- In {path_of_installation}/Digispark-Arduino-1.0.x/libraries/DigisparkIRLib/IRLib.h, set MY_PROTOCOL to NEC, SONY, RC5 to find the protocol used by your own IR Remote Control
- In {path_of_installation}/Digispark-Arduino-1.0.x/libraries/DigisparkUSB/DigiUSB.h, RING_BUFFER_SIZE shall be set to 32

 Sensor wiring: (Warning: the wiring may vary depending of the model of IR sensor)
 =============
        .-------.
        |  ___  |
        | /   \ | InfraRed
        | \___/ |  Sensor
        |       |
        '+--+--+'
         |  |  |      100
 P5 <----'  |  '--+---###--- +5V
            |     |
            |   '==='4.7uF
            |     |
            '--+--'
               |
              GND

*/

#define LED_PIN    1
#define IR_RX_PIN  0

#define BUTTON_OFF           0xF740BF //Set here the OFF code for the built-in LED when determined
#define BUTTON_ON            0xF7C03F //Set here the ON  code for the built-in LED when determined
//canonc RS02 buttons
#define left_arrow           0x8160926D
#define right_arrow          0x816052AD
#define up_arrow             0x8160E21D
#define down_arrow           0x816012ED
#define ok                   0x81605AA5


//these depend on windows numpad mouse beeing activated TODO:find out the correct name of this feature
#define MOUSE_UP             0x000068
#define MOUSE_DOWN           0x000068
#define MOUSE_LEFT           0x000068
#define MOUSE_RIGHT          0x000068
#define MOUSE_LEFT_CLICK     0x000068

IRrecv   My_Receiver(IR_RX_PIN);//Receive on pin IR_RX_PIN
IRdecode My_Decoder; 

void setup() 
{   
  //DigiKeyboard.println("started setup for receiver");
  My_Receiver.enableIRIn(); // Start the receiver
  pinMode(LED_PIN, OUTPUT);  
  pinMode(IR_RX_PIN, INPUT);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println("started to listen for IR signals");
  
} 

void loop() 
{   

  if(My_Receiver.GetResults(&My_Decoder))
  {
    My_Decoder.decode();
    //DigiKeyboard.println(My_Decoder.value, HEX);

    switch(My_Decoder.value)
    {
    case left_arrow:
      DigiKeyboard.sendKeyPress(MOUSE_LEFT);
      break;
    case right_arrow:
      DigiKeyboard.sendKeyPress(MOUSE_RIGHT);
      break;
    case up_arrow:
      DigiKeyboard.sendKeyPress(MOUSE_UP);
      break;
    case down_arrow:
      DigiKeyboard.sendKeyPress(MOUSE_DOWN);
      break;
    case ok:
      DigiKeyboard.sendKeyPress(MOUSE_LEFT_CLICK);
      break;
    default:break;
    }
    My_Receiver.resume();
    
  }

}
