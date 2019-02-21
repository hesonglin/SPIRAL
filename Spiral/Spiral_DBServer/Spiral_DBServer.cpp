// Spiral_DBServer.cpp : 定义控制台应用程序的入口点。
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
#include "SpiralSqlManager.h"
#include "SpiralNoSqlManager.h"
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
	SpiralSqlManager * mysql = SpiralSqlManager::getInstance();
	SpiralNoSqlManager * nomysql = SpiralNoSqlManager::getInstance();
	nomysql->initRedisConn();
	mysql->connectSql();
	nomysql->doTest();
	printf("开始连接服务端...\n");
	while (true)
	{
		//netManager->startUp();
	//	char msg[100] = "";
	//	std::cin >> msg;
	//	netManager->sendMessage(0, msg);
		int i = 0;
		i = i + 1;
		sleep(1000);
	}
	return 0;
}
