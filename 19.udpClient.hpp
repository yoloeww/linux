#pragma once
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno>

using namespace std;

namespace Client {
using namespace std;

    class udpClient {
    public:
        udpClient(const string& ip,const uint16_t &port) : _serverip(ip), _serverport(port), _sockfd(-1), _quit(false) {

        }
        void initClient() {
            _sockfd = socket(AF_INET,SOCK_DGRAM,0);
            if (_sockfd == -1) {
                cerr << "socket error :" << errno << " : " << strerror(errno) << endl;
                exit(2);
            }
            cout << "socket success :" << _sockfd << endl;
        }
        static void* readMessage(void *args) {

        }
        void run() {
            pthread_create(&_reader,nullptr,readMessage,(void*)&_sockfd);

            struct sockaddr_in server;
            bzero(server,sizeof(server));
            server.sin_family = AF_INET;
            server.sin_port = htons(_serverport);
            server.sin_addr.s_addr = inet_addr(_serverid.c_str());

            string message;
            char cmdline[1024];

            while (!_quit) {
                fprintf(stderr,"Enter # ");
                fflush(stderr);
                fgets(cmdline,sizeof(cmdline),stdin);

                cmdline[strlen(cmdline) - 1] = 0;

                message = cmdline;

                sendto(_sockfd,message.c_str(),sizeof(message),0,(struct sockaddr *)&server,sizeof (server));
            } 
        }
        ~udpClient() {
        }
    private:
            string _serverid;
            uint16_t _server port;
            int _sockfd;
            bool _quit;
            phtread_t _reader;
    };
}
