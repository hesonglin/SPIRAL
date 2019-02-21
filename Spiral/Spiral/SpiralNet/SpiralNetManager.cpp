#include "stdafx.h"
#include "SpiralNetManager.h"
#include <cstring>
int maxThreadNum = 5;

std::list<bufferevent *>  SpiralNetManager::net_list_;

//饿汉模式构造单例
SpiralNetManager* SpiralNetManager::INSTANCE = new SpiralNetManager();


SpiralNetManager::SpiralNetManager()
{
	//创建子线程
	for (int i = 0; i < maxThreadNum; i++)
	{
		thread_list_.push_back(new SpiralNetThread(i));
	}
	num = 20190215;
	netId = 0;
}

SpiralNetManager::~SpiralNetManager()
{
	event_base_loopexit(base, 0);
}

SpiralNetManager* SpiralNetManager::getInstance()
{
	return INSTANCE;
}

void SpiralNetManager::routine()
{
	//event_base_dispatch(base);
	while (true)
	{
		event_base_loop(base, EVLOOP_NONBLOCK);
		Sleep(1);
	}
	evconnlistener_free(listener);
	event_base_free(base);
}

int SpiralNetManager::netInit()//网络模块初始化，包括加载配置
{
#ifdef WIN32
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif

	BUFFER_SIZE = 1024;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(2500);

	base = event_base_new();
	if (!base)
	{
		printf("[error] initialize libevent failure!\n");
		return 1;
	}
	
	listener = evconnlistener_new_bind(base, listener_cb, (void *)&thread_list_,LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,(struct sockaddr*)&sin,sizeof(sin));

	if (!listener)
	{
		printf("[error] create listener failure\n");
		return 1;
	}

	//启动监听
	evconnlistener_enable(listener);

	evconnlistener_set_error_cb(listener, accept_error_cb); //接受错误反馈

	//启动子线程
	std::list<SpiralNetThread *>::iterator it;
	for (it = thread_list_.begin(); it != thread_list_.end(); it++)
	{
		SpiralNetThread * pThread = *it;
		pThread->start();
	}
	
	return 0;
}

int SpiralNetManager::sendMessage(int clientId,const char * reply_msg)//向客户端发送消息
{
	if(bev)
	{
		bufferevent_write(bev, reply_msg, strlen(reply_msg));
	}
	return 0;
}

int SpiralNetManager::sendBroadcastMsg(const char* msg, size_t sz)//广播
{
	std::list<bufferevent *>::iterator iter;
	for (iter = net_list_.begin(); iter != net_list_.end(); iter++)
	{
		bufferevent_write(*iter, msg, sz);
	}
	return 0;
}

void SpiralNetManager::listener_cb(struct evconnlistener *listener, evutil_socket_t fd,struct sockaddr *sa, int socklen, void *user_data)
{
	//listener 接受连接的连接监听器，sock 新接收的套接字，sa接受连接的地址，socklen sa的长度，user_data 调用evconnlistener_new()时用户提供的指针
	printf("Detect an connection\n");

	std::list<SpiralNetThread *> * thread_list = (std::list<SpiralNetThread *>*)user_data;

	int num = rand() % maxThreadNum;
	//获取随机线程

	std::list<SpiralNetThread *>::iterator it = thread_list->begin();
	for (int i = 0; i < num; i++) { it++; }
	SpiralNetThread * pThread = *it;
	if (!pThread->base)
	{
		pThread->base = event_base_new();
	}
	if (!pThread->base)
	{
		printf("[error] initialize libevent failure!\n");
		return;
	}
	//if (!pThread->bev)
	//{
	bufferevent* bev = bufferevent_socket_new(pThread->base, fd, BEV_OPT_CLOSE_ON_FREE);
	//}

	if (!bev)
	{
		printf("Could not create a bufferevent\n");
		event_base_loopbreak(pThread->base);
		return;
	}
	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb,(void*)pThread);
	bufferevent_enable(bev, EV_READ | EV_WRITE);
	//net_list_.push_back(bev);//添加进网络列表中
	//pThread->bev_list_.push_back(bev);
	pThread->clientConnected(num,fd,bev);
	//std::pair<std::map<evutil_socket_t, bufferevent *>::iterator, bool> Insert_Pair;
	//Insert_Pair = client_list_.insert(std::pair<evutil_socket_t, bufferevent *>(1, "student_one"));
	printf("connect socketId(clientId) is %d ", fd);
}

void SpiralNetManager::conn_writecb(struct bufferevent *bev, void *user_data)
{
	//    struct evbuffer *output = bufferevent_get_output(bev);
	//    if (evbuffer_get_length(output) == 0)
	//    {
	//        printf("Output evbuffer is flushed\n");
	//        bufferevent_free(bev);
	//    }
	//delay 1 second
   /*delay(1000);
	static int msg_num = 1;
	char reply_msg[1000] = { '\0' };
	char *str = "I receive a message from server ";
	memcpy(reply_msg, str, strlen(str));
	//sprintf(reply_msg + strlen(str), "%d", msg_num);
	bufferevent_write(bev, reply_msg, strlen(reply_msg));
	msg_num++;
	*/
}

void SpiralNetManager::conn_readcb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *input = bufferevent_get_input(bev);
	SpiralNetManager *net = (SpiralNetManager *)user_data;
	size_t sz = evbuffer_get_length(input);
	char msg[1024] = { '\0' };
	if (sz > 0)
	{
		
		bufferevent_read(bev, msg, sz);
		sendBroadcastMsg(msg, sz);
		printf("%s\n", msg);
	}
	printf("child pthread_self= %d\n", net->getId());
	std::thread::id;
	
}

void SpiralNetManager::conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	SpiralNetThread * pThread = (SpiralNetThread *)user_data;
	if (events & BEV_EVENT_EOF)
	{
		printf(" Server Connection closed\n");
		pThread->clientDisconnected(bev);
	}
	else if (events & BEV_EVENT_ERROR)
	{
		printf(" Server Connection error\n");
		pThread->clientDisconnected(bev);
	}
	else if (events & BEV_EVENT_READING)
	{
		printf(" Server Connection reading\n");
	}
	else if (events & BEV_EVENT_WRITING)
	{
		printf(" Server Connection writing\n");
	}
	else if (events & BEV_EVENT_TIMEOUT)
	{
		printf(" Server Connection timeout\n");
	}
	else if (events & BEV_EVENT_CONNECTED)
	{
		printf(" Server Connection connected\n");
	}

	bufferevent_free(bev);
	//net_list_.erase(bev);
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