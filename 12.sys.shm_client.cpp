#include"comm.hpp"
#include<unistd.h>

int main() {
    key_t k = getKey(); // 创造内核中的唯一标识值
    cout << "key : " << k << endl;
    int shmid = getShm(k);  // 返回值：成功返回共享内存标识符shmid；错误返回-1

    cout << "shmid : " << shmid << endl;

    char *start = (char *)attachShm(shmid); // 建立连接
    
    const char* message = "hello server, 我是另一个进程，正在和你通信";

    cout << "attach success , address start" << endl;

    pid_t id = getpid();
    
    int cnt = 0;

    while (true) {
        sleep(6);
        snprintf(start,MAX_SIZE,"%s[pid : %d][消息编号 : %d]",message,id,cnt ++);
    }
    detachShm(start);
    return 0;
}
