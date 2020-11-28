# libescpos

## What it is?
libescpos is a simple C++ library which can you use to print using ESC/POS compatible printers such as GOOJPRT JP-QR701-TTL or CSN-A2.

# Usage
Import the library into your project and declare send char function:
`void EscPos_sendCh(char a)`. Below is an example code which you can use with STM32:
```c++
extern UART_HandleTypeDef huart1;

void EscPos_sendCh(char a) {
		HAL_UART_Transmit(&huart1, &a, 1, 100);
}
```
or with ESP8266 arduino
```c++
void EscPos_sendCh(char a) {
		Serial1.write(a);
}
```

## Resources
https://www.starmicronics.com/support/Mannualfolder/escpos_cm_en.pdf - ESC/POS specifications
https://cdn-shop.adafruit.com/datasheets/CSN-A2+User+Manual.pdf - CSN-A2 manual