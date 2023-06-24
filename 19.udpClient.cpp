#include "udpClient.hpp"
#include <memory>
using namespace Client;

static void Usage(string proc) {
     cerr << "\nUsage:\n\t" << proc << " server_ip server_port\n\n";
}
