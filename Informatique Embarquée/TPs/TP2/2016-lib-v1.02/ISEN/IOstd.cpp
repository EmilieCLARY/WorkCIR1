// D.Delannoy & O.Rossiny le 12 janvier 2012
//
// Standard IO interface for all leds and buttons
//
// Version 1.0
//

#include "IOstd.h"
#include <../MCP23X08/MCP23X08.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <LabIsen-2009.h>


// Constructors ////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------------
		spiOffset : MCP23S00 address (0 to 3) (A1 A0)
		i2cOffset : MCP23000 address (0 to 7) (A2 A1 A0)
---------------------------------------------------------------------------------*/
IOstd::IOstd(uint8_t spiOffset, uint8_t i2cOffset) :
  i2c_io(i2cOffset),            // Init MCP23008
  spi_io(spiOffset)             // Init MCP23S08
{
}

// Public Methods //////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------------
  Init i2c and spi bus
---------------------------------------------------------------------------------*/  
void IOstd::begin()
{
  i2c_io.Setup_IODIR(VAL23X08_IODIR);      				  	// Set pins as input or output
  i2c_io.Setup_IODIR(VAL23X08_IPOL);        			  	// Set logic positive or negative
  i2c_io.Setup_IODIR(VAL23X08_GPPU);        			  	// Disable IO pull up resistors
  i2c_io.Setup_IODIR(VAL23X08_OLAP);        			  	// Default output latched values

  i2c_io.Write(REG23x08_GPINTEN, VAL23X08_GPINTEN_DIS);		// Disable int
  i2c_io.Write(REG23x08_DEFVAL, VAL23X08_DEFVAL);			// Define ref value for int
  i2c_io.Write(REG23x08_INTCON, VAL23X08_INTCON);			// Define int mode for ref value
  i2c_io.Write(REG23x08_IOCON, VAL23X08_IOCON_DIS);			// Open-drain output int output

  spi_io.Setup_IODIR(VAL23X08_IODIR);        				// Set pins as input or output 
  spi_io.Setup_IODIR(VAL23X08_IPOL);         				// Set logic positive or negative
  spi_io.Setup_IODIR(VAL23X08_GPPU);        			  	// Disable IO pull up resistors
  spi_io.Setup_IODIR(VAL23X08_OLAP);        			  	// Default output latched values

  spi_io.Write(REG23x08_GPINTEN, VAL23X08_GPINTEN_DIS);		// Disable int
  spi_io.Write(REG23x08_DEFVAL, VAL23X08_DEFVAL);			// Define ref value for int
  spi_io.Write(REG23x08_INTCON, VAL23X08_INTCON);			// Define int mode for ref value
  spi_io.Write(REG23x08_IOCON, VAL23X08_IOCON_DIS);			// Open-drain output int output
  
  i2c_io.Write(REG23x08_IODIR,0x0F);
  spi_io.Write(REG23x08_IODIR,0x0F);
}

/*---------------------------------------------------------------------------------
  Set pin as INPUT or OUTPUT, usefull for led 1..4 and button 1..4, useless for others
		pin : led or button 1..4
		mode : INPUT or OUTPUT
---------------------------------------------------------------------------------*/
void IOstd::pinMode(uint8_t pin, uint8_t mode)
{
	switch (pin) {
	case 1:
		::pinMode(PIN_IO_0, mode);
		break;
	case 2:
		::pinMode(PIN_IO_1, mode);
		break;
	case 3:
		::pinMode(PIN_IO_2, mode);
		break;
	case 4:
		::pinMode(PIN_IO_3, mode);
		break;
	}
}

/*---------------------------------------------------------------------------------
  Read button state 
		button : 1..12
		return : HIGH (depress) or LOW (press)
---------------------------------------------------------------------------------*/
int IOstd::digitalRead(uint8_t button)
{
	switch (button) {
	case 1:
		return ::digitalRead(PIN_IO_0);
	case 2:
		return ::digitalRead(PIN_IO_1);
	case 3:
		return ::digitalRead(PIN_IO_2);
	case 4:
		return ::digitalRead(PIN_IO_3);

	// SPI
	case 5:
	case 6:
	case 7:
	case 8:
		return 0x01 & (spi_io.Read_GPIO() >> (8 - button));		// return only one bit

	// I2C
	case 9:
	case 10:
	case 11:
	case 12:
		return 0x01 & (i2c_io.Read_GPIO() >> (12 - button));	// return only one bit
	}
	// unknown button
	return -1;
}

/*---------------------------------------------------------------------------------
  Write led state
		led : 1..12
		val : HIGH (on) or LOW (off)
---------------------------------------------------------------------------------*/  
void IOstd::digitalWrite(uint8_t led, uint8_t state)
{
	byte masque = B00000001;

	switch (led) {
	case 1:
		::digitalWrite(PIN_IO_0, state);
		break;
	case 2:
		::digitalWrite(PIN_IO_1, state);
		break;
	case 3:
		::digitalWrite(PIN_IO_2, state);
		break;
	case 4:
		::digitalWrite(PIN_IO_3, state);
		break;

	// SPI
	case 5:
	case 6:
	case 7:
	case 8:
		spi_io.Write_GPIO(((state & 0x01) << (12 - led)) | (spi_io.Read_GPIO() & ~(masque << (12 - led))));	// set only one bit without changing others
		break;

	// I2C
	case 9:
	case 10:
	case 11:
	case 12:
		i2c_io.Write_GPIO(((state & 0x01) << (16 - led)) | (i2c_io.Read_GPIO() & ~(masque << (16 - led))));	// set only one bit without changing others
		break;
	}
}

/*---------------------------------------------------------------------------------
  Turn all leds off
---------------------------------------------------------------------------------*/  
void IOstd::clear()
{
	::digitalWrite(PIN_IO_0, LOW);
	::digitalWrite(PIN_IO_1, LOW);
	::digitalWrite(PIN_IO_2, LOW);
	::digitalWrite(PIN_IO_3, LOW);
	spi_io.Write_GPIO(0x00);
	i2c_io.Write_GPIO(0x00);
}

