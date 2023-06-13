.PHONY:all
all:mysignal1
mysignal1:mysignal1.cpp
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -f mysignal1
