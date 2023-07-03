#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <functional>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <unordered_map>
#include "Protocol.hpp"

namespace server {
    enum {
        USAGE_ERR = 1,
        SOCKET_ERR,
        BIND_ERR,
        LISTEN_ERR
    };
    static const uint16_t gport = 8080;
    static const int gbacklog = 5;

    using func_t = std::function(bool<const HttpRequest &,Httpresponse& >)

    
    class HttpServer {
        HttpServer(func_t func,const uint16_t &port = gport) : _func(func),_listensock(-1),_port(port) {}
        void initServer() {
            _listensock = socket(AF_INET,SOCK_STREAM,0);
            if (_listensock < 0) {
                exie(LISTEN_ERR);
            }
            struct sockaddr_in local;
            local.sin_addr.s_addr = INADDR_ANY;
            local.sin_port = _port;
            local.sin_family = AF_INET;

            if (bind(_listensock,(struct sockaddr*)&local,sizeof(local) < 0)) {
                exit(BIND_ERR);
            } 

            if (listen(_listensock,gbacklog) < 0) {
                exit(LISTEN_ERR);
            }
        }
        void HandlerHttp(int sock) {
            // 1.读到完整的请求
            // 2.反序列化
            // 3.处理  httprequst, httpresponse, _func(req, resp)
            // 4.resp反序列化
            // 5.send
            char buffer[4096];
            HttpRequest req;
            HttpResponse reps;
            size_t n = recv(sock,buffer,sizeof(buffer) - 1);
            if (n > 0) {
                buffer[n] = 0;
                req.inbuffer = buffer;
                req.parse();
                _func(req,reps);
                send(sock,req.outbuffer.c_str(),resp.outbuffer.size(),0);
            }
        }
        void start() {
             for (;;) {
                struct sockaddr_in peer;
                socklen_t len = sizepf(peer);
                int sock = accept(_listensock,(struct sockaddr_in*)&peer,len);
                if (sock < 0) {
                    continue;
                }
                pid_t id = fock();
                if (id == 0) {
                    close(_listensock);
                    if (fork() > 0) exit(0);
                    HandlerHttp(sock);
                    close(sock);
                    exit(0);
                }
                close(sock);
                waitpid(id,nullptr,0);
             }
        }
        ~HttpServer() {}
        private:
        int _listensock; // 不是用来进行数据通信的，它是用来监听链接到来，获取新链接的！
        uint16_t _port;
        func_t _func;
        // std::unordered_map<std::string, func_t> funcs;
    };
}
