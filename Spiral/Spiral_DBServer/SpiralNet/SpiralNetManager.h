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
	����ģ�鸺�������£�
	1�������ͻ�������״̬
	2����ͻ��˷�����Ϣ
	3����¼���Ӷ���
*/
class SpiralNetManager :public BaseThread
{
public:
	//typedef BaseThread Inherited;
	~SpiralNetManager();
	int netInit();//����ģ���ʼ����������������
	//int startUp();//��������ģ�飬������������
	int sendMessage(int clientId, const char * reply_msg);//��ͻ��˷�����Ϣ
	static int sendBroadcastMsg(const char* msg, int sz);//�㲥
	int num;
	void routine(); //�̵߳����к�������������ʵ��
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

