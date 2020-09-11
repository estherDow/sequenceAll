#include "network.h"


//  char ssid[] = "HANGAR_convidats";
//  char pass[] = "convidatsHANGAR";

char ssid[] = "marcia.net_enlaluna";
char pass[] = "Log_tePiacesse7No.Pasaran";

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP

const IPAddress outIp(192,168,0,10);        // remote IP of your computer
//const IPAddress outIp(172,24,3,134);        // remote IP of your computer

const unsigned int outPort = 57120;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

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
  Serial.println("OKsent");
  Udp.endPacket();
  msg.empty();
  Udp.stop();
}
