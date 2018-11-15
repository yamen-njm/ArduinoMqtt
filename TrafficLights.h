#ifndef TRAFFIC_LIGHTS_H
#define TRAFFIC_LIGHTS_H
  
#include <Arduino.h>

#define RW 25// DUE Digital Pin 25*
#define OW 26// DUE Digital Pin 26*
#define VW 27// DUE Digital Pin 24*
  
#define RN 28// DUE Digital Pin 28*
#define ON 14// DUE Digital Pin 14*
#define VN 15// DUE Digital Pin 15*
  
#define RE 29// DUE Digital Pin 29*
#define OE 11// DUE Digital Pin 11*
#define VE 12// DUE Digital Pin 12*
  
#define RS 30// DUE Digital Pin 30*
#define OS 32// DUE Digital Pin 32*
#define VS 9// DUE Digital Pin9*

#define LED1 45// DUE Digital Pin 45*
#define LED2 47// DUE Digital Pin 47*
#define LED3 49// DUE Digital Pin 49*
#define LED4 51// DUE Digital Pin 51*
#define LED5 44// DUE Digital Pin 44*
#define LED6 46// DUE Digital Pin 46*
#define LED7 48// DUE Digital Pin 48*
#define LED8 50// DUE Digital Pin 50*
  
#define APE 31// DUE Digital Pin 31*
#define PPE 41// DUE Digital Pin 41*
  
#define APS 21// DUE Digital Pin 21*
#define PPS 20// DUE Digital Pin 20*
  
#define IL1 17// DUE Digital Pin 19*
#define IL2 16// DUE Digital Pin 18*
#define IL3 19// DUE Digital Pin 17*
#define IL4 18// DUE Digital Pin 16*
  
#define BP1 7// DUE Digital Pin7*
#define BP2 6// DUE Digital Pin6*
#define BP3 5// DUE Digital Pin5*
#define BP4 8// DUE Digital Pin8*
  
#define DPN 2// DUE Digital Pin2*
#define DPE 3// DUE Digital Pin3*
  
#define DISPA 33// DUE Digital Pin 33
#define DISPB 34// DUE Digital Pin 34
#define DISPC 35// DUE Digital Pin 35
#define DISPD 36// DUE Digital Pin 36
#define DISPE 37// DUE Digital Pin 37
#define DISPF 38// DUE Digital Pin 38
#define DISPG 39// DUE Digital Pin 39
#define DISPP 40// DUE Digital Pin 40  
  
#define LDR A0// DUE Digital Pin A0*
#define POT A1// DUE Digital Pin A1
  
#define APW A10// DUE Digital PinA11*
#define PPW A11// DUE Digital PinA10*
  
#define APN A9// DUE Digital Pin A9*
#define PPN A8// DUE Digital Pin A8*

enum Color {Red, Orange, Green};

enum Orientation {North, East, South, West};

class TrafficLights {
 public:
  void setUp();
  void setLight(Orientation o, Color c);
  void setCrossing(Orientation o, Color c);
  private:
  void setInput(int pin);
  void setOutput(int pin);
  void doEnable(int pin, bool mode);
};
#endif

