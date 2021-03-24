#ifndef ISENLiquidCrystal_h
#define ISENLiquidCrystal_h
#include <inttypes.h>

// NIH 27/02/2016
//#include "../LiquidCrystal/LiquidCrystal.h"
#include "LiquidCrystal.h"

#include "Clock.h"

class ISENLiquidCrystal : public LiquidCrystal {
public:
  ISENLiquidCrystal();
  void clear_line(int row);
  void displayTime(Clock &ck, TimeOperation op);
  void displayDate(Clock &clock, TimeOperation op);
};

#endif
