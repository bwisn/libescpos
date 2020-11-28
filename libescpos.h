#ifndef LIBESCPOS_H
#define LIBESCPOS_H

#include <stdint.h>

class EscPos {
public:
  void init();
  void feed(uint8_t lines);
  void lf() { feed(1); }
  void bold(uint8_t status = 1);
  void left();
  void center();
  void right();
  void small();
  void big();
  void invert(uint8_t status = 1);
  void print(const char *buf);
  void println(const char *buf);
  void printf(const char *buf, ...);
  void end() { feed(3); }; // ends printing with 2 newlines
};

void EscPos_sendCh(char a) __attribute__((weak));

#endif