#include "stdafx.h"
#include "SpiralNetManager.h"
#include <cstring>

struct bufferevent *SpiralNetManager::bev = 0;
std::list<bufferevent *>  SpiralNetManager::net_list_;
bool SpiralNetManager::isConnected = false;
//����ģʽ���쵥��
SpiralNetManager* SpiralNetManager::INSTANCE = new SpiralNetManager();
struct event_base *SpiralNetManager::base = 0;
SpiralNetManager::SpiralNetManager()
{
	num = 20190215;
	
}


SpiralNetManager::~SpiralNetManager()
{
}

SpiralNetManager* SpiralNetManager::getInstance()
{
	return INSTANCE;
}

void SpiralNetManager::routine()
{
	while (true)
	{
		if (!isConnected)
		{
			netInit();
			Sleep(1000);//ÿ��1���ӣ����һ���Ƿ����� 
		}
		int res = event_base_loop(base, EVLOOP_NONBLOCK);
		Sleep(1);
	}
	event_base_free(base);
}
int SpiralNetManager::netInit()//����ģ���ʼ����������������
{
#ifdef WIN32
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif
	struct sockaddr_in srv;
	memset(&srv, 0, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);

	srv.sin_addr.S_un.S_un_b.s_b1 = 127;
	srv.sin_addr.S_un.S_un_b.s_b2 = 0;
	srv.sin_addr.S_un.S_un_b.s_b3 = 0;
	srv.sin_addr.S_un.S_un_b.s_b4 = 1;

	base = event_base_new();
	if (!base)
	{
		printf("[error] initialize libevent failure!\n");
		return 1;
	}

	
	bev = bufferevent_socket_new(base, -1,BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, NULL);
	int flag = bufferevent_socket_connect(bev, (struct sockaddr *)&srv, sizeof(srv));
	bufferevent_enable(bev, EV_READ | EV_WRITE);
	if (-1 == flag)
	{
		printf("Connect failed\n");
		return 1;
	}
	return 0;
}

int SpiralNetManager::sendMessage(int clientId,const char * reply_msg)//��ͻ��˷�����Ϣ
{
	if(bev)
	{
		int res = bufferevent_write(bev, reply_msg, strlen(reply_msg));
		int i = 0;
	}
	return 0;
}

int SpiralNetManager::sendBroadcastMsg(const char* msg,int sz)//�㲥
{
	std::list<bufferevent *>::iterator iter;
	for (iter = net_list_.begin(); iter != net_list_.end(); iter++)
	{
		bufferevent_write(*iter, msg, sz);
	}
	return 0;
}

void SpiralNetManager::conn_writecb(struct bufferevent *bev, void *user_data)
{
	static int msg_num = 1;
	char reply_msg[1000] = { '\0' };
	char *str = "I receive a message from server ";
	memcpy(reply_msg, str, strlen(str));
	//sprintf(reply_msg + strlen(str), "%d", msg_num);
	//bufferevent_write(bev, reply_msg, strlen(reply_msg));
	msg_num++;
}

//����ģ����ܵ�����
void SpiralNetManager::conn_readcb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *input = bufferevent_get_input(bev);
	SpiralDbBuffer * dbBuffer = SpiralDbBuffer::getInstance();
	size_t sz = evbuffer_get_length(input);
	//char msg[1024] = { '\0' };
	char buffer[1024] = { '\0' };
	if (sz > 0)
	{
		
		bufferevent_read(bev, &buffer, sz);
		//sendBroadcastMsg(msg, sz);
		dbBuffer->updateDbBuffer(buffer);
		printf("%s\n", &buffer);
	}

	
}

void SpiralNetManager::conn_eventcb(struct bufferevent *bevv, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF)
	{
		isConnected = false;
		printf("Connection closed\n");
	}
	else if (events & BEV_EVENT_ERROR)
	{
		//printf("Got an error on the connection: %s\n", strerror(errno));
	}
	else if (events & BEV_EVENT_CONNECTED)
	{
		printf("Connect succeed\n");
		//�ͻ������ӳɹ��󣬸����������͵�һ����Ϣ
		char *reply_msg = "I receive a message from client \n";
		bufferevent_write(bevv, reply_msg, strlen(reply_msg));
		bev = bevv;
		bufferevent_write(bev, reply_msg, strlen(reply_msg));
		isConnected = true;
		return;
	}
	bufferevent_free(bev);
}

void SpiralNetManager::accept_error_cb(struct evconnlistener *listener, void *ptr)
{
	struct event_base * base = evconnlistener_get_base(listener);
	int err = EVUTIL_SOCKET_ERROR();
	fprintf(stderr, "got an error %d (%s) on the listener. shuttong down.\n", err, evutil_socket_error_to_string(err));
	event_base_loopexit(base,NULL);
}
void SpiralNetManager::delay(int ms)
{
	clock_t start = clock();
	while (clock() - start < ms);
}