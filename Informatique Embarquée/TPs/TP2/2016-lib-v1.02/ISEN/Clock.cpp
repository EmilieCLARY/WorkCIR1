// D.Delannoy & O.Rossiny le 16 janvier 2012
//
// Standard IO interface for clock
//
// Version 1.0
//

#include "Clock.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

# define REG_SC 0x30                // Seconds register
# define REG_MN 0x31                // Minutes register
# define REG_HR 0x32                // Hours register
# define REG_DT 0x33                // Day register
# define REG_MO 0x34                // Month register
# define REG_YR 0x35                // Year register
# define REG_DW 0x36                // day number (0-6) register
# define REG_Y2K 0x37               // year (19/20) register


// Constructors ////////////////////////////////////////////////////////////////

Clock::Clock(uint8_t rtcAddr) :
	rtc(rtcAddr)            // Init ISL12026
{
}

// Public Methods //////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------------
  Set current, alarm0 or alarm1 time
		hours : hours (1..24 or 1..12 depending of TimeAmPm)
		minutes : minutes (1..60)
		seconds : seconds (1..60)
		ampm : format setting 24h, 12h am or 12h pm for hours (HOUR_24, HOUR_12_AM, HOUR_12_PM)
		op : set time register (CurrentTime, Alarm0, Alarm1)
---------------------------------------------------------------------------------*/
void Clock::SetTime(unsigned int hours, unsigned int minutes, unsigned int seconds, TimeAmPm ampm, TimeOperation op)
{
	if (op == CurrentTime) {
		TimeDate currentTime;
		
		readTimeDateRegisters(currentTime, ISL12026_SC, false);			// Get time and date RTC page in time-date structure with flags
		copyTime(currentTime, hours, minutes, seconds, ampm);			// Set time in time-date structure
		
		if (ampm == HOUR_24) {
			currentTime.hr = currentTime.hr | ISL12026_HR_MIL;			// Add the MIL bit flag if 24h format
		}

		rtc.writeRTC(currentTime.sc, currentTime.mn, currentTime.hr,
					 currentTime.dt, currentTime.mo, currentTime.yr, currentTime.dw, currentTime.y2k);	// Set RTC
	} else {
		TimeDate alarm0;
		TimeDate alarm1;
		
		readTimeDateRegisters(alarm0, ISL12026_SCA0, false);			// Get ALARM0 and ALARM1 pages in time-date structure with alarm flag 
		readTimeDateRegisters(alarm1, ISL12026_SCA1, false);
		
		if (op == Alarm0)
			copyTime(alarm0, hours, minutes, seconds, ampm);			// Set time in time-date structure
		else
			copyTime(alarm1, hours, minutes, seconds, ampm);			// Set time in time-date structure
		
		rtc.writeAlarm(alarm0.sc, alarm0.mn, alarm0.hr, alarm0.dt, alarm0.mo, alarm0.yr, alarm0.dw, alarm0.y2k,
					   alarm1.sc, alarm1.mn, alarm1.hr, alarm1.dt, alarm1.mo, alarm1.yr, alarm1.dw, alarm1.y2k);	// Set ALARM
	}
	delay(1000); 														// wait to avoid killing EEPROM with loops
}

/*---------------------------------------------------------------------------------
  Get current, alarm0 or alarm1 time
		return hours : hours (1..24 or 1..12 depending of TimeAmPm)
		return minutes : minutes (1..60)
		return seconds : seconds (1..60)
		return ampm : format setting 24h, 12h am or 12h pm for hours (HOUR_24, HOUR_12_AM, HOUR_12_PM)
		op : get time register (CurrentTime, Alarm0, Alarm1)
---------------------------------------------------------------------------------*/
void Clock::GetTime(unsigned int *hours, unsigned int *minutes, unsigned int *seconds, TimeAmPm *ampm, TimeOperation op)
{
	TimeDate time = GetTimeDate(op);									// Get time and date page in time-date structure without alarm flag
		
	*seconds = bcd2int(time.sc);         								// Convert time format
	*minutes = bcd2int(time.mn);

	uint8_t refHours;
	if (op == CurrentTime) {											// Retreive hour from RTC to find 24h or 12h format
		refHours = time.hr;
	} else {
		refHours = rtc.randReadCCR(REG_HR);
	}
	
	uint8_t rawHours = time.hr;
	if (refHours & ISL12026_HR_MIL) {									// Convert time to 24h or 12h format with am/pm
		// 24-hour,
		*hours = bcd2int(rawHours & 0x3F);
		*ampm = HOUR_24;
	} else {
		// 12-hour, AMPM
		*hours = bcd2int(rawHours & 0x1F);
		*ampm = (rawHours & ISL12026_HR_PM) ? HOUR_12_PM : HOUR_12_AM;
	}
	
}

