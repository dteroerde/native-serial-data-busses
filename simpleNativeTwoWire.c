#include <stdio.h>
#include <math.h>

//8051 HEADER
#include <at89c51cc03.h>

unsigned char bit SDA @ 0xc0;
unsigned char bit SCL @ 0xc1;

signed char HIGH;
unsigned char LOW;

//GENERATE START CONDITION
void TWO_WIRE_START(void){
    SDA = 1;
    SCL = 1;
    SDA = 0;
}

//GENERATE STOP CONDITION
void TWO_WIRE_STOP(void){
    SDA=0;
    SCL=1;
    SDA=1;
}

//GENERATE ONE BYTE FOR OUTPUT
void TWO_WIRE_SEND(unsigned char Data)
{
    unsigned char i;
    unsigned char mask = 128;
    SCL = 0; //SET CLOCK TO LOW

    //8 BITS = 1 BYTE
    for(i=0; i<8; i++){
        if(Data & mask) SDA = 1;
        else SDA = 0;
        SCL = 1;
        mask = mask / 2;
        SCL = 0;
    }
    //RECEIVE ACK/NACK FROM SLAVE
    SDA = 1;
    SCL = 1;
    if(SDA){
        printf("ERROR\n");
        printf("GET NO ACK FROM SLAVE\n");
        while(1);
    }
    SCL = 0;
}

//READ BYTE FROM SLAVE
unsigned char TWO_WIRE_RECV(void){
    unsigned char ergebnis=0;
    unsigned char i, value=128;
    SCL = 0; //SET CLOCK TO LOW
    SDA = 1;
    //8 BITS = 1 BYTE
    for(i=0; i<8; i++)
    { 
        SCL = 1; //CLOCK HIGH
        if(SDA) ergebnis = ergebnis + value;
        SCL = 0; //CLOCK LOW
        value = value/2;
    }
        return ergebnis;
}

//MASTER SEND POSITIVE ACKNOWLEDGE
void TWO_WIRE_Master_ACK(void){
    SDA = 0;
    SCL = 1;
    SCL = 0;
    SDA = 1;
}

//MASTER SEND NEGATIVE ACKNOWLEDGE
void TWO_WIRE_Master_NACK(void){
    SDA = 1;
    SCL = 1;
    SCL = 0;
}

//MAIN
void main (void){
    //RESET
    SDA=1; SCL=1;
}