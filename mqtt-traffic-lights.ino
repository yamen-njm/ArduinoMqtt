//#include <system.h>
#include <Ethernet.h>
#include <SPI.h>
#include <PubSubClient.h>
#include<time.h>

#include "TrafficLights.h"

const char ID[]     = "mqtt-traffic-lights-13";
const char TOPIC[]  = "street/server";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,137,1);
IPAddress myDns(10, 188, 0, 1);
const char* mqttServer = "m15.cloudmqtt.com";
const int mqttPort = 18724;
const char* mqttUser = "senfdtah";
const char* mqttPassword = "QFMngZSY4SL1";

time_t t;

EthernetClient ethClient  ;
PubSubClient client(ethClient); 
TrafficLights trafficlights;
//MQTTClient mqtt;

enum State {RedRed, OrangeRed, GreenRed, RedOrange, RedGreen};

enum Direction {NorthSouth, EastWest};

State state;

Direction direction;

unsigned long timestamp;

bool hasSpent(int n, unsigned long t) {
  return (millis() - t) >= (n * 1000);
}

void doRedRed() {
  trafficlights.setLight(North, Red);
  trafficlights.setLight(East, Red);
  trafficlights.setLight(South, Red);
  trafficlights.setLight(West, Red);
  trafficlights.setCrossing(North, Red);
  trafficlights.setCrossing(East, Red);
  trafficlights.setCrossing(South, Red);
  trafficlights.setCrossing(West, Red);
  time(&t);
  client.publish("street/server", "{\"streetId\":\"127.0.0.1\",\"north\":\"rouge\",\"est\":\"rouge\",\"ouest\":\"rouge\",\"sud\":\"rouge\"}" );
}

void doOrangeRed() {
  trafficlights.setLight(North, Orange);
  trafficlights.setLight(East, Red);
  trafficlights.setLight(South, Orange);  
  trafficlights.setLight(West, Red);
  trafficlights.setCrossing(North, Red);
  trafficlights.setCrossing(East, Red);
  trafficlights.setCrossing(South, Red);
  trafficlights.setCrossing(West, Red);
  client.publish("street/server", "{\"streetId\":\"127.0.0.1\",\"north\":\"orange\",\"est\":\"rouge\",\"ouest\":\"rouge\",\"sud\":\"orange\"}");
}

void doGreenRed() {
  trafficlights.setLight(North, Green);
  trafficlights.setLight(East, Red);
  trafficlights.setLight(South, Green);
  trafficlights.setLight(West, Red);
  trafficlights.setCrossing(North, Red);
  trafficlights.setCrossing(East, Green);
  trafficlights.setCrossing(South, Red);
  trafficlights.setCrossing(West, Green);
  client.publish("street/server", "{\"streetId\":\"127.0.0.1\",\"north\":\"vert\",\"est\":\"rouge\",\"ouest\":\"rouge\",\"sud\":\"vert\"}");
}

void doRedOrange() {
  trafficlights.setLight(North, Red);
  trafficlights.setLight(East, Orange);
  trafficlights.setLight(South, Red);
  trafficlights.setLight(West, Orange);
  trafficlights.setCrossing(North, Red);
  trafficlights.setCrossing(East, Red);
  trafficlights.setCrossing(South, Red);
  trafficlights.setCrossing(West, Red);
  client.publish("street/server", "{\"streetId\":\"127.0.0.1\",\"north\":\"rouge\",\"est\":\"orange\",\"ouest\":\"orange\",\"sud\":\"rouge\"}");
}

void doRedGreen() {
  trafficlights.setLight(North, Red);
  trafficlights.setLight(East, Green);
  trafficlights.setLight(South, Red);
  trafficlights.setLight(West, Green);
  trafficlights.setCrossing(North, Green);
  trafficlights.setCrossing(East, Red);
  trafficlights.setCrossing(South, Green);
  trafficlights.setCrossing(West, Red);
  client.publish("street/server", "{\"streetId\":\"127.0.0.1\",\"north\":\"rouge\",\"est\":\"vert\",\"ouest\":\"vert\",\"sud\":\"rouge\"}");
}

void doUpdate() {
  if (state == RedRed) {
    if (hasSpent(1, timestamp)) {
      timestamp = millis();
      if (direction == NorthSouth) {
        direction = EastWest;
        state = RedGreen;
        doRedGreen();
      } else if (direction == EastWest) {
        direction = NorthSouth;
        state = GreenRed;
        doGreenRed();
      }
    }
  } else if (state == OrangeRed) {
    if (hasSpent(1, timestamp)) {
      timestamp = millis();
      state = RedRed;
      doRedRed();
    }
  } else if (state == GreenRed) {
    if (hasSpent(6, timestamp)) {
      timestamp = millis();
      state = OrangeRed;
      doOrangeRed();
    }
  } else if (state == RedOrange) {
    if (hasSpent(1, timestamp)) {
      timestamp = millis();
      state = RedRed;
      doRedRed();
    }
  } else if (state == RedGreen) {
    if (hasSpent(6, timestamp)) {
      timestamp = millis();
      state = OrangeRed;
      doOrangeRed();
    }
  }
}

void doConnect() {
 client.setServer(mqttServer, mqttPort);
 client.setCallback(callback);
   while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("Arduino Yamen", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  client.subscribe(TOPIC);
 
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void info() {
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);

  trafficlights.setUp();
  state = RedRed;
  direction = NorthSouth;
  timestamp = millis();

  doConnect();
  
  delay(1000);
  doRedRed();
}

void loop() {
  doUpdate();
}
