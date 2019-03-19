#pragma once

#include "SpiralBase/BaseThread.h"
#include <event2/util.h>
#include <list>
#include <map>
struct connInfo
{
	int threadIndex;//������߳����
	//long long int  fd;//�����socketId
	struct bufferevent * bev;
};
//���̣߳����ڴ���IO�¼�
class SpiralNetThread :public BaseThread
{
public:
	SpiralNetThread(int id);
	~SpiralNetThread();
	void routine();
	struct event_base *base;
	struct bufferevent *bev;
	std::list<bufferevent *>  bev_list_;//��¼���ӳɹ���buffer
	std::map<long long int, connInfo>  client_list_;//��¼���ӵĿͻ���
	void clientConnected(int threadIndex, evutil_socket_t fd,bufferevent *bev);
	//void clientDisconnected( evutil_socket_t fd); 
	void clientDisconnected(evutil_socket_t fd);
private:
	int index;//��¼�����̳߳ص�ʱ�򣬸��̵߳ı�ţ���ͬ���߳�ID��
};

