#pragma once 

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#include "log.hpp"

namespace server {
    using namespace std;
     static const uint16_t gport = 8080;
    static const int gbacklog = 5;
    enum {
        USAGE_ERR = 1,
        SOCKET_ERR,
        BIND_ERR,
        LISTEN_ERR
    };
    class TcpServer {
    public:
        TcpServer(const uint16_t& port = gport) : _listensock(-1),_port(port) {

        }
        void initServer() {
            // 1. 创建socket文件套接字对象
            _listensock = socket(AF_INET,SOCK_STREAM,0);
            if (_listensock < 0) {
                logMessage(FATAL, "create socket error");
                exit(SOCKET_ERR);
            }
            logMessage(NORMAL, "create socket success: %d", _listensock);
            struct sockaddr_in local;
            memset(&local,0,sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(_port);
            local.sin_addr.s_addr = INADDR_ANY;
            // 2. bind绑定自己的网络信息
            if(bind(_listensock,(struct sockaddr*)& local,sizeof(local))) {
                logMessage(FATAL,"bind socket error");
                exit(BIND_ERR);
            }
            logMessage(NORMAL, "bind socket success");
            // 3.设置socket 为监听状态
            if (listen(_listensock,gbacklog) < 0) {
                logMessage(FATAL,"listen socket error");
                exit(LISTEN_ERR);
            }
            logMessage(NORMAL,"listen socket success");
        }
        void start() {
            for (;;) {
                struct sockaddr_in peer;
                socklen_t len = sizeof(peer);
                int sock = accept(_listensock,(struct sockaddr*)&peer,&len);
                if (sock < 0) {
                    logMessage(ERROR,"accept error,next");
                    continue;
                }
                loadTaskFunc(NORMAL,"accept a new link success");
                cout << "sock : " << sock << endl;
                serviceIO(sock);
                close(sock);
            }
        }
        ~TcpServer() {}
    private:
        int _listensock; // 不是用来进行数据通信的，它是用来监听链接到来，获取新链接的！
        uint16_t _port;
    };
}
