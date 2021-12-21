#include  "dimmerMegaCore.h"

#define InterruptPin 2
#define TriacPin 13

void setup() {
  Serial.begin(115200);
  // begin(Interupt Pin, Triac Pin, Frequency (50/60 Hz), Output Active High or Low)
  dimmerMegaCore.begin(InterruptPin, TriacPin, 50, LOW);
}

void loop() {
  for (byte i = 1; i < 99; i++) {
    Serial.println(i);
    dimmerMegaCore.setPower(i);
    delay(20);
  }

  for (byte i = 100; i > 2; i--) {
    Serial.println(i);
    dimmerMegaCore.setPower(i);
    delay(20);
  }
}
