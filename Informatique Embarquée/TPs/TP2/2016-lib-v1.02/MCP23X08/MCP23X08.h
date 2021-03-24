// D.Delannoy le 15 juillet 2009
// B.Stefanelli le 19 juillet 2009
// O.Rossiny le 19 juillet 2009
//
// Version 2.0
//

#ifndef MCP23X08_h
#define MCP23X08_h

#include <inttypes.h>

# define REG23x08_IODIR   0x00
# define REG23x08_IOPOL   0x01
# define REG23x08_GPINTEN 0x02
# define REG23x08_DEFVAL  0x03
# define REG23x08_INTCON  0x04
# define REG23x08_IOCON   0x05
# define REG23x08_GPPU    0x06
# define REG23x08_INTF    0x07
# define REG23x08_INTCAP  0x08
# define REG23x08_GPIO    0x09
# define REG23x08_OLAT    0x0A

# define VAL23008_IOCON 0b00110100  // bit 7, 6 NOP
                                    // bit 5 SEQOP  1 = Sequential operation disabled, address pointer does not increment
                                    // bit 4 DISSLW  1 = Slew rate disabled
                                    // bit 3 NOP
                                    // bit 2 ODR  1 = Open-drain output (overrides the INTPOL bit)
                                    // bit 1 INTPOL  NOP
                                    // bit 0 NOP

# define VAL23S08_IOCON 0b00111100  // bit 7, 6 NOP
                                    // bit 5 SEQOP  1 = Sequential operation disabled, address pointer does not increment
                                    // bit 4 DISSLW  1 = Slew rate disabled
                                    // bit 3 HAEN  1 = Enables the MCP23S08 address pins
                                    // bit 2 ODR  1 = Open-drain output (overrides the INTPOL bit)
                                    // bit 1 INTPOL  NOP
                                    // bit 0 NOP                                    


class MCP23X08 {
protected:
  uint8_t val_iocon;
  uint8_t _deviceAddr;
  MCP23X08(uint8_t _deviceAddr, uint8_t val_iocon);
public:
  virtual void Write(uint8_t, uint8_t) = 0;
  virtual uint8_t Read(uint8_t) = 0;
  
  void Setup_IODIR(uint8_t);
  void Write_GPIO(uint8_t);
  uint8_t Read_GPIO();
};
                                    
class MCP23008_I2C : public MCP23X08 {
public:
  MCP23008_I2C(uint8_t = 0);
  void Write(uint8_t, uint8_t);
  uint8_t Read(uint8_t);
};


class MCP23S08_SPI : public MCP23X08 {
public:
  MCP23S08_SPI(uint8_t = 0);
  void Write(uint8_t, uint8_t);
  uint8_t Read(uint8_t);
};

#endif /* MCP23X08 */
