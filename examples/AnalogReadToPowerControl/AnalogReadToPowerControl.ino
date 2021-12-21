#include  "dimmerMegaCore.h"

#define InterruptPin 2
#define TriacPin 13

int potValue = 0;
int duty;

void setup() {
  Serial.begin(115200);
  // begin(Interupt Pin, Triac Pin, Frequency (50/60 Hz), Output Active High or Low)
  dimmerMegaCore.begin(InterruptPin, TriacPin, 50, LOW);
}

void loop() {

  // read the analog in value:
  potValue = analogRead(A0);
  // map it to the range of the analog out: 1-100%
  duty = map(potValue, 0, 1023, 1, 100);
  
  Serial.print("duty : ");
  Serial.println(duty);
  dimmerMegaCore.setPower(duty);
  delay(100); 
}
