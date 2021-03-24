// D.Delannoy le 15 juillet 2009
// B.Stefanelli le 19 juillet 2009
// D.Delannoy & O.Rossiny le 12 janvier 2012
//
// Interface for MCP4725 DAC
//
// Version 2.0
//

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MCP4725.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>

//=================================================================================================
// MCP4725 I2C DAC
//=================================================================================================

/*---------------------------------------------------------------------------------
 Set up MCP4725 device address
		deviceAddr : device address from 0 to 1
---------------------------------------------------------------------------------*/
MCP4725_I2C::MCP4725_I2C(uint8_t deviceAddr) : _deviceAddr(deviceAddr) {
  Wire.begin(); 								// join i2c bus as master device
  _deviceAddr = _deviceAddr | MCP4725_ADDR;	    // add offset address for MCP4725 device
}


/*---------------------------------------------------------------------------------
 Write data to MCP4725 register
		val : data value
---------------------------------------------------------------------------------*/
void MCP4725_I2C::Write_DAC(uint16_t val ) {
  Wire.beginTransmission(_deviceAddr);			// begin transmission with slave device #_deviceAddr
  Wire.write((uint8_t)(val >> 8) & MCP4725_MASK);// put 1 byte (high)
  Wire.write((uint8_t)(val & 255));    			// put 1 byte (low)
  Wire.endTransmission();						// send all bytes
}