#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
string changeId(const pthread_t &thread_id) {
    char tid[128];
    snprintf(tid,sizeof(tid),"0x%x",thread_id);
    return tid;
}

void *start_routine(void *args) {
   // pthread_detach(pthread_self());
    string threadname = static_cast<const char *>(args);
    int cnt = 5;
    while (cnt --) {
        
        cout <<threadname <<  "running..."<< changeId(pthread_self()) <<endl;
        sleep(1);
    }
}
int main() {
    pthread_t tid;
    pthread_create(&tid,nullptr,start_routine,(void*)"thread 1");
    cout << endl;
    pthread_detach(tid);
    cout << "main thread running... new thread id "<< changeId(tid) << endl;
    // 一个线程默认是joinable的，如果设置了分离状态，不能进行等待了
    int n = pthread_join(tid,nullptr);
    cout << "result" << n << ":" << strerror(n) << endl;
    return 0;
}
