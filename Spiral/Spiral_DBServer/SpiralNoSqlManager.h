#pragma once
//https://www.cnblogs.com/sixbeauty/p/3954199.html

//http://www.cnblogs.com/linjiqin/archive/2013/05/27/3101694.html
#include "hiredis.h"
#include <string>
class SpiralNoSqlManager
{
public:

	~SpiralNoSqlManager();
	static SpiralNoSqlManager* SpiralNoSqlManager::getInstance();
	void doTest();
	int initRedisConn();
	int setValue(const char* keyValue,const char* value);
	char* getValue(const char* keyValue);
	bool isKeyExist(const char* keyValue );
private:
	redisContext * redisConn;//NoSql conn
	static SpiralNoSqlManager* INSTANCE;
	SpiralNoSqlManager();
};

