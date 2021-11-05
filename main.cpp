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
#include <iostream>

using namespace std;

#define BUTTON_1 D2
#define BUTTON_2 D3 
#define BUTTON_3 D4 
#define BUTTON_4 D5 


//Define outputs
DigitalOut ledR(PB_10);
DigitalOut ledV(PA_8);
DigitalOut ledB(PA_9);

//Define counters
int cb1 = 0, cb2 = 0, cb3 = 0;

//Define interrupt inputs
InterruptIn b1_press(BUTTON_1);
InterruptIn b2_press(BUTTON_2);
InterruptIn b3_press(BUTTON_3);
InterruptIn b4_press(BUTTON_4);
   
//Define ISRs for the interrupts
void button_1_handler(){
    cb1++;
}


void button_2_handler(){
    cb2++;
}


void button_3_handler(){
    cb3++;
}


void button_4_handler(){
    cb1 = 0, cb2 = 0, cb3 = 0;
    ledR = 0, ledV = 0, ledB = 0;
}


void update(){

    ThisThread::sleep_for(1500ms);

    ledR = (cb1) && (cb1 >= cb2 && cb1 >= cb3);
    ledV = (cb2) && (cb2 >= cb1 && cb2 >= cb3);
    ledB = (cb3) && (cb3 >= cb1 && cb3 >= cb2);
    
}


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	
	__enable_irq();			//enable interrupts
	
    cb1 = cb2 = cb3 = 0;    //turning off initialization
    ledR = ledV = ledB = 0;

    b1_press.fall(&button_1_handler);
    b2_press.fall(&button_2_handler);
    b3_press.fall(&button_3_handler);
    b4_press.fall(&button_4_handler);

	while(1){
        __WFI();
        printf("\ncb1 = %d\n", cb1);
        printf("cb2 = %d\n", cb2);
        printf("cb3 = %d\n", cb3);
        update();
        ThisThread::sleep_for(2s);
    }
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2019*************************************
