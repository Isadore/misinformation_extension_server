#include "webserver.h"
#include "utils.h"
#include <iostream>

using namespace std;

void WebServer::listeners() {

    this->server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        string page = Utils::getFile("site.html");
        res.set_content(page, "text/html");
    });

    this->server.Get("/site.css", [](const httplib::Request&, httplib::Response& res) {
        string page = Utils::getFile("site.css");
        res.set_content(page, "text/css"); 
    });

    this->server.Get("/loading.gif", [](const httplib::Request&, httplib::Response& res) {
        string page = Utils::getFile("loading.gif");
        res.set_content(page, "image/gif");
    });

    this->server.Get("/text_analysis", [](const httplib::Request& req, httplib::Response& res) {
        if(req.has_param("text") && req.has_param("id")) {
            try {
                const string command = "python3 textanalysis.py \"" + req.get_param_value("text") + "\" \"" +  req.get_param_value("id") + "\"";
                system(command.c_str());
                string filepath = "analysis_" + req.get_param_value("id") + ".json";
                string analysisResult = Utils::getFile(filepath);
                Utils::addAnalysisDescription(analysisResult);
                res.set_content(analysisResult, "application/json");
                remove(filepath.c_str());
            } catch (string ex) {
                res.status = 500;
                res.set_content(ex, "text/plain");
            }
        } else {
            res.status = 400;
            res.set_content("400: Invalid parameters", "text/plain");
        }
    });

}

void WebServer::start() {
    this->listeners();
    cout<<"Server starting @ " + this->IP + ":" + to_string(this->PORT)<<endl;
    this->server.listen(this->IP.c_str(), this->PORT);
}

void WebServer::stop() {
    this->server.stop();
    cout<<"Server stopped."<<endl;
}

WebServer::WebServer(string ip, int port) {
    this->PORT = port;
    this->IP = ip;
}