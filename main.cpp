#include <iostream>
#include <fstream>
#include "httplib.h"
#include "utils.h"

using namespace std;

const int PORT = 3000;

int main() {

    httplib::Server server;
    
    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        string page = Utils::getFile("site.html");
        res.set_content(page, "text/html");
    });

    server.Get("/site.css", [](const httplib::Request&, httplib::Response& res) {
        string page = Utils::getFile("site.css");
        res.set_content(page, "text/css"); 
    });


    std::cout<<"Server starting @ port " + std::to_string(PORT)<<std::endl;
    server.listen("127.0.0.1", PORT);

    return 0;

}