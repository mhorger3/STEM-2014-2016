/*
The Pennsylvania Governor’s STEM State Competition
BUILDING A STRONGER PENNSYLVANIA

Bishop Shanahan High School
Arduino Project File: Brilliantly_Bright_Second_Sign 

“Brilliantly Bright Solar LED Street Signs” 
Stephen Anderson, Angela Herb, Matthew Horger, Andrew Johnson, Conor Waldt
Advisor: John P. Janasik, PhD

*/ //     _________________
//       /.--------------.\
//      //                \\
//     //                  \\
//    || .-..----. .-. .--. ||
//    ||( ( '-..-'|.-.||.-.|||
//    || \ \  ||  || ||||_||||
//    ||._) ) ||  \'-'/||-' ||
//     \\'-'  `'   `-' `'  //
//      \\                //
//       \\______________//
//        '--------------'


// Stepper library import
#include <Stepper.h>
// include the library code:
#include <LiquidCrystal.h>

// variables declared
const int stepsPerRevolution = 200;  //  number of steps per revolution
int stepCount = 0; // number of steps the motor has taken
int state = 0; // bluetooth input data
int flag = 0; // serial print

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// initializes stepper motor instance on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 11, 12, 13);

void setup() {

  pinMode(9,OUTPUT); // turns on enA on driver
  pinMode(10,OUTPUT); // turns on enB on driver
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  Serial.begin(9600); // starts Bluetooth receive & motor functions
  
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.print("hello, world!"); // Print a message to the LCD.
}

void loop() {
  // put your main code here, to run repeatedly:
  
if(Serial.available() > 0) // if the Bluetooth data is being received
    {
     state = Serial.read(); // set its value into state
     flag = 0; // declared so our Serial doesn't loop
   }

 if (state == '0') // if the value received is a '0'
   {
     myStepper.step(1); // if 1 is being received, stepper motor takes 1 step
     stepCount++; // add one!
     delay(500); // about half a second
         if(flag == 0)
           {
             lcd.setCursor(0, 1);
             lcd.print("Closing"); // prints a message
             flag = 1; // no infinite serials thank you very much 
           }
   }

 else if (state == '1') // if the value received is a '1'
   {
     myStepper.step(-1); // if 1 is being received, stepper motor takes -1 step
     stepCount++; // add one!
     delay(500); // about half a second
          if(flag == 0)
            {
             lcd.setCursor(0, 1);
             lcd.print("Opening"); // prints a message
             flag = 1;
             }
   }
}
