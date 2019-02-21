#include "stdafx.h"
#include <stdio.h>
#include "BaseThread.h"
#include <thread>
//构造函数，通过参数列表方式给线程号初始化为0
BaseThread::BaseThread() //:tid(0)
{

}

//虚析构函数
BaseThread::~BaseThread()
{
	if (!this->isInterrupted())
	{
		this->interrupt();
	}

	if (this->_thread.joinable()) {
		this->_thread.join();
	}
	printf("~ThreadBase\n");
}


/****************************************************************
@功能：启动线程
@参数：无
@返回值: 成功：0，失败：-1
******************************************************************/
int BaseThread::start()
{
/*	int ret = 0;

	size_t nsize = 1024 * 20; //20k
	ret = pthread_attr_init(&t_attr); //初始化线程属性
	if (ret != 0)
	{
		perror("pthread_attr_init");
		return -1;
	}

	//设置线程的堆栈大小
	ret = pthread_attr_setstacksize(&t_attr, nsize);
	if (ret != 0)
	{
		perror("pthread_attr_getstacksize");
		return -1;
	}

	//创建线程
	return pthread_create(&tid, &t_attr, work, this);*/
	std::thread _thr(std::bind(&BaseThread::routine,this));
	this->_thread = std::move(_thr);
	//return CreateThread()
	return 0;
}

/****************************************************************
@功能：线程的运行函数，此处为空，由派生类实现
@参数：无
@返回值: 无
******************************************************************/
void BaseThread::routine()
{
	printf("BaseThread routine");
}

/****************************************************************
@功能：获取当前线程的线程号
@参数：无
@返回值: 线程号
******************************************************************/
/*pthread_t BaseThread::self()
{
	if (!tid)
	{
		tid = pthread_self(); //获取线程号
	}

	return tid;
}
*/
/****************************************************************
@功能：比较线程号是否相等
@参数：待比较的线程号
@返回值: 相等：0，不相等：-1
******************************************************************/
/*int BaseThread::equal(pthread_t t)
{
	int ret = 0;
	ret = pthread_equal(tid, t);
	return (ret) ? 0 : -1;
}
*/
/****************************************************************
@功能：分离线程，待线程结束时让系统自动回收其资源
@参数：无
@返回值: 成功：0，失败：-1
******************************************************************/
/*int BaseThread::detach()
{
	return pthread_detach(tid);
}*/

/****************************************************************
@功能：连接线程，等待指定的线程结束，并回收其资源
@参数：无
@返回值: 成功：0，失败：-1
******************************************************************/
/*int BaseThread::join(pthread_t t)
{
	return pthread_join(t, NULL);
}*/

/****************************************************************
@功能：线程退出
@参数：无
@返回值: 成功：0，失败：-1
******************************************************************/
/*int BaseThread::exit()
{
	int ret = 0;
	pthread_exit(NULL);
	return ret;
}*/

/****************************************************************
@功能：取消线程
@参数：线程号
@返回值: 成功：0，失败：-1
******************************************************************/
/*int BaseThread::cancel(pthread_t t)
{
	return  pthread_cancel(t);
}*/

/****************************************************************
@功能：销毁线程
@参数：线程号
@返回值: 成功：0，失败：-1
******************************************************************/
/*int BaseThread::destroy()
{
	return cancel(tid);
}*/

/****************************************************************
@功能：线程清理函数
@参数：线程句柄
@返回值: 无
******************************************************************/
/*void BaseThread::cleaner(void *pHandle)
{
	ThreadBase *p = (ThreadBase *)pHandle;
	delete p;
	p = NULL;
	printf("after clean\n");
}*/

/****************************************************************
@功能：线程回调函数
@参数：线程句柄
@返回值: 无
******************************************************************/
/*void *BaseThread::work(void *pHandle)
{
	ThreadBase* pThread = (ThreadBase *)pHandle;

	//注册线程处理函数
	pthread_cleanup_push(cleaner, pHandle);

	pThread->routine(); //线程运行函数

						//线程资源释放，参数为非0
	pthread_cleanup_pop(1);

	return NULL;
}*/
std::thread::id BaseThread::getId()
{
	return this->_thread.get_id();
}

void BaseThread::interrupt()
{
	this->isInterript = true;
}

bool BaseThread::isInterrupted()
{
	return this->isInterript;
}

void BaseThread::join()
{
	this->_thread.join();
}

