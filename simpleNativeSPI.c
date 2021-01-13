#include <stdio.h>
#include <math.h>

//8051 HEADER
#include <at89c51cc03.h>

unsigned char bit DIN @ 0x92;
unsigned char bit LOAD @ 0x93;
unsigned char bit CLK @ 0x95;

signed char HIGH;
unsigned char LOW;

void SEND_SPI(unsigned char adr, unsigned char dat){
    unsigned char mask;
    int i;
    LOAD=0;
    mask=128;

    //SEND ADDRESS
    for(i=0;i<8;i++){
        if(adr&mask) DIN=1;
        else DIN=0;
        CLK=1;
        CLK=0;
        mask=mask/2;
    }

    //SEND DATA
    mask=128;
    for(i=0;i<8;i++){
        if(dat&mask) DIN=1;
        else DIN=0;
        CLK=1;
        CLK=0;
        mask=mask/2;
    }
    LOAD=1;
}

//MAIN
void main (void){
    //RESET
    LOAD=1;
    CLK=0;
}