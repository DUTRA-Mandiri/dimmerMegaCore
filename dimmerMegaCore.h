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
 
 
#ifndef DimmerMegaCore_h
#define DimmerMegaCore_h

#include "Arduino.h"  

static void ZCdetected();

class DimmerMegaCore
{
  public:
  
  // Begin(Interupt Pin, Triac Pin, Frequency (50/60 Hz), Output Active High or Low)
  void begin(byte INT_Pin, byte triac_Pin, long Freq, bool ConfOutput);
  
  void setPower(long val);
	
  private:
	long _freqStep;
	long _dim;
	byte _ON;
	byte _OFF;

};

extern DimmerMegaCore dimmerMegaCore;

#endif