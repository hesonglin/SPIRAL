#pragma once
/*mysql 与 redis 同步方案：
1、外部模块“查”数据时：
	1.1、先从redis中读取，如果命中，则返回数据。
	1.2、如果未命中，则到mysql中进行查找。如果命中，则返回结果，并且将值保存到redis。如果未命中，返回错误码
2、外部模块“增删改”数据时：
	2.1、更新缓存，调用mysql进行数据的“增删改”。并且查询redis中是否存在，若存在则删除，否则，不做处理。
   */
class SyncSqlAndNoSql
{
public:
	SyncSqlAndNoSql();
	~SyncSqlAndNoSql();
};

