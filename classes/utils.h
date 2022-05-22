#ifndef utils_h
#define utils_h

#include <iostream>
using namespace std;

class Utils {

    public:
        static string getFile(string path);
        static void addAnalysisDescription(string& jsonstr);
        static void sanitizeText(string &text);
        static string generateUUID();

};

#endif