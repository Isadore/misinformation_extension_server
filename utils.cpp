#include "utils.h"
#include <fstream>
#include <string> // for getline

using namespace std;

string Utils::getFile(string path) {
    string text = "";
    ifstream file(path);
    string line;
    while (getline(file, line))  {
        text += line;
    }
    return text;
}