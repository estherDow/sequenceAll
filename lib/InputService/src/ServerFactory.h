#ifndef SERVERFACTORY
#define SERVERFACTORY
#include <WebServer.h>
class ServerFactory {
public:
  static WebServer * make() {
    WebServer *serverPtr;
    WebServer server(80);
    serverPtr = & server;
    return serverPtr;
  }

};
#endif
