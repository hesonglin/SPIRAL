// Spiral.cpp : �������̨Ӧ�ó������ڵ㡣
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
	printf("�����������...\n");
	netManager->netInit();
	netManager->start();

	printf("�����ű�ϵͳ...\n");
	LuaScript *luaScript = LuaScript::getInstance();
	luaScript->loadFunctionConfig();
	luaScript->startUpLuaScript();

	printf("protobuf3.1 ����\n");
	SystemProtoInfo * protoInfo = new SystemProtoInfo();
	protoInfo->writeName("hsl");
	protoInfo->writeId(517);
	//protoInfo->test();

	printf("�������ݿ�ģ��\n");
	SpiralSqlManager * mysql = SpiralSqlManager::getInstance();
	SpiralNoSqlManager * nomysql = SpiralNoSqlManager::getInstance();
	nomysql->initRedisConn();
	mysql->connectSql();

	while (true)
	{
		char msg[100] = "";
		int clientId = 0;
		printf("��������Ϣ��rsfΪ�ű��ȸ���:\n");
		std::cin >> msg;
		//auto res = strcmp(msg, "rsf");
		if (strcmp(msg, "rsf") == 0)
		{
			printf("��ʼ�����ȸ�����������������...\n");
			int lvmId;
			std::cin >> lvmId;
			printf("������Ϊ%d,��ʼ�ȸ���\n", lvmId);
			luaScript->reloadAllFunctionMode();
		}
		else
		{
			printf("������ͻ���ID:\n");
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
