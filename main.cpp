#include "./classes/customserver.h"

using namespace std;

int main() {

    CustomServer server("127.0.0.1", 3000);
    server.start();

    return 0;

}