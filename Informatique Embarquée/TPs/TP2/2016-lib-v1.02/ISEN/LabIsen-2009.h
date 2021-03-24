#ifndef LABISEN_2009_h
#define LABISEN_2009_h

// LED positions
# define PIN_IO_0 8                 // red led, button 0, pb0
# define PIN_IO_1 9                 // yellow led, button 1, pb1
# define PIN_IO_2 2                 // green led, button 2, pd2
# define PIN_IO_3 3                 // blue led, button 3, pd3

// autres IO positions
# define PIN_POT  3         		// Potentiometer pin, pc3

// Display size
# define Display_cols	16			// Number of colums
# define Display_lines	2			// Number of lines


// SPI / I2C options 
# define VAL23X08_IODIR 		0x0F       	// IO direction value, 4 high bits output (0), 4 low bits input (1)
# define VAL23X08_IPOL  		0x00       	// IO logic state, logic state = input state (0)
# define VAL23X08_GPINTEN_DIS 	0x00       	// Interrupt enable value, disable all int
# define VAL23X08_GPINTEN_EN 	0x0F       	// Interrupt enable value, enable 4 low bits int
# define VAL23X08_DEFVAL 		0xFF       	// Compare interrupt value, default all is 1
# define VAL23X08_INTCON 		0xFF		// Compare with DEFVAL values, default all is 1
# define VAL23X08_IOCON_DIS 	0b00001100	// Enable the address pins b3=1, open-drain output (overrides the INTPOL bit) b=1 
# define VAL23X08_GPPU  		0x00       	// IO pull up internal resistor
# define VAL23X08_OLAP  		0x00       	//Default output latched values

#endif /* LABISEN_2009_h */
