#pragma once
#include "my_global.h"//https://www.jb51.net/article/101187.htm
#include "mysql.h"
#include <iostream>

//https://blog.csdn.net/zxng_work/article/details/78926413#mysql-c-api%E7%A7%BB%E6%A4%8D
/*用于保存用户数据*/
class SpiralSqlManager
{
public:
	
	~SpiralSqlManager();
	static SpiralSqlManager* SpiralSqlManager::getInstance();
	void connectSql();

private:
	static SpiralSqlManager* INSTANCE;
	SpiralSqlManager();
};

