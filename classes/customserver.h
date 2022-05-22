#ifndef customserver_h
#define customserver_h

#include "webserver.h"
#include <iostream>

class CustomServer : public WebServer {

    protected:
        virtual void listeners();
    
    public:
        CustomServer(std::string ip, int port) : WebServer(ip, port) {}

};

#endif