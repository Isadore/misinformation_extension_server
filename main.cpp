#include "./classes/webserver.h"

using namespace std;

int main() {

    WebServer server("127.0.0.1", 3000);
    server.start();

    return 0;

}