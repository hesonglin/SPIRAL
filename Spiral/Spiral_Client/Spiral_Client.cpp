// spiral1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
#include <time.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include "SpiralNetManager.h"

#pragma comment(lib, "libevent.lib")
#pragma comment(lib, "ws2_32.lib")

const int PORT = 2500;
const int BUFFER_SIZE = 1024;
int main()
{
	printf("client startup\n");

	SpiralNetManager * netManager = SpiralNetManager::getInstance();

	
	netManager->netInit();
	netManager->start();
	printf("开始连接服务端...\n");
	while (true)
	{
		//netManager->startUp();
		char msg[100] = "";
		std::cin >> msg;
		netManager->sendMessage(0,msg);
		//int i = 0;
		//i = i + 1;
	}
	
/*#ifdef WIN32
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif


	struct sockaddr_in srv;
	memset(&srv, 0, sizeof(srv));
	//srv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	srv.sin_addr.S_un.S_un_b.s_b1 = 127;
	srv.sin_addr.S_un.S_un_b.s_b2 = 0;
	srv.sin_addr.S_un.S_un_b.s_b3 = 0;
	srv.sin_addr.S_un.S_un_b.s_b4 = 1;
	//inet_aton("", );
	//inet_pton();
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);

	struct event_base *base = event_base_new();
	if (!base)
	{
		printf("Could not initialize libevent\n");
		return 1;
	}

	struct bufferevent* bev = bufferevent_socket_new(base, -1,
		BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, NULL);
	int flag = bufferevent_socket_connect(bev, (struct sockaddr *)&srv, sizeof(srv));
	bufferevent_enable(bev, EV_READ | EV_WRITE);
	if (-1 == flag)
	{
		printf("Connect failed\n");
		return 1;
	}

	//event_base_dispatch(base);
	event_base_loop(base, EVLOOP_NONBLOCK);
	while (true)
	{
		event_base_loop(base, EVLOOP_NONBLOCK);
		char msg[100] = "";
		std::cin >> msg;
		bufferevent_write(bev, msg, strlen(msg));
		//scanf("%s", msg);
	}
	event_base_free(base);

	printf("done\n");*/
	return 0;
}


