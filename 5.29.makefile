mythread2:mythread2.cpp
	g++ -o $@ $^ -std=c++11 -lpthread
.PHONY:clean
clean:
	rm -f mythread2
