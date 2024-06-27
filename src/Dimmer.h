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

//Timers
unsigned long systemHealthTimer;
unsigned long pageRefreshTimer;
unsigned long pressureTimer;
unsigned long brewingTimer;
unsigned long thermoTimer;
unsigned long scalesTimer;
unsigned long flowTimer;
unsigned long steamTime;

#define GET_PRESSURE_READ_EVERY 10 // Pressure refresh interval (ms)
#define GET_SCALES_READ_EVERY   100 // Scales refresh interval (ms)
#define REFRESH_SCREEN_EVERY    150 // Screen refresh interval (ms)
#define REFRESH_FLOW_EVERY      50 // Flow refresh interval (ms)
#define HEALTHCHECK_EVERY       30000 // System checks happen every 30sec
#define BOILER_FILL_START_TIME  3000UL // Boiler fill start time - 3 sec since system init.
#define BOILER_FILL_TIMEOUT     8000UL // Boiler fill timeout - 8sec since system init.
#define BOILER_FILL_SKIP_TEMP   85.f // Boiler fill skip temperature threshold
#define SYS_PRESSURE_IDLE       0.7f // System pressure threshold at idle
#define MIN_WATER_LVL           10u // Min allowable tank wa


