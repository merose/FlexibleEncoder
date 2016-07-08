// Implements a quadrature encoder that uses the either hardware or
// pin-change interrupts by using the EnableInterrupt library.
//
// The sense of positive rotation is copied from the PJRC Encoder
// library. If (pinA,pinB) is the state of the encoder pins, then
// positive rotation is given by:
//     (0,0) --> (0,1) --> (1,1) --> (1,0) --> (0,0)
// We detect this rotation by interrupting on pinA only, so if
// pinA==pinB when pinA changes, we are rotating in the positive
// direction, otherwise the negative direction.

#include <Arduino.h>
#include <EnableInterrupt.h>
#include "FlexibleEncoder.h"

static const int MAX_PINS = 14;

static Encoder *encoderForPin[MAX_PINS];

static void isr0() {encoderForPin[0]->update();}
static void isr1() {encoderForPin[1]->update();}
static void isr2() {encoderForPin[2]->update();}
static void isr3() {encoderForPin[3]->update();}
static void isr4() {encoderForPin[4]->update();}
static void isr5() {encoderForPin[5]->update();}
static void isr6() {encoderForPin[6]->update();}
static void isr7() {encoderForPin[7]->update();}
static void isr8() {encoderForPin[8]->update();}
static void isr9() {encoderForPin[9]->update();}
static void isr10() {encoderForPin[10]->update();}
static void isr11() {encoderForPin[11]->update();}
static void isr12() {encoderForPin[12]->update();}
static void isr13() {encoderForPin[13]->update();}

Encoder::Encoder(uint8_t pin1, uint8_t pin2)
  : pinA(pin1), pinB(pin2), ticks(0)
{
  if (pin1 < MAX_PINS) {
    encoderForPin[pin1] = this;
  }

  switch (pin1) {
  case 0: enableInterrupt(0, isr0, CHANGE); break;
  case 1: enableInterrupt(1, isr1, CHANGE); break;
  case 2: enableInterrupt(2, isr2, CHANGE); break;
  case 3: enableInterrupt(3, isr3, CHANGE); break;
  case 4: enableInterrupt(4, isr4, CHANGE); break;
  case 5: enableInterrupt(5, isr5, CHANGE); break;
  case 6: enableInterrupt(6, isr6, CHANGE); break;
  case 7: enableInterrupt(7, isr7, CHANGE); break;
  case 8: enableInterrupt(8, isr8, CHANGE); break;
  case 9: enableInterrupt(9, isr9, CHANGE); break;
  case 10: enableInterrupt(10, isr10, CHANGE); break;
  case 11: enableInterrupt(11, isr11, CHANGE); break;
  case 12: enableInterrupt(12, isr12, CHANGE); break;
  case 13: enableInterrupt(13, isr13, CHANGE); break;
  }
}

int32_t Encoder::read() {
  noInterrupts();
  int32_t tempTicks = ticks;
  interrupts();

  return tempTicks;
}

void Encoder::write(int32_t value) {
  noInterrupts();
  ticks = value;
  interrupts();
}

void Encoder::update() {
  if (digitalRead(pinA) == digitalRead(pinB)) {
    ++ticks;
  } else {
    --ticks;
  }
}
