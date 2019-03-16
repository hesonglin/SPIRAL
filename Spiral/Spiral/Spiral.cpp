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

#include "SystemProtoInfo.h"
#include "SpiralSqlManager.h"
#include "SpiralNoSqlManager.h"

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

	printf("开启脚本系统...\n");
	LuaScript *luaScript = LuaScript::getInstance();
	luaScript->loadFunctionConfig();
	luaScript->startUpLuaScript();

	printf("protobuf3.1 测试\n");
	SystemProtoInfo * protoInfo = new SystemProtoInfo();
	protoInfo->writeName("hsl");
	protoInfo->writeId(517);
	//protoInfo->test();

	printf("测试数据库模块\n");
	SpiralSqlManager * mysql = SpiralSqlManager::getInstance();
	SpiralNoSqlManager * nomysql = SpiralNoSqlManager::getInstance();
	nomysql->initRedisConn();
	mysql->connectSql();

	while (true)
	{
		char msg[100] = "";
		int clientId = 0;
		printf("请输入消息（rsf为脚本热更）:\n");
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
			printf("请输入客户端ID:\n");
			std::cin >> clientId;
			netStream.sendBroadcastMsg(msg, strlen(msg));
			//printf("\n");
			netStream.sendMsg(clientId, msg, strlen(msg));
		}
		//scanf("%s", msg);
		//netManager->sendBroadcastMsg(msg,strlen(msg));


		int i = 0;
		i = i + 1;
	}
	system("pause");
}
