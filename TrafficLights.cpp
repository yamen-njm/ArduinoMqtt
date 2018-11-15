#include <Arduino.h>
#include "TrafficLights.h"

void TrafficLights::setInput(int pin) {
  pinMode(pin, INPUT);
}
void TrafficLights::setOutput(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}
void TrafficLights::doEnable(int pin, bool mode) {
  if (mode) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

void TrafficLights::setCrossing(Orientation o, Color c) {
  if (o == North) {
    if (c == Red) {
      doEnable(APN, true);
      doEnable(PPN, false);
    } else if (c == Green) {
      doEnable(APN, false);
      doEnable(PPN, true);
    }
  } else if (o == East) {
    if (c == Red) {
      doEnable(APE, true);
      doEnable(PPE, false);
    } else if (c == Green) {
      doEnable(APE, false);
      doEnable(PPE, true);
    }
  } else if (o == South) {
    if (c == Red) {
      doEnable(APS, true);
      doEnable(PPS, false);
    } else if (c == Green) {
      doEnable(APS, false);
      doEnable(PPS, true);
    }
  } else if (o == West) {
    if (c == Red) {
      doEnable(APW, true);
      doEnable(PPW, false);
    } else if (c == Green) {
      doEnable(APW, false);
      doEnable(PPW, true);
    }
  }
}

void TrafficLights::setLight(Orientation o, Color c) {
  if (o == North) {
    if (c == Red) {
      doEnable(RN, true);
      doEnable(ON, false);
      doEnable(VN, false);
    } else if (c == Orange) {
      doEnable(RN, false);
      doEnable(ON, true);
      doEnable(VN, false);    
    } else if (c == Green) {
      doEnable(RN, false);
      doEnable(ON, false);
      doEnable(VN, true);
    }
  } else if (o == East) {
    if (c == Red) {
      doEnable(RE, true);
      doEnable(OE, false);
      doEnable(VE, false);
    } else if (c == Orange) {
      doEnable(RE, false);
      doEnable(OE, true);
      doEnable(VE, false);    
    } else if (c == Green) {
      doEnable(RE, false);
      doEnable(OE, false);
      doEnable(VE, true);
    }
  } else if (o == South) {
    if (c == Red) {
      doEnable(RS, true);
      doEnable(OS, false);
      doEnable(VS, false);
    } else if (c == Orange) {
      doEnable(RS, false);
      doEnable(OS, true);
      doEnable(VS, false);    
    } else if (c == Green) {
      doEnable(RS, false);
      doEnable(OS, false);
      doEnable(VS, true);
    }
  } else if (o == West) {
    if (c == Red) {
      doEnable(RW, true);
      doEnable(OW, false);
      doEnable(VW, false);
    } else if (c == Orange) {
      doEnable(RW, false);
      doEnable(OW, true);
      doEnable(VW, false);    
    } else if (c == Green) {
      doEnable(RW, false);
      doEnable(OW, false);
      doEnable(VW, true);
    }
  }
}

void TrafficLights::setUp() {
  setOutput(LED1);
  setOutput(LED2);
  setOutput(LED3);
  setOutput(LED4);
  setOutput(LED5);
  setOutput(LED6);
  setOutput(LED7);
  setOutput(LED8);

  setOutput(RW);
  setOutput(RN);
  setOutput(RS);
  setOutput(RE);

  setOutput(OW);
  setOutput(OS);
  setOutput(ON);
  setOutput(OE);

  setOutput(VN);
  setOutput(VE);
  setOutput(VW);
  setOutput(VS);

  setOutput(APE);
  setOutput(APS);
  setOutput(PPE);
  setOutput(PPS);
  setOutput(APW);
  setOutput(APN);
  setOutput(PPN);
  setOutput(PPW);

  setOutput(DISPA);
  setOutput(DISPB);
  setOutput(DISPC);
  setOutput(DISPD);
  setOutput(DISPE);
  setOutput(DISPF);
  setOutput(DISPG);
  setOutput(DISPP);  

  setInput(BP1);
  setInput(BP2);
  setInput(BP3);
  setInput(BP4);
  setInput(DPN);
  setInput(DPE);

  setInput(IL1);
  setInput(IL2);
  setInput(IL3);
  setInput(IL4);

  setInput(LDR);
}
