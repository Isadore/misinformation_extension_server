#ifndef webserver_h
#define webserver_h

#include "../libs/httplib.h"
#include <iostream>
using namespace std;

class WebServer {

    httplib::Server server;
    int PORT;
    string IP;

    private:
        void listeners();
    
    public:
        WebServer(string ip, int port);
        void start();
        void stop();

};

#endif