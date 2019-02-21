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
	����ģ�鸺�������£�
	1�������ͻ�������״̬
	2����ͻ��˷�����Ϣ
	3����¼���Ӷ���
*/

/*�����̳߳ص�Ŀ���ǵ��̵߳�net�������Ҵﵽһ����������Ӧ�����1s
����������鲻�㣬���ܲ��㡣�������net����̣߳���ĳһ���߳��ڵ�
�����������ָ��ֵ���򿪱��µ��߳��������źţ���֤��Ҳ����ܼ�ʱ��Ӧ*/

class SpiralNetManager :public BaseThread
{
public:
	~SpiralNetManager();
	int netInit();//����ģ���ʼ����������������
	int sendMessage(int clientId, const char * reply_msg);//��ͻ��˷�����Ϣ
	static int sendBroadcastMsg(const char* msg, size_t sz);//�㲥
	int BUFFER_SIZE;
	int num;
	void routine(); //�̵߳����к�������������ʵ��
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