/*---------------------------------------------------------------------------------
  Set current, alarm0 or alarm1 time
		day : day (1..31 depending of month)
		month : month (1..12)
		year : year (0..99)
		dayOfWeek : day of week (Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday)
		op : set time register (CurrentTime, Alarm0, Alarm1)
---------------------------------------------------------------------------------*/
void Clock::SetDate(unsigned int day, unsigned int month, unsigned int year, WeekDay dayOfWeek, TimeOperation op)
{
	if (op == CurrentTime) {
		TimeDate currentTime;
		
		readTimeDateRegisters(currentTime, ISL12026_SC, false);			// Get time and date RTC page in time-date structure with flags
		copyDate(currentTime, day, month, year, dayOfWeek);				// Set date in time-date structure

		rtc.writeRTC(currentTime.sc, currentTime.mn, currentTime.hr,
					 currentTime.dt, currentTime.mo, currentTime.yr, currentTime.dw, currentTime.y2k);		// Set clock
	} else {
	    TimeDate alarm0, alarm1;
		
		readTimeDateRegisters(alarm0, ISL12026_SCA0, false);			// Get ALARM0 and ALARM1 pages in time-date structure with alarm flag
		readTimeDateRegisters(alarm1, ISL12026_SCA1, false);
		
		if (op == Alarm0)
			copyDate(alarm0, day, month, year, dayOfWeek);				// Set date in time-date structure
		else
			copyDate(alarm1, day, month, year, dayOfWeek);				// Set date in time-date structure
		
		rtc.writeAlarm(alarm0.sc, alarm0.mn, alarm0.hr, alarm0.dt, alarm0.mo, alarm0.yr, alarm0.dw, alarm0.y2k,
					   alarm1.sc, alarm1.mn, alarm1.hr, alarm1.dt, alarm1.mo, alarm1.yr, alarm1.dw, alarm1.y2k);	// Set ALRAM
	}
	delay(1000); 														// wait to avoid killing EEPROM with loops
}

/*---------------------------------------------------------------------------------
  Get current, alarm0 or alarm1 time
		return day : day (1..31 depending of month)
		return month : month (1..12)
		return year : year (0..99)
		return dayOfWeek : day of week (Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday)
		op : get time register (CurrentTime, Alarm0, Alarm1)
---------------------------------------------------------------------------------*/
void Clock::GetDate(unsigned int *day, unsigned int *month, unsigned int *year, WeekDay *dayOfWeek, TimeOperation op)
{
	TimeDate time = GetTimeDate(op);									// Get time and date page in time-date structure without alarm flag
	
    *day = bcd2int(time.dt);                 							// Convert date format
	*month = bcd2int(time.mo);         
	*year = bcd2int(time.yr);         
	*dayOfWeek = (WeekDay)(time.dw);  
}

/*---------------------------------------------------------------------------------
  Set alarm
		alarm : alarm number (Alarm0, Alarm1)
		enabled : enabled or disable (true..false)
---------------------------------------------------------------------------------*/
void Clock::setAlarm(TimeOperation alarm, bool enabled) {
	if (alarm == CurrentTime) {
		// Invalid alarm
		return;
	}
	
	TimeDate alarm0, alarm1;
		
	readTimeDateRegisters(alarm0, ISL12026_SCA0, alarm == Alarm0);		// Get time and date ALARM0 and ALARM1 pages in time-date structure with alarm flag
	readTimeDateRegisters(alarm1, ISL12026_SCA1, alarm == Alarm1);
	
	uint8_t intValue = rtc.randReadCCR(ISL12026_INT);					// Get INT register
	uint8_t mask;
	  
	if (alarm == Alarm0) {
		mask = ISL12026_INT_AL1E; 										// We want to keep AL1E state
		intValue = (intValue & mask);
		if (enabled) {													// Set ALAM0 alam flags for all values
			alarm0.sc = 0x80 | alarm0.sc;
			alarm0.mn = 0x80 | alarm0.mn;
			alarm0.hr = 0x80 | alarm0.hr;
			alarm0.dt = 0x80 | alarm0.dt;
			alarm0.mo = 0x80 | alarm0.mo;
			alarm0.dw = 0x80 | alarm0.dw;
			intValue |= ISL12026_INT_AL0E;
		}
	} else {
		mask = ISL12026_INT_AL0E; 										// We want to keep AL0E state
		intValue = (intValue & mask);
		if (enabled) {													// Set ALAM1 alam flags for all values
			alarm1.sc = 0x80 | alarm1.sc;
			alarm1.mn = 0x80 | alarm1.mn;
			alarm1.hr = 0x80 | alarm1.hr;
			alarm1.dt = 0x80 | alarm1.dt;
			alarm1.mo = 0x80 | alarm1.mo;
			alarm1.dw = 0x80 | alarm1.dw;
			intValue |= ISL12026_INT_AL1E;
		}
	}
	
	rtc.writeAlarm(alarm0.sc, alarm0.mn, alarm0.hr, alarm0.dt, alarm0.mo, alarm0.yr, alarm0.dw, alarm0.y2k,
				   alarm1.sc, alarm1.mn, alarm1.hr, alarm1.dt, alarm1.mo, alarm1.yr, alarm1.dw, alarm1.y2k); 	// Set ALRAM

	intValue |= 0x80;													// Set INT register IM bit
	rtc.writeCCR(ISL12026_INT, intValue);								// Set INT register
	
	delay(1000); 														// wait to avoid killing EEPROM with loops
}

