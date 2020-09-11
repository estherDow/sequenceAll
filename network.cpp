#include "network.h"



extern char ssid[];
extern char pass[];
WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
extern uint8_t ip[4];
const IPAddress outIp(ip[0],ip[1],ip[2],ip[3]);        // remote IP of your computer

//const IPAddress outIp();        // remote IP of your computer
//const IPAddress outIp(172,24,3,134);        // remote IP of your computer
extern unsigned int outPort;          // remote port to receive OSC
extern unsigned int localPort;        // local port to listen for OSC packets (actually not used for sending)


void wlan::begin() {


  Serial.printf(" Connecting to: %s\n", ssid );
  WiFi.begin(ssid,pass);

  //Warten auf Verbindung
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Wifi connected!\n IP Address: \n");
  Serial.println(WiFi.localIP());

  //Init udp and OSC
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(localPort);
}


void wlan::sendOsc(uint8_t on, const char* Voice, uint8_t param) {


  OSCMessage msg(Voice);
  msg.add(on);
  msg.add(param);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  //Serial.println("OKsent"); //Debug relic
  Udp.endPacket();
  msg.empty();
  Udp.stop();
}
