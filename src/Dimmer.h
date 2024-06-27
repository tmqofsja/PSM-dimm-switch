#include <Arduino.h>
#include "pindef.h"

//#include "lcd/lcd.h"
//#include "esp_comms.h"
//#include "profiling_phases.h"


#include <EasyNextionLibrary.h>


enum class NextionPage: byte {
  /* 00 */ Home,
  /* 01 */ BrewPreinfusion,
  /* 02 */ BrewSoak,
  /* 03 */ BrewProfiling,
  /* 04 */ BrewManual,
  /* 05 */ Flush,
  /* 06 */ Descale,
  /* 07 */ SettingsBoiler,
  /* 08 */ SettingsSystem,
  /* 09 */ BrewGraph,
  /* 0A */ BrewMore,
  /* 0B */ ShotSettings,
  /* 0C */ BrewTransitionProfile,
  /* 0D */ GraphPreview,
  /* 0E */ KeyboardNumeric,
  /* 0F */ Led
};

extern volatile NextionPage lcdCurrentPageId;
extern volatile NextionPage lcdLastCurrentPageId;

void lcdInit(void);
//bool lcdCheckSerialInit(const char* expectedOutput, size_t expectedLen);

void lcdListen(void);

void lcdShowPopup(const char *msg);






