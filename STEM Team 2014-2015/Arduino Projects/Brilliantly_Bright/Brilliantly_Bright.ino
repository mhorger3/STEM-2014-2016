/*
The Pennsylvania Governor’s STEM State Competition
BUILDING A STRONGER PENNSYLVANIA

Bishop Shanahan High School
Arduino Project File: Brilliantly_Bright 

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

// variables declared
const int stepsPerRevolution = 200;  //  number of steps per revolution
int stepCount = 0; // number of steps the motor has taken
int ledpin = 6; // LED lights (white) on pin 6
int ledpin2 = 7; // LED lights (red) on pin 7
int state = 0; // bluetooth input data
int flag = 0; // serial print

// initializes stepper motor instance on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // put your setup code here, to run once:

  pinMode(ledpin,OUTPUT); // sets pin 6 output
  pinMode(ledpin2,OUTPUT); // sets pin 7 output
  Serial.begin(9600); // starts Bluetooth receive & motor functions
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
     digitalWrite(ledpin, LOW); // white off
     digitalWrite(ledpin2,HIGH); // red on
     
         if(flag == 0)
           {
             Serial.println("LED: off"); // prints a message
             flag = 1; // no infinite serials thank you very much 
           }
   }

 else if (state == '1') // if the value received is a '1'
   {
     digitalWrite(ledpin, HIGH); // white on
     digitalWrite(ledpin2,LOW); // red off
     
          if(flag == 0)
            {
             Serial.println("LED: on");
             flag = 1;
             }
             
     myStepper.step(1); // if 1 is being received, stepper motor takes 1 step
     Serial.print("steps: " + stepCount ); // serial step count printout
     stepCount++; // add one!
     delay(500); // about half a second
   }
}
