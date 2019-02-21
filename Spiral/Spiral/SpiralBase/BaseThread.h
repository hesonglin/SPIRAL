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
//�̻߳���
class BaseThread
{
public:
	BaseThread(); //���캯��
	virtual ~BaseThread(); //����������

	int start(); //�����߳�
	virtual void routine(); //�̵߳����к�������������ʵ��
	std::thread::id getId();
	void interrupt();
	bool isInterrupted();
	void join();
/*	virtual pthread_t self(); //��ȡ��ǰ�̵߳��̺߳�
	virtual int equal(pthread_t t); //�Ƚ��̺߳��Ƿ����
	virtual int detach(); //�����߳�
	virtual int join(pthread_t t); //�����߳�
	virtual int exit(); //�߳��˳�
	virtual int cancel(pthread_t t); //ȡ���߳�
	virtual int destroy(); //�����߳�
*/
private:
//	static void cleaner(void *pHandle); //�߳�������
//	static void *work(void *pHandle); //�̻߳ص�����

private:
//	pthread_attr_t  t_attr; //�߳�����
//	pthread_t tid; //�̺߳�
	std::thread _thread;
	std::atomic<bool> isInterript = false;
};

#endif

