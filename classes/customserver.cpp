#include "customserver.h"
#include "utils.h"
#include "../libs/nlohmann/json.hpp"

void CustomServer::listeners() {

    this->Get("/", [](const httplib::Request&, httplib::Response& res) {
        string page = Utils::getFile("./site/site.html");
        res.set_content(page, "text/html");
    });

    this->Get("/site.css", [](const httplib::Request&, httplib::Response& res) {
        string page = Utils::getFile("./site/site.css");
        res.set_content(page, "text/css");
    });

    this->Get("/loading.gif", [](const httplib::Request&, httplib::Response& res) {
        string page = Utils::getFile("./site/loading.gif");
        res.set_content(page, "image/gif");
    });

    this->Post("/text_analysis", [](const httplib::Request& req, httplib::Response& res) {
        nlohmann::json data = nlohmann::json::parse(req.body.c_str(), nullptr, false);
        if(data.contains("text")) {
            try {
                const string uuid = Utils::generateUUID();
                string text = data["text"];
                Utils::sanitizeText(text);
                const string command = "python3 ./textanalysis.py \"" + text + "\" \"" + uuid + "\"";
                system(command.c_str());
                string filepath = "./analysis_" + uuid + ".json";
                string analysisResult = Utils::getFile(filepath);
                Utils::addAnalysisDescription(analysisResult);
                res.set_content(analysisResult, "text/plain");
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

    this->Get("/samples", [](const httplib::Request& req, httplib::Response& res) {
        bool failed = false;
        if(req.has_param("number")) {
            try {
                string param = req.get_param_value("number");
                int sample_number = stoi(param);
                if(sample_number > 0 && sample_number < 4) {
                    string sample = Utils::getFile("./site/samples/" + param + ".txt");
                    res.set_content(sample, "text/plain");
                } else {
                    failed = true;
                }
            } catch(...) {
                failed = true;
            }
        } else {
            failed = true;
        }
        if(failed) {
            res.status = 400;
            res.set_content("400: Invalid parameters", "text/plain");
        }
    });

}