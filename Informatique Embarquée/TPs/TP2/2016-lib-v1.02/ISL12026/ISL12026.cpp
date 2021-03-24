// B.Stefanelli le 30 janvier 2010
// D.Delannoy & O.Rossiny le 12 janvier 2012
//
// Interface for ISL12026 clock
//
// Version 3.0
//

#include "ISL12026.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

# define ISL12026_CCR_ADDR   0x6F				// offset ISL12026 CCR address
# define ISL12026_ARRAY_ADDR 0x57				// offset ISL12026 ARRAY address

/*---------------------------------------------------------------------------------
 Set up ISL12026 device address
		deviceAddr : fixed device address = 0
---------------------------------------------------------------------------------*/
ISL12026::ISL12026(uint8_t deviceAddr) : _deviceAddr(deviceAddr  | ISL12026_CCR_ADDR) {
	// add offset address for ISL12026 device
  Wire.begin(); 								// Join i2c bus as master device
}

/*---------------------------------------------------------------------------------
 Disable int to avoid conflic with interrrupts and switches
---------------------------------------------------------------------------------*/
void ISL12026::disableInt() {
  writeCCR(ISL12026_INT, 0x00);					// Disable interrupt
}

/*---------------------------------------------------------------------------------
 Enable writing to registers step 1
		enable : begin or end (true..false)
---------------------------------------------------------------------------------*/
void ISL12026::writeEnableLatch(bool enable) {
  Wire.beginTransmission(_deviceAddr);			// Begin transmission with registers 
  Wire.write((uint8_t) 0x00);					// Select SR register
  Wire.write((uint8_t) ISL12026_SR);
  if (enable) {
	Wire.write((uint8_t) ISL12026_SR_WEL);    	// Set WEL bit
  } else {  
	Wire.write((uint8_t) 0x00);    				// Reset RWEL & WEL bits
  }
  Wire.endTransmission();						// Send all bytes
  
  delay(20);									// Writing to EEPROM may take up to 20ms
}

/*---------------------------------------------------------------------------------
 Enable writing to registers step 2
---------------------------------------------------------------------------------*/
void ISL12026::registerWriteEnableLatch() {
  Wire.beginTransmission(_deviceAddr);			// Begin transmission with registers 
  Wire.write((uint8_t) 0x00);					// Select SR register
  Wire.write((uint8_t) ISL12026_SR);
  Wire.write((uint8_t) ISL12026_SR_WEL | ISL12026_SR_RWEL);    	// Set RWEL & WEL bits
  Wire.endTransmission();						// Send all bytes
  
  delay(20);									// Writing to EEPROM may take up to 20ms  
}

/*---------------------------------------------------------------------------------
 Write data to ISL12026 RTC registers (8 words page write)
		sc : seconds (1..60)
		mn : minutes (1..60)
		hr : hours (1..24 or 1..12 depending of format)
		dt : day (1..31 depending of month)
		mo : month (1..12)
		yr : year (0..99)
		dw : day of week (0..6)
		y2k : 19xx or 20xx (19..20)
---------------------------------------------------------------------------------*/
void ISL12026::writeRTC(uint8_t sc, uint8_t mn, uint8_t hr, uint8_t dt, uint8_t mo, uint8_t yr, uint8_t dw, uint8_t y2k) {

  writeEnableLatch(true);
  registerWriteEnableLatch();

  Wire.beginTransmission(_deviceAddr);			// Begin transmission with CCR 
  Wire.write((uint8_t) 0x00);					// Select SC register
  Wire.write((uint8_t) ISL12026_SC);
  Wire.write(sc);
  Wire.write(mn);
  Wire.write(hr);
  Wire.write(dt);
  Wire.write(mo);
  Wire.write(yr);
  Wire.write(dw);
  Wire.write(y2k);  					
  Wire.endTransmission();						// Send all bytes

  writeEnableLatch(false);

  delay(20);									// Writing to EEPROM may take up to 20ms
}

