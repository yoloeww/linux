#include"comm.hpp"
#include<unistd.h>


int main() {
    key_t k = getKey(); // 创造内核中的唯一标识值
    cout << "key : " << k << endl;
    int shmid = getShm(k);  // 返回值：成功返回共享内存标识符shmid；错误返回-1

    cout << "shmid : " << shmid << endl;

    char *start = (char *)attachShm(shmid); // 建立连接

    printf("attach success, address start: %p\n", start);

    while (true) {
        cout << "client say :" << start << endl;
        struct shmid_ds ds;

        shmctl(shmid,IPC_STAT,&ds);
        printf("获取属性: size: %d, pid: %d, myself: %d, key: 0x%x",\
                ds.shm_segsz, ds.shm_cpid, getpid(), ds.shm_perm.__key);
        sleep(1);
    }
    detachShm(start);

    sleep(1);
    delShm(shmid);

    return 0;
    
}
