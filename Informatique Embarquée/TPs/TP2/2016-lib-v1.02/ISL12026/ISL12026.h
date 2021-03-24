// B.Stefanelli le 30 janvier 2010
// D.Delannoy & O.Rossiny le 12 janvier 2012
//
// Version 3.0
//

#ifndef ISL12026_h
#define ISL12026_h

#include <inttypes.h>

# define ISL12026_SCA0 0x00  // Alarm0 EEPROM
# define ISL12026_MNA0 0x01
# define ISL12026_HRA0 0x02
# define ISL12026_DTA0 0x03
# define ISL12026_MOA0 0x04
# define ISL12026_YRA0 0x05
# define ISL12026_DWA0 0x06
# define ISL12026_Y2K0 0x07

# define ISL12026_SCA1 0x08   // Alarm1 EEPROM
# define ISL12026_MNA1 0x09
# define ISL12026_HRA1 0x0A
# define ISL12026_DTA1 0x0B
# define ISL12026_MOA1 0x0C
# define ISL12026_YRA1 0x0D
# define ISL12026_DWA1 0x0E
# define ISL12026_Y2K1 0x0F

# define ISL12026_BL   0x10  // Control EEPROM
# define ISL12026_INT  0x11
# define ISL12026_ATR  0x12
# define ISL12026_DTR  0x13
# define ISL12026_PWR  0x14

# define ISL12026_SC   0x30  // RTC (SRAM)
# define ISL12026_MN   0x31
# define ISL12026_HR   0x32
# define ISL12026_DT   0x33
# define ISL12026_MO   0x34
# define ISL12026_YR   0x35
# define ISL12026_DW   0x36
# define ISL12026_Y2K  0x37

# define ISL12026_SR   0x3F   // Status

// Bit positions
// Status register
# define ISL12026_SR_WEL   	0x02
# define ISL12026_SR_RWEL  	0x04
// HR register
# define ISL12026_HR_MIL   	0x80
# define ISL12026_HR_PM		0x20
// INT Register
# define ISL12026_INT_AL0E	0x20
# define ISL12026_INT_AL1E	0x40

class ISL12026 {
public:
  ISL12026(uint8_t = 0);
  void disableInt();
  void writeRTC(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  void writeControl(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  void writeAlarm(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t,
				  uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t,
				  uint8_t, uint8_t, uint8_t, uint8_t);
  void writeCCR(uint8_t, uint8_t);
  uint8_t randReadCCR(uint8_t);
  
private:
  void registerWriteEnableLatch();
  void writeEnableLatch(bool enable);
  uint8_t _deviceAddr;
  uint8_t _arrayAddr;
};

#endif /* ISL12026_h */
