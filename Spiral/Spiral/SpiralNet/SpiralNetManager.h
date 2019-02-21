#pragma once

#include <thread>
#include "SpiralBase/BaseThread.h"
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <list>
#include <map>
#include "SpiralNetThread.h"
#include <string>
#pragma comment(lib, "libevent.lib")
#pragma comment(lib, "ws2_32.lib")
/*
	网络模块负责功能如下：
	1、监听客户端连接状态
	2、向客户端发送消息
	3、记录连接对象
*/

/*创建线程池的目的是单线程的net，如果玩家达到一定数量，响应会高于1s
导致玩家体验不足，性能不足。如果创建net多个线程，当某一个线程内的
玩家数量大于指定值，则开辟新的线程来处理信号，保证玩家操作能及时响应*/

class SpiralNetManager :public BaseThread
{
public:
	~SpiralNetManager();
	int netInit();//网络模块初始化，包括加载配置
	int sendMessage(int clientId, const char * reply_msg);//向客户端发送消息
	static int sendBroadcastMsg(const char* msg, size_t sz);//广播
	int BUFFER_SIZE;
	int num;
	void routine(); //线程的运行函数，由派生类实现
	static SpiralNetManager* getInstance();
	struct sockaddr_in sin;
	struct evconnlistener *listener;
	struct event_base *base;
	struct bufferevent *bev;
	//BufferNetThread netList[5];
	std::list<SpiralNetThread *>  thread_list_;
	//std::map<evutil_socket_t,bufferevent *>  client_list_;
private:

	static void listener_cb(struct evconnlistener *, evutil_socket_t,struct sockaddr *, int socklen, void *);
	static void conn_writecb(struct bufferevent *, void *);
	static void conn_readcb(struct bufferevent *, void *);
	static void conn_eventcb(struct bufferevent *, short, void *);
	static void accept_error_cb(struct evconnlistener *listener,void *ptr);
	static void delay(int ms);
	static std::list<bufferevent *>  net_list_;
	//http://www.cppblog.com/sailing/articles/161659.html
	static SpiralNetManager* INSTANCE;
	int netId;
	SpiralNetManager();
};

