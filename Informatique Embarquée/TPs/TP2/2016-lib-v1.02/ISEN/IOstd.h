// D.Delannoy & O.Rossiny le 12 janvier 2012
//
// Version 1.0
//

#ifndef IOstd_h
#define IOstd_h

#include <inttypes.h>
#include <MCP23X08.h>

class IOstd
{
  MCP23008_I2C i2c_io;       // Init MCP23008
  MCP23S08_SPI spi_io;       // Init MCP23S08
  public:
    IOstd (uint8_t spiOffset = 0x00, uint8_t i2cOffset = 0x00);
    void begin();
    void pinMode(uint8_t pin, uint8_t mode);
    int digitalRead(uint8_t pin);
    void digitalWrite(uint8_t pin, uint8_t val);
    void clear();
};

#endif /* IOstd_h */

