#include "utils.h"
#include <fstream>
#include <string> // for getline
#include "nlohmann/json.hpp"

using namespace std;

string Utils::getFile(string path) {
    string text = "";
    ifstream file(path);
    if(!file.is_open()) throw "Requested file does not exist.";
    string line;
    while (getline(file, line))  {
        text += line;
    }
    return text;
}

void Utils::addAnalysisDescription(string& jsonstr) {
    nlohmann::json j1 = nlohmann::json::parse(jsonstr);
    float polarity = j1["polarity"];
    float subjectivity = j1["subjectivity"];
    if(polarity == 0 && subjectivity == 0) {
        j1["description"] = "Text is either too short to analyze or completely neutral";
    }
    if(polarity < -.9) {
        j1["description"] = "Text is extremely negative";
    } else if(polarity < -.6) {
        j1["description"] = "Text is fairly negative";
    } else if(polarity < -.3) {
        j1["description"] = "Text is moderately negative";
    } else if(polarity < 0) {
        j1["description"] = "Text is slightly negative";
    }
    jsonstr = j1.dump(); 
}

string Utils::sanitizeText(string text) {

}