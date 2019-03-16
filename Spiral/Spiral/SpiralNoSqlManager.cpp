#include "stdafx.h"
#include "SpiralNoSqlManager.h"
#include <iostream>
#pragma comment(lib, "hiredis.lib")
//饿汉模式构造单例
SpiralNoSqlManager* SpiralNoSqlManager::INSTANCE = new SpiralNoSqlManager();

SpiralNoSqlManager::SpiralNoSqlManager()
{
}


SpiralNoSqlManager::~SpiralNoSqlManager()
{
}

SpiralNoSqlManager* SpiralNoSqlManager::getInstance()
{
	return INSTANCE;
}

void SpiralNoSqlManager::doTest()
{
	//redis 默认监听端口为6387，可以在配置文件中修改
	redisConn = redisConnect("127.0.0.1",6379);
	if (redisConn->err)
	{
		printf("Connect to redisServer faile:%s\n", redisConn->errstr);
		redisFree(redisConn);
		return;
	}
	printf("Connect to redisServer Success\n");

	const char* command1 = "set stest1 value1";
	redisReply* r = (redisReply*)redisCommand(redisConn, command1);

	if (NULL == r)
	{
		printf("Execut command1 failure\n");
		redisFree(redisConn);
		return;
	}
	if (!(r->type == REDIS_REPLY_STATUS && (strcmp(r->str, "OK") == 0 || strcmp(r->str, "ok") == 0)))
	{
		printf("Failed to execute command[%s]\n", command1);
		freeReplyObject(r);
		redisFree(redisConn);
		return;
	}
	freeReplyObject(r);
	printf("Succeed to execute command[%s]\n", command1);

	const char* command2 = "strlen stest1";
	r = (redisReply*)redisCommand(redisConn, command2);
	if (r->type != REDIS_REPLY_INTEGER)
	{
		printf("Failed to execute command[%s]\n", command2);
		freeReplyObject(r);
		redisFree(redisConn);
		return;
	}
	int length = r->integer;
	freeReplyObject(r);
	printf("The length of 'stest1' is %d.\n", length);
	printf("Succeed to execute command[%s]\n", command2);


	const char* command3 = "get stest1";
	r = (redisReply*)redisCommand(redisConn, command3);
	if (r->type != REDIS_REPLY_STRING)
	{
		printf("Failed to execute command[%s]\n", command3);
		freeReplyObject(r);
		redisFree(redisConn);
		return;
	}
	printf("The value of 'stest1' is %s\n", r->str);
	freeReplyObject(r);
	printf("Succeed to execute command[%s]\n", command3);

	const char* command4 = "get stest2";
	r = (redisReply*)redisCommand(redisConn, command4);
	if (r->type != REDIS_REPLY_NIL)
	{
		printf("Failed to execute command[%s]\n", command4);
		freeReplyObject(r);
		redisFree(redisConn);
		return;
	}
	freeReplyObject(r);
	printf("Succeed to execute command[%s]\n", command4);


	redisFree(redisConn);

}

int SpiralNoSqlManager::initRedisConn()
{
	//redis 默认监听端口为6387，可以在配置文件中修改
	redisConn = redisConnect("127.0.0.1", 6379);
	if (redisConn->err)
	{
		printf("Connect to redisServer faile:%s\n", redisConn->errstr);
		redisFree(redisConn);
		return -1;
	}
	printf("Connect to redisServer Success\n");
//	setValue("test","redis");
	char * str = getValue("test");
	//printf("redis test str:%s\n", str);
	std::cout << "redis test str:" << str << std::endl;
	return 0;
}

int SpiralNoSqlManager::setValue(const char* keyValue, const char* value)
{
	char command[100] = "set ";// +keyValue + value;
	strcat(command,keyValue);
	strcat(command, " ");
	strcat(command, value);
	if (!redisConn) { printf("redisConn is null\n"); }
	redisReply* r = (redisReply*)redisCommand(redisConn, command);

	if (NULL == r)
	{
		printf("Execut command failure\n");
		redisFree(redisConn);
		return -1;
	}
	if (!(r->type == REDIS_REPLY_STATUS && (strcmp(r->str, "OK") == 0 || strcmp(r->str, "ok") == 0)))
	{
		printf("Failed to execute command[%s]\n", command);
		freeReplyObject(r);
		redisFree(redisConn);
		return -2;
	}
	freeReplyObject(r);
	printf("Succeed to execute command[%s]\n", command);
	return 0;
}

char* SpiralNoSqlManager::getValue(const char* keyValue)
{
	char command[100] = "get ";// +keyValue + value;
	strcat(command, keyValue);

	redisReply* r = (redisReply*)redisCommand(redisConn, command);

	r = (redisReply*)redisCommand(redisConn, command);
	if (r->type != REDIS_REPLY_STRING)
	{
		printf("Failed to execute command[%s]\n", command);
		freeReplyObject(r);
		redisFree(redisConn);
		return 0;
	}
	//printf("The value of '%s' is %s\n", keyValue, r->str);
	char* buffer = (char*)malloc(sizeof(char)*strlen(r->str));
	//memset(res,0,sizeof(char)*strlen(r->str));
	memcpy(buffer, r->str,sizeof(char)*strlen(r->str));
	freeReplyObject(r);
	//printf("Succeed to execute command[%s]\n", command);
	return buffer;
}

bool SpiralNoSqlManager::isKeyExist(const char* keyValue)
{
	return false;
}