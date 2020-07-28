#include <vector>
#include "mbed.h"
#include "mpr121.h"
 
// Create the interrupt receiver object on pin 26
InterruptIn interrupt(p26);
I2C i2c(p9, p10);
BusOut solenoids(p13,p14,p15,p16,p17,p18,p19,p20);
Mpr121 mpr121(&i2c, Mpr121::ADD_VSS);
 volatile int value = 0;
float waittime = 1.0;
 
 // Key hit/release interrupt routine
 
void fallInterrupt()
{
    value = mpr121.read(0x00);
    value += mpr121.read(0x01)<<8;
}
 
// Function for Bernoulli distribution to control water flow pattern
vector<bool> f(double p, int n){
    vector<bool> my_vector;
    for(int i = 0; i<n; ++i){            
        my_vector.push_back((rand() %100 < 100*p));
    }    
    return my_vector;
}
 
int main()
 
{
 
    // setting up the interrupt
    interrupt.mode(PullUp);
    wait(.01);
    interrupt.fall(&fallInterrupt);
 
     while (1) { // individual solenoid control
        solenoids[7]= value & 0x01;
        solenoids[6]=(value>>1) & 0x01;
        solenoids[5]=(value>>2) & 0x01;
        solenoids[4]=(value>>3) & 0x01;
        solenoids[3]=(value>>4) & 0x01;
        solenoids[2]=(value>>5) & 0x01;
        solenoids[1]=(value>>6) & 0x01;
        solenoids[0]=(value>>7) & 0x01; 
 
        if ((value>>8) & 0x01) {
 
            // pattern 1
            solenoids[0] = 1;
            wait(waittime);
            solenoids[1] = 1;
            wait(waittime);
            solenoids[2] = 1;
            wait(waittime);
            solenoids[3] = 1;
            wait(waittime);
            solenoids[4] = 1;
            wait(waittime);
            solenoids[5] = 1;
            wait(waittime);
            solenoids[6] = 1;
            wait(waittime);
            solenoids[7] = 1;
            wait(waittime);
 
            solenoids[7] = 0;
            wait(waittime);
            solenoids[6] = 0;
            wait(waittime);
            solenoids[5] = 0;
            wait(waittime);
            solenoids[4] = 0;
            wait(waittime);
            solenoids[3] = 0;
            wait(waittime);
            solenoids[2] = 0;
            wait(waittime);
            solenoids[1] = 0;
            wait(waittime);
            solenoids[0] = 0;
            wait(waittime);
 
            // end of pattern 1
        }
 
        if ((value>>9) & 0x01) {
 
            // pattern 2
            solenoids[0] = 1;
            solenoids[7] = 1;
            wait(waittime);
            solenoids[1] = 1;
            solenoids[6] = 1;
            wait(waittime);
            solenoids[2] = 1;
            solenoids[5] = 1;
            wait(waittime);
 
            solenoids[3] = 1;
            solenoids[4] = 1;
            wait(waittime);
            solenoids[0] = 0;
            solenoids[7] = 0;
            wait(waittime);
            solenoids[1] = 0;
            solenoids[6] = 0;
            wait(waittime);
            solenoids[2] = 0;
            solenoids[5] = 0;
            wait(waittime);
            solenoids[3] = 0;
            solenoids[4] = 0;
            wait(waittime);
 
            // end of pattern 2
 
        }
 
        if ((value>>10) & 0x01) {
 
            // pattern 3
            solenoids[0] = 1;
            solenoids[1] = 1;
            solenoids[2] = 1;
            solenoids[3] = 1;
            solenoids[4] = 1;
            solenoids[5] = 1;
            solenoids[6] = 1;
            solenoids[7] = 1;
            wait(waittime);
 
            solenoids[0] = 0;
            wait(waittime);
            solenoids[7] = 0;
            wait(waittime);
            solenoids[1] = 0;
            wait(waittime);
            solenoids[6] = 0;
            wait(waittime);
            solenoids[2] = 0;
            wait(waittime);
            solenoids[5] = 0;
            wait(waittime);
            solenoids[3] = 0;
            wait(waittime);
            solenoids[4] = 0;
            wait(waittime);
 
            // end of pattern 3
 
        }
 
         if ((value>>11) & 0x01) {
 
            // pattern 4
 
            solenoids[0] = 1;
            wait(waittime);
            solenoids[0] = 0;
            solenoids[1] = 1;
            wait(waittime);
            solenoids[1] = 0;
            solenoids[2] = 1;
            wait(waittime);
            solenoids[2] = 0;
            solenoids[3] = 1;
            wait(waittime);
            solenoids[3] = 0;
            solenoids[4] = 1;
            wait(waittime);
            solenoids[4] = 0;
            solenoids[5] = 1;
            wait(waittime);
            solenoids[5] = 0;
            solenoids[6] = 1;
            wait(waittime);
            solenoids[6] = 0;
            solenoids[7] = 1;
            wait(waittime);
            solenoids[7] = 0;
 
            // end of pattern 4
        }
    }
}
