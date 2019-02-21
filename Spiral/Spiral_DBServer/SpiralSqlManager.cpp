#include "stdafx.h"
#include "SpiralSqlManager.h"
#include "SpiralNoSqlManager.h"
#pragma comment(lib, "libmysql.lib")

SpiralSqlManager* SpiralSqlManager::INSTANCE = new SpiralSqlManager();

SpiralSqlManager::SpiralSqlManager()
{
}


SpiralSqlManager::~SpiralSqlManager()
{
}

SpiralSqlManager* SpiralSqlManager::getInstance()
{
	return INSTANCE;
}

void SpiralSqlManager::connectSql()
{
	MYSQL mysql;
	mysql_init(&mysql);
	auto res = mysql_real_connect(&mysql,"10.10.10.206","root","123456","actordb_yjtz",3306,NULL,0);
	char* sql = "select * from actors;";
	mysql_query(&mysql,sql);
	MYSQL_RES *result = mysql_store_result(&mysql);
	if (!result) { printf("result is null\n"); return; }

	int num_fields = mysql_num_fields(result);
	if (0 == num_fields) { printf("num_fields is 0 \n"); return;
	}

	MYSQL_FIELD *fields = mysql_fetch_fields(result);
	if (!fields) { printf("fields fetch is error\n"); return;
	}

	SpiralNoSqlManager * nomysql = SpiralNoSqlManager::getInstance();
	for (int i = 0; i < num_fields; i++)
	{
		std::cout << "field " << i << " name is " << fields[i].name << std::endl;
		nomysql->setValue(fields[i].name, fields[i].db);
	}

	for (int i = 0; i < num_fields; i++)
	{
		std::cout << "key: " << fields[i].name << " value: " << nomysql->getValue(fields[i].name) << std::endl;
	}
}