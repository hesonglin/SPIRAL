#pragma once
#ifndef __THREADBASE_H__
#define __THREADBASE_H__
#include "stdafx.h"
/*#ifdef WIN32
#include <pthread.h>
#endif*/
//https://blog.csdn.net/a499957739/article/details/81254730
#include <thread>
#include <atomic>
/*int run()
{
	return 0;
}*/
//线程基类
class BaseThread
{
public:
	BaseThread(); //构造函数
	virtual ~BaseThread(); //虚析构函数

	int start(); //启动线程
	virtual void routine(); //线程的运行函数，由派生类实现
	std::thread::id getId();
	void interrupt();
	bool isInterrupted();
	void join();
/*	virtual pthread_t self(); //获取当前线程的线程号
	virtual int equal(pthread_t t); //比较线程号是否相等
	virtual int detach(); //分离线程
	virtual int join(pthread_t t); //连接线程
	virtual int exit(); //线程退出
	virtual int cancel(pthread_t t); //取消线程
	virtual int destroy(); //销毁线程
*/
private:
//	static void cleaner(void *pHandle); //线程清理函数
//	static void *work(void *pHandle); //线程回调函数

private:
//	pthread_attr_t  t_attr; //线程属性
//	pthread_t tid; //线程号
	std::thread _thread;
	std::atomic<bool> isInterript = false;
};

#endif

