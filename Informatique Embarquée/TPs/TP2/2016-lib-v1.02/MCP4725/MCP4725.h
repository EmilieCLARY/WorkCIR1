// D.Delannoy le 15 juillet 2009
// B.Stefanelli le 19 juillet 2009
// D.Delannoy & O.Rossiny le 12 janvier 2012
//
// Version 2.0
//

#ifndef MCP4725_h
#define MCP4725_h

#include <inttypes.h>

# define MCP4725_ADDR  0x60		    // offset MCP4725 address
# define MCP4725_MASK  0b00001111   // bit 15 & 14 Fast Mode Command (C2, C1 = 0, 0)
                                    // bit 13 & 12 Power Down Select, Normal Mode (PD1, PD0 = 0, 0)

class MCP4725_I2C {
public:
  MCP4725_I2C(uint8_t);
  void Write_DAC(uint16_t);
  
private:
  uint8_t _deviceAddr;
};

#endif /* MCP4725_h */