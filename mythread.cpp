#include <iostream>
#include <cstdio>
#include <cassert>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int g_val = 0;
string fun() {
    return "我是一个独立的方法！";
}
void *thread_routine(void *args) {
    const char* name = (const char *)args;
    while (true) {
        fun();
        cout << "我是新线程, 我正在运行! name: " << name << " : "<< fun()  << " : " << g_val++ << " &g_val : " << &g_val << endl;
        sleep(1);
    }
}
int main() {
    pthread_t tid;
    int n = pthread_create(&tid,nullptr,thread_routine,(void*)"thread one");
    assert(n == 0);
    (void)n;
    
    while (true) {
        char tidbuffer[64];
        snprintf(tidbuffer,sizeof(tidbuffer),"0x%x",tid);
        cout << "我是主线程, 我正在运行!, 我创建出来的线程的tid： " << tidbuffer << " : " << g_val << " &g_val : " << &g_val << endl;
        sleep(1);
    }
    return 0;
}
