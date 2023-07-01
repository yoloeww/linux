#include <iostream>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <functional>
#include <sys/wait.h>
#include <signal.h>
#include <arpa/inet.h>
#include <cstdlib.h>
#include <unistd.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include "Protocol.hpp"

using namespace std;

namespace server {
    enum {
        USAGE_ERR = 1,
        SOCKET_ERR,
        BIND_ERR,
        LISTEN_ERR
    };
    static const uint16_t gport = 8080;
    static const int gbacklog = 5;

    using func_t = std::function<bool (const HttpRequest &, HttpResponse &)>;
    class HttpServer {
    public:
    HttpServer(func_t func, const uint16_t &port = gport) : _func(func), _listensock(-1), _port(port) {}
    void initServer() {

        _listensock = socket(AF_INET,SOCK_STREAM,0);
        if (_listensock < 0) {
            exit(SOCKET_ERR);
        }
        struct sockaddr_in local;
        memset(local,0,sizeof(local));
        local.sin_family = AF_INET;
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_port = _port;
        bind(_listensock,(struct sockaddr*)&local,sizeof(local) < 0) {
            exit(BIND_ERR);
        }
    }
    ~HttpServer() {}
    private:
        uint16_t _port;
        int _listensock;
        func_t _func;

    };

} // namespace server
