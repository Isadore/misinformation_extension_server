#include "utils.h"

string Utils::getFile(string path) {
    string text = "";
    ifstream file(path);
    string line;
    while (getline(file, line))  {
        text += line;
    }
    return text;
}