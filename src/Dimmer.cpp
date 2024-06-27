#include <Arduino.h>
#include "Dimmer.h"
#include "pump.h"

const int REFRESH_TIME = 100;           // time to refresh the Nextion page every 100 ms
unsigned long refresh_timer = millis();  // timer for refreshing Nextion's page

const unsigned int valueFactor = 4; // precalculated constant 1024 [10 bit ADC resolution] / 128 [range + 1] / 2
volatile unsigned int value = 0;

EasyNex myNex(USART_LCD);

static void cpsInit(void);
static void lcdRefresh(void);
 
void setup() {

      Serial.begin(115200);
      //Pump
      setPumpOff();
      lcdInit();
      cpsInit();
      // Pump init
      pumpInit(60u,myNex.readNumber("sP.pump_zero.val") / 10000.f); 
      }

int16_t tem;

void loop() {
  lcdRefresh();
    tem = millis()-refresh_timer;
  if(tem >= REFRESH_TIME){ 
    //setPumpToRawValue(myNex.readNumber("pi.readTemp.val"));
    delay(500);
    refresh_timer = millis();  
  }
}


void lcdInit(void) {
  myNex.begin(115200);
  myNex.writeStr("splash.build_version.txt", "AUTO_VERSION");
}

void lcdListen(void) {
  myNex.NextionListen();
  lcdCurrentPageId = static_cast<NextionPage>(myNex.currentPageId);
}

void lcdWakeUp(void) {
  myNex.writeNum("sleep", 0);
}

static void cpsInit(void) {
  int cps = getCPS();
  if (cps > 110) { // double 60 Hz
    
  } else if (cps > 80) { // double 50 Hz
  } else if (cps > 55) { // 60 Hz
  } else if (cps > 0) { // 50 Hz
  }
}

void trigger1(void) { setPumpFullOn(); 
   lcdShowPopup("PUMP ON");           
   }
void trigger2(void) { setPumpOff();
   lcdShowPopup("PUMP OFF");          
   }
void trigger3(void) {  }
void trigger4(void) {  }
void trigger6(void) {  }
void trigger7(void) {  }
void trigger8(void) {  }
void trigger9(void) {  }
void trigger10(void) {  }

void lcdShowPopup(const char *msg) {
  static unsigned int timer;
  if(millis() > timer + 1150) {
    myNex.writeStr("popupMSG.t0.txt", msg);
    myNex.writeStr("page popupMSG");
    timer = millis();
  }
}

static void lcdRefresh(void) {
  uint16_t tempDecimal;

  if (millis() > pageRefreshTimer) {
      int tmp = myNex.readNumber("pi.readTemp.val");
      if(tmp) setPumpToRawValue(tmp);
    pageRefreshTimer = millis() + REFRESH_SCREEN_EVERY;
  }
}