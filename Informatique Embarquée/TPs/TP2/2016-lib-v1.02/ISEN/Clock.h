// D.Delannoy & O.Rossiny le 16 janvier 2012
//
// Version 1.0
//

#ifndef Clock_h
#define Clock_h

#include <inttypes.h>
#include <../ISL12026/ISL12026.h>

enum WeekDay {
	Sunday = 0,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};

enum TimeOperation {
	CurrentTime = 0,
	Alarm0,
	Alarm1
};

enum TimeAmPm {
	HOUR_24 = 0,
	HOUR_12_AM,
	HOUR_12_PM
};

struct TimeDate {
	uint8_t sc, mn, hr, dt, mo, yr, dw, y2k;
};

class Clock
{
  private:
    ISL12026 rtc;
	unsigned int bcd2int(unsigned val_bcd);
	unsigned int int2bcd(unsigned val_int);
	void copyDate(TimeDate &dest, unsigned int day, unsigned int month, unsigned int year, WeekDay dayOfWeek);
	void copyTime(TimeDate &dest, unsigned int hours, unsigned int minutes, unsigned int seconds, TimeAmPm ampm);
	void readTimeDateRegisters(TimeDate &td, uint8_t offset, bool removeAlarmEnableBits);
	TimeDate GetTimeDate(TimeOperation op);
  public:
    Clock(uint8_t rtcAddr = 0);
    void SetTime(unsigned hours, unsigned minutes, unsigned seconds, TimeAmPm ampm, TimeOperation op = CurrentTime);
	void SetDate(unsigned day, unsigned month, unsigned year, WeekDay dayOfWeek, TimeOperation op = CurrentTime);
	void GetTime(unsigned *hours, unsigned *minutes, unsigned *seconds, TimeAmPm *ampm, TimeOperation op = CurrentTime);
	void GetDate(unsigned *day, unsigned *month, unsigned *year, WeekDay *dayOfWeek, TimeOperation op = CurrentTime);
	
	void setAlarm(TimeOperation alarm, bool enabled);
	bool isAlarmEnabled(TimeOperation alarm);
	bool isAlarmActive(TimeOperation alarm);
};

#endif /* Clock_h */

