#include "utils.h"
#include <fstream>
#include <string> // for getline
#include <regex>
#include "../libs/nlohmann/json.hpp"
#include "../libs/uuid.h"

using namespace std;

// modified code from https://www.cplusplus.com/reference/istream/istream/read/
string Utils::getFile(string path) {
    ifstream file(path, ifstream::binary);
    if(!file || !file.is_open()) {
        throw "Requested file does not exist.";
    } else {
        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);
        char* buf = new char[length];
        file.read(buf, length);
        file.close();
        string s = "";
        for(int i = 0; i < length; i++) {
            s += string(1, buf[i]);
        }
        delete[] buf;
        return s; 
    }
}

//code from https://github.com/mariusbancila/stduuid
string Utils::generateUUID() {
    random_device rd;
    auto seed_data = array<int, mt19937::state_size> {};
    generate(begin(seed_data), end(seed_data), ref(rd));
    seed_seq seq(begin(seed_data), end(seed_data));
    mt19937 generator(seq);
    uuids::uuid_random_generator gen{generator};
    uuids::uuid rand_id = gen();
    return uuids::to_string(rand_id);
}

void Utils::addAnalysisDescription(string& jsonstr) {
    nlohmann::json j1 = nlohmann::json::parse(jsonstr);
    float polarity = j1["polarity"];
    float subjectivity = j1["subjectivity"];
    string description = "";
    if(polarity < -.9) {
        description = "Text is extremely negative";
    } else if(polarity < -.6) {
        description = "Text is very negative";
    } else if(polarity < -.3) {
        description = "Text is moderately negative";
    } else if(polarity < 0) {
        description = "Text is slightly negative";
    } else if(polarity == 0) {
        description = "Text is likely neutral";
    } else if(polarity < .3) {
        description = "Text is slightly positive";
    } else if(polarity < .6) {
        description = "Text is moderately positive";
    } else if(polarity < .9) {
        description = "Text is very positive";
    } else {
        description = "Text is extremely positive";
    }
    if(subjectivity < .1) {
        description += "\nText is likely objective";
    } else if(subjectivity < .3) {
        description += "\nText is slightly subjective";
    } else if(subjectivity < .6) {
        description += "\nText is moderately subjective";
    } else if(subjectivity < .9) {
        description += "\nText is very subjective";
    } else {
        description += "\nText is extremely subjective";
    }
    if(polarity == 0 && subjectivity == 0) {
        description = "Text is either too short to analyze or completely neutral";
    }
    j1["description"] = description;
    jsonstr = j1.dump();
}

void Utils::sanitizeText(string& text) {
    regex r("[\"\']+");
    text = regex_replace(text, r, "", regex_constants::match_any);
}