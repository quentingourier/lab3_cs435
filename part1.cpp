/*----------------------------------------------------------------------------
LAB EXERCISE 3.1 - INTERRUPT IN/OUT
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the Mbed API functions to:
 
    1) Define InterruptIn and ISR for each button press
    2) In the interrupt service routine, the RGB LED is used to indicate when a
    button was pressed:
            + Button 1 - light RED
            + Button 2 - light BLUE
            + Button 3 - light GREEN
            + Button 4 - light WHITE (RED, GREEN and BLUE at the same time)
            
    3) Put the processor into sleep mode upon exiting from the ISR
            
    GOOD LUCK!
 *----------------------------------------------------------------------------*/
#include "mbed.h"


#define BUTTON_1 (PA_8)
#define BUTTON_2 (PB_10)
#define BUTTON_3 (PB_4)
#define BUTTON_4 (PB_5) 


//Define outputs
DigitalOut ledR(PB_6);
DigitalOut ledV(PC_7);
DigitalOut ledB(PA_9);


//Define interrupt inputs
InterruptIn b1_press(BUTTON_1);
InterruptIn b2_press(BUTTON_2);
InterruptIn b3_press(BUTTON_3);
InterruptIn b4_press(BUTTON_4);
   
//Define ISRs for the interrupts
void button_1_handler(){
    ledR = 1;
}


void button_2_handler(){
    ledV = 1;
}


void button_3_handler(){
    ledB = 1;
}


void button_4_handler(){
    ledR = ledV = ledB = 1;
}

void button_1_handler2(){
    ledR = 0;
}


void button_2_handler2(){
    ledV = 0;
}


void button_3_handler2(){
    ledB = 0;
}


void button_4_handler2(){
    ledR = ledV = ledB = 0;
}


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
    
    __enable_irq();         //enable interrupts
    
    ledR = ledV = ledB = 0; // I choose to turn off the led at the beginning

    b1_press.fall(&button_1_handler);
    b2_press.fall(&button_2_handler);
    b3_press.fall(&button_3_handler);
    b4_press.fall(&button_4_handler);
    
    b1_press.rise(&button_1_handler2);
    b2_press.rise(&button_2_handler2);
    b3_press.rise(&button_3_handler2);
    b4_press.rise(&button_4_handler2);

    while(1){
        __WFI();
    }
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2019*************************************
