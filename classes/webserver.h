#ifndef webserver_h
#define webserver_h

#include "../libs/httplib.h"
#include <iostream>
using namespace std;

class WebServer : protected httplib::Server {
    
    int PORT;
    string IP;

    protected:
        virtual void listeners() = 0;
    
    public:
        WebServer(string ip, int port);
        void start();
        void end();

};

#endif