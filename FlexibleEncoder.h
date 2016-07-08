// Defines a flexible quadrature encoder that can use hardware or
// pin-change interrupts. Uses the EnableInterrupt library.

#ifndef FlexibleEncoder_h
#define FlexibleEncoder_h

class Encoder
{
 public:
  Encoder(uint8_t pin1, uint8_t pin2);

  int32_t read();

  void write(int32_t value);

  void update();
  
 private:
  int pinA;
  int pinB;
  volatile int32_t ticks;
};

#endif //FlexibleEncoder_h
