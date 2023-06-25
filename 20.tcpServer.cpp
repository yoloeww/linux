#include "tcpServer.hpp"
#include <memory>

using namespace server;
using namespace std;

static void Usage(string proc)
{
    cout << "\nUsage:\n\t" << proc << " local_port\n\n";
}

// tcp服务器，启动上和udp server一模一样
// ./tcpserver local_port
int main(int argc, char *argv[])
{ 
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }
    uint16_t port = atoi(argv[1]);

    unique_ptr<TcpServer> tsvr(new TcpServer(port));
    tsvr->initServer();
    tsvr->start();

    return 0;
}
