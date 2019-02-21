#pragma once

#include <thread>
#include "BaseThread.h"
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <list>
//#include "SpiralDbBuffer.h"
#include"SpiralDbBuffer.h"
#include <string>
#pragma comment(lib, "libevent.lib")
#pragma comment(lib, "ws2_32.lib")
/*
	网络模块负责功能如下：
	1、监听客户端连接状态
	2、向客户端发送消息
	3、记录连接对象
*/
class SpiralNetManager :public BaseThread
{
public:
	//typedef BaseThread Inherited;
	~SpiralNetManager();
	int netInit();//网络模块初始化，包括加载配置
	//int startUp();//启动网络模块，开启监听功能
	int sendMessage(int clientId, const char * reply_msg);//向客户端发送消息
	static int sendBroadcastMsg(const char* msg, int sz);//广播
	int num;
	void routine(); //线程的运行函数，由派生类实现
	const int PORT = 2500;
	const int BUFFER_SIZE = 1024;
	static SpiralNetManager* getInstance();
	//struct sockaddr_in srv;
private:
	struct sockaddr_in sin;
	struct evconnlistener *listener;
	static struct event_base *base ;
	static bool isConnected;
	static struct bufferevent *bev;

	static void conn_writecb(struct bufferevent *, void *);
	static void conn_readcb(struct bufferevent *, void *);
	static void conn_eventcb(struct bufferevent *, short, void *);
	static void accept_error_cb(struct evconnlistener *listener,void *ptr);
	static void delay(int ms);
	static std::list<bufferevent *>  net_list_;
	//static std::list<bufferevent *>::iterator iter;
	//http://www.cppblog.com/sailing/articles/161659.html
	static SpiralNetManager* INSTANCE;

	SpiralNetManager();
};

