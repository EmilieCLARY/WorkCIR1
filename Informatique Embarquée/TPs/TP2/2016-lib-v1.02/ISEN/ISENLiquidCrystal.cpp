// D.Delannoy le 11 juin 2009
// D.Delannoy le 21 juillet 2009

#include "ISENLiquidCrystal.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

ISENLiquidCrystal::ISENLiquidCrystal() : LiquidCrystal(15, 0, 14, 4, 5, 6, 7) {
}

/*---------------------------------------------------------------------------------
 Position the cursor at the beginning of the line and clear it
---------------------------------------------------------------------------------*/ 
void ISENLiquidCrystal::clear_line(int row) {
  setCursor(0, row);                // set cursor position to zero
  print("                ");        // clear line
  setCursor(0, row);                // set cursor position to zero
}

void ISENLiquidCrystal::displayTime(Clock &clock, TimeOperation op) {
	unsigned int hr, mn, sc;
	TimeAmPm ampm;
	clock.GetTime(&hr, &mn, &sc, &ampm, op);
	
	if (ampm != HOUR_24) {
		print(ampm == HOUR_12_PM ? 'p': 'a');
		print('m');
	}
	if (hr < 10) print("0");
	print(hr);
    print(":");
	if (mn < 10) print("0");
    print(mn);
    print(":");
	if (sc < 10) print("0");
    print(sc);
}

void ISENLiquidCrystal::displayDate(Clock &clock, TimeOperation op) {
	unsigned int dt, mo, yr;
	WeekDay dw;
	clock.GetDate(&dt, &mo, &yr, &dw, op);
	
	if (dt < 10) print("0");
	print(dt);
    print("/");
	if (mo < 10) print("0");
    print(mo);
    print("/");
	if (yr < 10) print("0");
    print(yr);
}
