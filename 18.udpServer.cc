#include "udpServer.hpp"
#include <memory>
#include <fstream>
#include <unordered_map>

using namespace std;
using namespace Server;
const std::string dictTxt = "./dict.txt";
static void Usage(string proc) {
    cout << "\nUsage:\n\t" << proc << " local_port\n\n";
}
unordered_map<string,string> dict;
static bool cutString(const string&line,string *s1,string *s2,const string &sep) {
    //string sep = ":";
    auto pos = line.find(sep);
    if (pos == string::npos) {
        return false;
    }
    *s1 = line.substr(0,pos);
    *s2 = line.substr(pos + sep.size());
    return true;

}
static void initDict() {
    ifstream in(dictTxt,ios::binary);
    if (!in.is_open()) {
        std::cerr << "open file" << dictTxt << "error " << endl;
        exit(OPEN_ERR);
    }
    string line;
    string key,value;
    while (getline(in,line)) {
        // cout << line << endl;
        if (cutString(line,&key,&value,":")) {
            dict.insert(make_pair(key,value));
        }
    }
    in.close();
}
static void debugPrint() {
    for (auto &dt : dict) {
        cout << dt.first << "#" << dt.second << endl;
    }
}
void handlerMessage(string clientip, uint16_t clientport, string message)
{
    //就可以对message进行特定的业务处理，而不关心message怎么来的 ---- server通信和业务逻 辑解耦！


}

int main(int argc,char *argv[]) {
    if (argc != 2) {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }
    uint16_t port = atoi(argv[1]);
    initDict();
    debugPrint();
    // std::unique_ptr<udpServer> usvr(new udpServer(handlerMessage, port));

    // usvr->initServer();
    // usvr->start();

    return 0;
}
