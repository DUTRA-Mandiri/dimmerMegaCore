/*  20 december 2021
 *  DUTRA Mandiri - Ichfan Arif Widyanto - Surabaya, Indonesia 
 *
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  
 *  Used hardware timer1 based on TimerOne Library by PaulStoffregen
 *  https://github.com/PaulStoffregen/TimerOne
 *  And
 *  Adapted from sketch by Ed1960
 *  https://codebender.cc/sketch:171819#AC-Dimmer-Timer%20Driven.ino
 */
  
#include "Arduino.h"  
#include "dimmerMegaCore.h"	

DimmerMegaCore dimmerMegaCore;

#if defined (__AVR_ATmega8__) || defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__)
#define TIMSK1 TIMSK
#endif
	
volatile byte Triac_Pin;
volatile int i;             
volatile boolean zero_cross;
long freqStep, dim;
byte turnON, turnOFF;

const int8_t DimmerPower[] = {
   2,  3,  4,  6,  7,  8, 9, 11, 12, 13,
  15, 16, 17, 18, 20, 21, 22, 24, 25, 26,
  27, 29, 30, 31, 32, 34, 35, 36, 38, 39,
  40, 41, 43, 44, 45, 46, 47, 49, 50, 52,
  53, 54, 56, 57, 58, 59, 61, 62, 63, 64,
  66, 67, 68, 70, 71, 72, 73, 75, 76, 77,
  78, 80, 81, 82, 84, 85, 86, 87, 88, 90,
  91, 93, 94, 95, 96, 98, 99, 100, 102, 103,
  104, 105, 106, 107, 108, 109, 110, 112, 113, 114,
  115, 116, 117, 118, 120, 121, 123, 125, 126, 127 };

void ZCdetected() {
	zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
	i = 0;
	digitalWrite(Triac_Pin, turnOFF);       // turn off TRIAC
} 

void dim_check() {                   
  if(zero_cross == true) {              
    if(i>=dim) {                     
      digitalWrite(Triac_Pin, turnON); // turn on TRIAC       
      i=0;                          
      zero_cross = false; 
    } 
    else {
      i++;                     
    }                                
  }                                  
}       

void DimmerMegaCore::setPower(long val){
	dim = DimmerPower[val-1];
}

void DimmerMegaCore::begin(byte INT_Pin, byte triac_Pin, long Freq, bool ConfOutput) {
	
	pinMode(INT_Pin, INPUT_PULLUP);
	pinMode(triac_Pin, OUTPUT);
	
	attachInterrupt(digitalPinToInterrupt(INT_Pin), ZCdetected, RISING);
	
	Triac_Pin = triac_Pin;
	freqStep = _freqStep;
	dim = _dim;
	turnON = _ON;
	turnOFF = _OFF;
	
	if (Freq == 50) {
		freqStep = 600;
	}
	else {
		freqStep = 520;
	}
	
	if (ConfOutput) {
		turnON = HIGH;
		turnOFF = LOW;
	}
	else {
		turnON = LOW;
		turnOFF = HIGH;
	}
	
	TCCR1B = _BV(WGM13);        
	TCCR1A = 0;                 
	ICR1 = freqStep;
	TCCR1B = _BV(WGM13) | _BV(CS10);
	TIMSK1 = _BV(TOIE1);
}

ISR(TIMER1_OVF_vect)
{
  dim_check();
}