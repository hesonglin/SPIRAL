// Spiral.cpp : 定义控制台应用程序的入口点。
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

#include "SpiralNet/SpiralNetManager.h"
#include "SpiralNetIO.h"
#include "LuaScript.h"

#pragma comment(lib, "libevent.lib")
#pragma comment(lib, "ws2_32.lib")

const int PORT = 2500;
const int BUFFER_SIZE = 1024;
int main(int argc, char **argv)
{
	printf("server startup \n");
	SpiralNetManager * netManager = SpiralNetManager::getInstance();
	SpiralNetIO netStream;
	printf("启动网络监听...\n");
	netManager->netInit();
	netManager->start();
	//netPool->start();
	printf("开启脚本系统...\n");
	//lua_State* L = luaL_newstate();
	LuaScript *luaScript = LuaScript::getInstance();
	luaScript->loadFunctionConfig();
	luaScript->startUpLuaScript();


	while (true)
	{
		/*netManager->startUp();*/
		char msg[100] = "";
		int clientId = 0;
		std::cin >> msg;
		//auto res = strcmp(msg, "rsf");
		if (strcmp(msg, "rsf") == 0)
		{
			printf("开始进行热更！请输入虚拟机编号...\n");
			int lvmId;
			std::cin >> lvmId;
			printf("输入编号为%d,开始热更！\n", lvmId);
			luaScript->reloadAllFunctionMode();
		}
		else
		{
			std::cin >> clientId;
			netStream.sendBroadcastMsg(msg, strlen(msg));
			netStream.sendMsg(clientId, msg, strlen(msg));
		}
		//scanf("%s", msg);
		//netManager->sendBroadcastMsg(msg,strlen(msg));


		int i = 0;
		i = i + 1;
	}
/*#ifdef WIN32
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	struct evconnlistener *listener;
	struct event_base *base = event_base_new();
	if (!base)
	{
		printf("Could not initialize libevent\n");
		return 1;
	}
	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&sin,
		sizeof(sin));

	if (!listener)
	{
		printf("Could not create a listener\n");
		return 1;
	}

	event_base_dispatch(base);
	evconnlistener_free(listener);
	event_base_free(base);

	printf("done\n");
	return 0;*/
	system("pause");
	//event_base_dump_events();
}
