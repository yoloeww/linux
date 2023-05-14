/child->write, father->read                                                                                                                                                                                                                                                                                                                                                                                                                                                        
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
using namespace std;
class subEp {
public:
	subEp (string &name,pid_t subId,int writeFd) :
	_name(name),_subId(_subId),_writeFd(writeFd)
	{}
public:
	string _name;
	pid_t _subId;
	int _writeFd;

};
int main()
{
	// 先描述后组织
	vector<subEp> subs;
	int fd[2] = { 0 };
	if (pipe(fd) < 0){ //使用pipe创建匿名管道
		perror("pipe");
		return 1;
	}
	pid_t id = fork(); //使用fork创建子进程
	if (id == 0){
		//child
		close(fd[0]); //子进程关闭读端
		//子进程向管道写入数据
		const char* msg = "hello father, I am child...";
		int count = 10;
		while (count--){
			write(fd[1], msg, strlen(msg));
			sleep(1);
		}
		close(fd[1]); //子进程写入完毕，关闭文件
		exit(0);
	}
	//father
	close(fd[1]); //父进程关闭写端
	//父进程从管道读取数据
	char buff[64];
	while (1){
		ssize_t s = read(fd[0], buff, sizeof(buff));
		if (s > 0){
			buff[s] = '\0';
			printf("child send to father:%s\n", buff);
		}
		else if (s == 0){
			printf("read file end\n");
			break;
		}
		else{
			printf("read error\n");
			break;
		}
	}
	close(fd[0]); //父进程读取完毕，关闭文件
	waitpid(id, NULL, 0);
	return 0;
}
