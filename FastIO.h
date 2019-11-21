#ifndef	FASTIO_H
#define	FASTIO_H

#include <arduino.h>

#ifdef ARDUINO_ARCH_AVR
#define REGTYPE uint8_t   // AVR uses 8-bit registers
#else
#define REGTYPE uint32_t
#endif

struct IO {
  REGTYPE bitmask;
  volatile REGTYPE *reg;
};

inline struct IO set_IO(uint8_t pin, uint8_t io)
{
  struct IO temp;
  REGTYPE port = digitalPinToPort(pin);
  volatile REGTYPE *mode;

  temp.bitmask = digitalPinToBitMask(pin);

  if (port == NOT_A_PIN) return;

  mode = portModeRegister(port);

  if (io == OUTPUT) {
    temp.reg = portOutputRegister(port);
    *mode |= temp.bitmask;
  }
  else {
    *mode &= ~temp.bitmask;
    temp.reg = portInputRegister(port);
    //*temp.reg &= ~temp.bitmask;
    if (io == INPUT_PULLUP)*temp.reg |= temp.bitmask;
  }

  return temp;
}

inline bool dig_read(struct IO in) {
  REGTYPE temp = *in.reg & in.bitmask;

  if (temp) return 1;

  return 0;
}

inline void dig_write(struct IO out, uint8_t logic) {

  if (logic)  *out.reg |= out.bitmask;
  else *out.reg &= ~out.bitmask;

}
#endif
