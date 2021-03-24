// D.Delannoy le 15 juillet 2009
// B.Stefanelli le 19 juillet 2009
// O.Rossiny le 19 juillet 2009
//
// Interface for MCP23008 I2C and MCP23S08 SPI
//
// Version 2.0
//

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MCP23X08.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>
#include <Spi.h>

# define MCP23008_ADDR 0x20		    // offset MCP23008 address
# define MCP23S08_ADDR 0x20		    // offset MCP23S08 address

//=================================================================================================
// MCP23008 I2C I/O
//=================================================================================================

MCP23X08::MCP23X08(uint8_t deviceAddr, uint8_t val) {
  _deviceAddr = deviceAddr;
  val_iocon = val;
}

/*---------------------------------------------------------------------------------
 Set up MCP23008 device address
		deviceAddr : device address from 0 to 7
---------------------------------------------------------------------------------*/
MCP23008_I2C::MCP23008_I2C(uint8_t deviceAddr) : MCP23X08(deviceAddr, VAL23008_IOCON) {
  Wire.begin(); 											// join i2c bus as master device
  _deviceAddr = ( _deviceAddr  & 0x07 ) | MCP23008_ADDR ;	// add offset address for MCP23008 device
}


/*---------------------------------------------------------------------------------
 Write data to MCP23008 register
		reg : MCP23008 register
		val : data value
---------------------------------------------------------------------------------*/
void MCP23008_I2C::Write(uint8_t reg, uint8_t val ) {
  Wire.beginTransmission(_deviceAddr);			// begin transmission with slave device #_deviceAddr
  Wire.write(reg);								// select register
  Wire.write(val);    							// put 1 byte
  Wire.endTransmission();						// send all bytes
}


/*---------------------------------------------------------------------------------
 Read data from MCP23008 register
		reg : MCP23008 register
		return : data value
---------------------------------------------------------------------------------*/
uint8_t MCP23008_I2C::Read(uint8_t reg) {

  Wire.beginTransmission(_deviceAddr);			// begin transmission with slave device #_deviceAddr
  Wire.write(reg);								// select register
  Wire.endTransmission();						// send all bytes

  Wire.requestFrom(_deviceAddr, (uint8_t)1);   	// request 1 byte from slave device #_deviceAddr

  if (Wire.available())   	 					// slave may send less than requested
  { 
    return Wire.read(); 						// get 1 byte
  } 
  else {
	return 0;
  }
}


/*---------------------------------------------------------------------------------
 Write data to MCP23X08 IODIR register
		val : data value, 0 = output, 1 = input
---------------------------------------------------------------------------------*/
void MCP23X08::Setup_IODIR(uint8_t val) {
  Write(REG23x08_IODIR, val);
  Write(REG23x08_IOCON, val_iocon);
}


/*---------------------------------------------------------------------------------
 Write data to MCP23X08 GPIO register
		val : data value
---------------------------------------------------------------------------------*/
void MCP23X08::Write_GPIO(uint8_t val) {
  Write(REG23x08_GPIO, val);
}


/*---------------------------------------------------------------------------------
 Read data from MCP23X08 GPIO register
		return : data value
---------------------------------------------------------------------------------*/
uint8_t MCP23X08::Read_GPIO() {
  return Read(REG23x08_GPIO);
}



//=================================================================================================
// MCP23S08 SPI I/O
//=================================================================================================

/*---------------------------------------------------------------------------------
 Set up MCP23S08 device address
		deviceAddr : device address from 0 to 3
---------------------------------------------------------------------------------*/
MCP23S08_SPI::MCP23S08_SPI(uint8_t deviceAddr) : MCP23X08(deviceAddr, VAL23S08_IOCON) {

  digitalWrite(SS_PIN, HIGH);                   // Disable slave pin CS
  
  //    Configure SPI Control Register (SPCR) (All values initially 0)
  //     Bit  Description
  //       7  SPI Interrupt Enable             -- disable  (SPIE --> 0)
  //       6  SPI Enable                            -- enable   (SPE  --> 1)
  //       5  Data Order                            -- MSB 1st  (DORD --> 0) (Slave specific)
  //       4  Master/Slave Select              -- master   (MSTR --> 1)
  //       3  Clock Polarity                        --          (CPOL --> 0) (Slave specific) ("Mode")
  //       2  Clock Phase                           --          (CPHA --> 0) (Slave specific
  //       1  SPI Clock Rate Select 1         -- }        (SPR1 --> 0) 
  //       0  SPI Clock Rate Select 0        -- } fOSC/4 (SPR0 --> 0) ("Fastest" but see SPI2X in SPSR)
  Spi.mode(0);                                  // SPCR = (1<<SPE)| (1<<MSTR)

  _deviceAddr = _deviceAddr | MCP23S08_ADDR;	// add offset address for MCP23S08 device
}


/*---------------------------------------------------------------------------------
 Write data to MCP23S08 register
		reg : MCP23S08 register
		val : data value
---------------------------------------------------------------------------------*/
void MCP23S08_SPI::Write(uint8_t reg, uint8_t val ) {

  digitalWrite(SS_PIN, LOW);                    // Enable slave pin CS
  Spi.transfer(0 | (_deviceAddr << 1));         // begin transmission with slave device #_deviceAddr
  Spi.transfer(reg);                            // select register
  Spi.transfer(val);                            // put 1 byte
  digitalWrite(SS_PIN, HIGH);                   // Disable slave pin CS
}


/*---------------------------------------------------------------------------------
 Read data from MCP23S08 register
		reg : MCP23S08 register
		return : data value
---------------------------------------------------------------------------------*/
uint8_t MCP23S08_SPI::Read(uint8_t reg) {

  digitalWrite(SS_PIN, LOW);                    // Enable slave
  Spi.transfer(1 | (_deviceAddr << 1));         // begin transmission with slave device #_deviceAddr
  Spi.transfer(reg);                            // select register
  
  byte data;
  data = Spi.transfer(0xFF);                    // Spi.transfer dummy byte to get response
  digitalWrite(SS_PIN, HIGH);                   // Disable slave
  return data;
}
