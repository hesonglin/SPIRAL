#pragma once

#include "SpiralBase/BaseThread.h"
#include <event2/util.h>
#include <list>
#include <map>
struct connInfo
{
	int threadIndex;//分配的线程序号
	//long long int  fd;//分配的socketId
	struct bufferevent * bev;
};
//子线程，用于处理IO事件
class SpiralNetThread :public BaseThread
{
public:
	SpiralNetThread(int id);
	~SpiralNetThread();
	void routine();
	struct event_base *base;
	struct bufferevent *bev;
	std::list<bufferevent *>  bev_list_;//记录连接成功的buffer
	std::map<long long int, connInfo>  client_list_;//记录连接的客户端
	void clientConnected(int threadIndex, evutil_socket_t fd,bufferevent *bev);
	//void clientDisconnected( evutil_socket_t fd); 
	void clientDisconnected(evutil_socket_t fd);
private:
	int index;//记录创建线程池的时候，该线程的编号（不同于线程ID）
};