/*---------------------------------------------------------------------------------
  Get alarm
		alarm : alarm number (Alarm0, Alarm1)
		return : enabled or disable (true..false)
---------------------------------------------------------------------------------*/
bool Clock::isAlarmEnabled(TimeOperation alarm) {
	if (alarm == Alarm0) {
		return (rtc.randReadCCR(ISL12026_INT) & ISL12026_INT_AL0E) != 0;	// Get alarm state bit mask
	} else {
		return (rtc.randReadCCR(ISL12026_INT) & ISL12026_INT_AL1E) != 0;
	}
}

bool Clock::isAlarmActive(TimeOperation alarm) {
	if (alarm == Alarm0) {
		return rtc.randReadCCR(ISL12026_SR) & 0x20;							// Get alarm state bit
	} else {
		return rtc.randReadCCR(ISL12026_SR) & 0x40;
	}
}


// Private Methods //////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------------
  Get time and date page in time-date structure form display
		op : get time register (CurrentTime, Alarm0, Alarm1)
		return : structure with all time-date registers value with alarm bit
---------------------------------------------------------------------------------*/
TimeDate Clock::GetTimeDate(TimeOperation op)
{
    TimeDate t;
	if (op == CurrentTime) {
		readTimeDateRegisters(t, ISL12026_SC, false);						// Get time and date RTC page in time-date structure with flags
	} else  if (op == Alarm0) {
		readTimeDateRegisters(t, ISL12026_SCA0, true);						// Get time and date ALARM0 page in time-date structure without alarm flag
	} else if (op == Alarm1) {
		readTimeDateRegisters(t, ISL12026_SCA1, true);						// Get time and date ALARM1 page in time-date structure without alarm flag
	}
	
	return t;
}

/*---------------------------------------------------------------------------------
  Copy time values from individual variables to a time-date structure and convert int to bcd representation form writing to chip
		hours : hours (1..24 or 1..12 depending of TimeAmPm)
		minutes : minutes (1..60)
		seconds : seconds (1..60)
		return : structure with all time-date registers value
---------------------------------------------------------------------------------*/
void Clock::copyTime(TimeDate &dest, unsigned int hours, unsigned int minutes, unsigned int seconds, TimeAmPm ampm) {
	dest.sc = (int2bcd(seconds) & 0x7F) | (dest.sc & 0x80);
	dest.mn = (int2bcd(minutes) & 0x7F) | (dest.mn & 0x80);
	
	// Keep previous value of MSB
	uint8_t msb = dest.hr & 0x80;
	if (ampm == HOUR_24) {
		// Add MIL FLAG
		dest.hr = int2bcd(hours);
	} else if (ampm == HOUR_12_AM) {
		// 12-hour AM
		dest.hr = int2bcd(hours) & 0x1F;
	} else { // 12-hour PM
		dest.hr = (int2bcd(hours) & 0x1F) | ISL12026_HR_PM;
	}
	dest.hr = (dest.hr & 0x7F) | msb;
}

/*---------------------------------------------------------------------------------
  Copy date values from individual variables to a time-date structure and convert int to bcd representation form writing to chip
		day : day (1..31 depending of month)
		month : month (1..12)
		year : year (0..99)
		dayOfWeek : day of week (Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday)
		return : structure with all time-date registers value
---------------------------------------------------------------------------------*/
void Clock::copyDate(TimeDate &dest, unsigned int day, unsigned int month, unsigned int year, WeekDay dayOfWeek) {
	dest.dt = (int2bcd(day) & 0x7F) | (dest.dt & 0x80);
	dest.mo = (int2bcd(month) & 0x7F) | (dest.mo & 0x80);
	dest.yr = (int2bcd(year) & 0x7F) | (dest.yr & 0x80);
	dest.dw = (int2bcd(dayOfWeek) & 0x7F) | (dest.dw & 0x80);
	dest.y2k = 0x20;
}

/*---------------------------------------------------------------------------------
  Read time and date page from chip in raw mode
		return : structure with all time-date registers value
		removeAlarmEnableBits : mask or not alarm bit (true..false)
---------------------------------------------------------------------------------*/
void Clock::readTimeDateRegisters(TimeDate &td, uint8_t offset, bool removeAlarmEnableBits) {
	uint8_t *p;
		
	p = &td.sc;
	while (p <= &td.y2k) {
		if (removeAlarmEnableBits) {
			*p = rtc.randReadCCR(p - &td.sc + offset) & 0x7F;
		} else {
			*p = rtc.randReadCCR(p - &td.sc + offset);
		}
		p++;
	}
}

/*---------------------------------------------------------------------------------
  Convert int to bcd representation
		val_int : int value
		return : bcd value
---------------------------------------------------------------------------------*/
unsigned int Clock::int2bcd(unsigned int val_int)
{
  return 16*(val_int/10)+(val_int%10);
}

/*---------------------------------------------------------------------------------
  Convert bcd to int representation
		val_bcd : bcd value
		return : int value
---------------------------------------------------------------------------------*/
unsigned int Clock::bcd2int(unsigned val_bcd)
{
  return 10*(val_bcd/16)+(val_bcd%16);
}

