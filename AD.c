/*
 * File:   AD.c
 * Author: kakac
 *
 * Created on 3 de Setembro de 2019, 21:13
 */

#include <xc.h>
#define _XTAL_FREQ 200000000
#include <pic16f877a.h>
#include <pic.h>

int init(){
    TRISA = 0xFF;
    TRISD = 0x00;
    ADC_init();
    return 0;
}

unsigned int ADC_reader(unsigned char channel){
    unsigned int read;
    ADCON0 = ADCON0 & 0xC7;
    ADCON0 = ADCON0 | (channel<<3);
    __delay_ms(2);
    GO_nDONE = 1; // INICIO DA CONVERÇÃO
    while(GO_nDONE);
    read = (ADRESH<<8)+ADRESL;
    return read;
}

int ADC_init(){
    ADCON0 = 0x81;
    ADCON1 = 0x80;
    return 0;
}

void main() {
    unsigned int read = 0, aux = 128;
    init();
    while(1){
        read = ADC_reader(2);
        if(read <= aux){
            PORTD = 0b00000001;
        }
        else if(read <= aux*2){
            PORTD = 0b00000011;
        }
        else if(read <= aux*3){
            PORTD = 0b00000111;
        }
        else if(read <= aux*4){
            PORTD = 0b00001111;
        }
        else if(read <= aux*5){
            PORTD = 0b00011111;
        }
        else if(read <= aux*6){
            PORTD = 0b00111111;
        }
        else if(read <= aux*7){
            PORTD = 0b01111111;
        }
        else if(read <= aux*8){
            PORTD = 0b11111111;
        }
        else {
            PORTD = 0b11111111;
            __delay_ms(500);
            PORTD = 0b00000000;
            __delay_ms(500);
            
        }
    }
}