/*---------------------------------------------------------------------------------
 Write data to ISL12026 control registers (5 words page write)
		bl : bl register
		cint : cint register
		atr : atr register
		dtr : dtr register
		pwr : pwr register
---------------------------------------------------------------------------------*/
void ISL12026::writeControl(uint8_t bl, uint8_t cint, uint8_t atr, uint8_t dtr, uint8_t pwr) {

  writeEnableLatch(true);
  registerWriteEnableLatch();

  Wire.beginTransmission(_deviceAddr);			// Begin transmission with CCR 
  Wire.write((uint8_t) 0x00);					// Select BL register
  Wire.write((uint8_t) ISL12026_BL);
  Wire.write(bl);
  Wire.write(cint);
  Wire.write(atr);
  Wire.write(dtr);
  Wire.write(pwr);					
  Wire.endTransmission();						// Send all bytes

  writeEnableLatch(false);

  delay(20);									// Writing to EEPROM may take up to 20ms
}

/*---------------------------------------------------------------------------------
 Write data to ISL12026 Alarm 0 and 1 registers (16 words page write)
		sca0 : seconds (1..60)
		mna0 : minutes (1..60)
		hra0 : hours (1..24 or 1..12 depending of format)
		dta0 : day (1..31 depending of month)
		moa0 : month (1..12)
		yra0 : year (0..99)
		dwa0 : day of week (0..6)
		y2k0 : 19xx or 20xx (19..20)
		sca1 : seconds (1..60)
		mna1 : minutes (1..60)
		hra1 : hours (1..24 or 1..12 depending of format)
		dta1 : day (1..31 depending of month)
		moa1 : month (1..12)
		yra1 : year (0..99)
		dwa1 : day of week (0..6)
		y2k1 : 19xx or 20xx (19..20)		
---------------------------------------------------------------------------------*/
void ISL12026::writeAlarm(uint8_t sca0, uint8_t mna0, uint8_t hra0, uint8_t dta0, uint8_t moa0, uint8_t yra0, uint8_t dwa0, uint8_t y2k0, uint8_t sca1, uint8_t mna1, uint8_t hra1, uint8_t dta1, uint8_t moa1, uint8_t yra1, uint8_t dwa1, uint8_t y2k1) {
  
  writeEnableLatch(true);
  registerWriteEnableLatch();

  Wire.beginTransmission(_deviceAddr);			// Begin transmission with CCR  
  Wire.write((uint8_t) 0x00);					// Select MNA0 register
  Wire.write((uint8_t) 0x01);
  Wire.write(mna0);
  Wire.write(hra0);
  Wire.write(dta0);
  Wire.write(moa0);
  Wire.write(yra0);
  Wire.write(dwa0);
  Wire.write(y2k0);
  Wire.write(sca1);
  Wire.write(mna1);
  Wire.write(hra1);
  Wire.write(dta1);
  Wire.write(moa1);
  Wire.write(yra1);
  Wire.write(dwa1);
  Wire.write(y2k1);  					
  Wire.write(sca0);
  Wire.endTransmission();						// Send all bytes

  writeEnableLatch(false);

  delay(20);									// Writing to EEPROM may take up to 20ms
}

/*---------------------------------------------------------------------------------
 Write data to the other ISL12026 CCR registers (byte write), excepted DWA0 and DWA1 which require page write
		reg : any register from control, alamrm1, alarm0 sections (2nd address byte only)
		val : data value
---------------------------------------------------------------------------------*/
void ISL12026::writeCCR(uint8_t reg, uint8_t val) {

  writeEnableLatch(true);
  registerWriteEnableLatch();

  Wire.beginTransmission(_deviceAddr);			// Begin transmission with CCR 
  Wire.write((uint8_t) 0x00);					// Select SC register
  Wire.write(reg);
  Wire.write(val);  					
  Wire.endTransmission();						// Send all bytes

  writeEnableLatch(false);
  
  delay(20);
}

/*---------------------------------------------------------------------------------
 Read data from any ISL12026 CCR register (random read)
		reg : any CCR register (2nd address byte only)
		return : data value
---------------------------------------------------------------------------------*/
uint8_t ISL12026::randReadCCR(uint8_t reg) {

  Wire.beginTransmission(_deviceAddr);			// Begin transmission with slave device #_deviceAddr
  Wire.write((uint8_t) 0x00);
  Wire.write(reg);								// Select register
  Wire.endTransmission();						// Send all bytes

  delay(20);									// Writing to EEPROM may take up to 20ms
  
  Wire.requestFrom(_deviceAddr, (uint8_t)1);   	// Request 1 byte from slave device #_deviceAddr

  if (Wire.available())   	 					// Slave may send less than requested
  { 
    return Wire.read(); 						// Get 1 byte
  } 
  else {
	return 0;
  }
}