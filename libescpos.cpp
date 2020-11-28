#include "libescpos.h"
#include "escpos_internals.h"
#include <cstdarg>
#include <cstdio>

/**
 * @brief Sends char* to the printer
 *
 * @param buf string buffer
 */
static void sendStr(const char *buf) {
  char *tmp = (char *)buf;
  while (*tmp != 0x00) {
    EscPos_sendCh(*tmp);
    ++tmp;
  }
}

/**
 * @brief Initializes the printer module
 *
 */
void EscPos::init() {
  // clean printer settings
  EscPos_sendCh(ESC);
  EscPos_sendCh('@');

  // csn-a2 settings
  EscPos_sendCh(ESC);
  EscPos_sendCh('7');
  EscPos_sendCh(HEAT_DOTS);
  EscPos_sendCh(HEAT_TIME);
  EscPos_sendCh(HEAT_INTERVAL);

  // print density
  EscPos_sendCh(DC2);
  EscPos_sendCh('#');
  EscPos_sendCh((PRINT_DENSITY << 4) | PRINT_BREAKTIME);

  bold(0); // restore text parameters to default
  invert(0);
}

/**
 * @brief Feeds [lines] lines of paper
 *
 * @param lines number of lines
 */
void EscPos::feed(uint8_t lines) {
  EscPos_sendCh(ESC);
  EscPos_sendCh('d');
  EscPos_sendCh(lines);
}

/**
 * @brief Makes text bold or not
 *
 * @param status 0 is normal, 1 is bold
 */
void EscPos::bold(uint8_t status) {
  if (status > 1 || status < 0)
    status = 1;
  EscPos_sendCh(ESC);
  EscPos_sendCh(' ');
  EscPos_sendCh(status);
}

/**
 * @brief Aligns text to the left
 *
 */
void EscPos::left() {
  EscPos_sendCh(ESC);
  EscPos_sendCh('a');
  EscPos_sendCh(0); // 0 is left
}

/**
 * @brief Aligns text to the center
 *
 */
void EscPos::center() {
  EscPos_sendCh(ESC);
  EscPos_sendCh('a');
  EscPos_sendCh(1); // 1 is center
}

/**
 * @brief Aligns text to the right
 *
 */
void EscPos::right() {
  EscPos_sendCh(ESC);
  EscPos_sendCh('a');
  EscPos_sendCh(2); // 2 is right
}

/**
 * @brief Changes font to small
 *
 */
void EscPos::small() {
  EscPos_sendCh(GS);
  EscPos_sendCh('!');
  EscPos_sendCh(0x0000);
}

/**
 * @brief Changes font to big
 *
 */
void EscPos::big() {
  EscPos_sendCh(GS);
  EscPos_sendCh('!');
  EscPos_sendCh('8');
}

/**
 * @brief Inverts background with foreground, ie. white text on black background
 *
 * @param status 0 is normal, 1 is inverted
 */
void EscPos::invert(uint8_t status) {
  if (status > 1 || status < 0)
    status = 1;
  EscPos_sendCh(GS);
  EscPos_sendCh('B');
  EscPos_sendCh(status);
}

/**
 * @brief Sends char* to the printer
 *
 * @param buf text that you want to print
 */
void EscPos::print(const char *buf) { sendStr(buf); }

/**
 * @brief Sends char* to the printer and make a newline
 *
 * @param buf text that you want to print
 */
void EscPos::println(const char *buf) {
  sendStr(buf);
  feed(1);
}

/**
 * @brief Sends formatted string to the printer
 *
 * @param buf "" format
 * @param ... arguments
 */
void EscPos::printf(const char *buf, ...) {
  va_list args;
  char *str = (char *)buf;
  va_start(args, buf);
  size_t fmtlen = vsnprintf(NULL, 0, str, args);
  char *tmp = new char[fmtlen + 1];
  vsnprintf(tmp, fmtlen + 1, str, args);
  tmp[fmtlen] = '\0'; // null terminate
  sendStr(tmp);
  va_end(args);
  delete[] tmp;
}
