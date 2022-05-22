#include "webserver.h"
#include <iostream>


using namespace std;

void WebServer::start() {
    this->listeners();
    cout<<"Server starting @ " + this->IP + ":" + to_string(this->PORT)<<endl;
    this->listen(this->IP.c_str(), this->PORT);
}

void WebServer::end() {
    this->stop();
    cout<<"Server stopped."<<endl;
}

WebServer::WebServer(string ip, int port) {
    this->PORT = port;
    this->IP = ip;
}