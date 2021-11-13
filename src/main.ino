#include <Clock.h>
#include <Voice.h>
#include <SignalTypes.h>
#include <Arduino.h>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <ArduinoJson.h>
//#include <FreeRTOS.h>

class dummyObserver : public IObserver {
public:
  dummyObserver() {};
  void update(SignalTypes sender, int _msg);

};

void dummyObserver::update(SignalTypes _sender, int _msg){
  //Serial.println("Received Update:");
  //Serial.println(_msg);
  //Serial.println("From:");
  //Serial.println(_sender);
}

Clock sClock;


WebServer server(80);
WebServer *serverPtr = &server;

SignalTypes trigger = TRIGGER;
Voice *kick = new Voice(trigger, 16);
dummyObserver *dummy = new dummyObserver();

TaskHandle_t network;
TaskHandle_t sequencer;

// JSON data buffer
StaticJsonDocument<250> jsonDocument;
char buffer[250];

const char * ssid;
const char *  password;

void setSTA() {
  Serial.println("setSTA was called");
  if (serverPtr->hasArg("plain") == false) {
  //handle error here
  }
  serverPtr->send(200, "application/json", "{}");
  String body = serverPtr->arg("plain");
  deserializeJson(jsonDocument, body);
  if (WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect();
    Serial.println("Wifi was disconnected");
  }

  _doSetSTA(jsonDocument["ssid"], jsonDocument["password"]);
}

int _doSetSTA(const char * ssid, const char *  password) {
    //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting to wifi...");
    }
    Serial.println("connected to wifi...");
    Serial.println(WiFi.localIP());

    return 1;
}

IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional

void setAP() {
  if (serverPtr->hasArg("plain") == false) {
  //handle error here
  }
  serverPtr->send(200, "application/json", "{}");
  String body = serverPtr->arg("plain");
  deserializeJson(jsonDocument, body);
  if (WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect();
  }
  _doSetAP(jsonDocument["ssid"], jsonDocument["password"]);
}

int _doSetAP(const char * ssid, const char *  password) {
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
  Serial.println("AP Failed to configure");
  }

  WiFi.softAP(ssid, password);
  return 1;
}

void getTestResponse() {
  serverPtr->send(200, "text/plain", "Hello World");

}

void setup() {
  Serial.begin(115200);
  sClock.setBeatsPerMinute(25);
  sClock.attach(kick);

  kick->attach(dummy);
  kick->setQuarterNoteDivisions(20);
  Serial.printf("Subdivisions per quarternote: %i\n", kick->getQuarterNoteDivisions());
  kick->setStep(1,1);
  kick->setStep(1,5);
  kick->setStep(1,9);
  kick->setStep(1,13);



  _doSetSTA("iPhone de Paula", "pautsau1");
  Serial.println(WiFi.localIP());

    if(!MDNS.begin("sequenceall")) {
       Serial.println("Error starting mDNS");
       return;
  }
  MDNS.addService("http", "tcp", 80);
  serverPtr->on("/set_sta", HTTP_POST, setSTA);
  serverPtr->on("/set_ap",HTTP_POST, setAP);
  serverPtr->on("/hello",getTestResponse);
  serverPtr->begin();

}


void loop() {
  sClock.timer();
  serverPtr->handleClient();
}
