#include "stdafx.h"
#include <stdio.h>
#include "BaseThread.h"
#include <thread>
//���캯����ͨ�������б�ʽ���̺߳ų�ʼ��Ϊ0
BaseThread::BaseThread() //:tid(0)
{

}

//����������
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
@���ܣ������߳�
@��������
@����ֵ: �ɹ���0��ʧ�ܣ�-1
******************************************************************/
int BaseThread::start()
{
/*	int ret = 0;

	size_t nsize = 1024 * 20; //20k
	ret = pthread_attr_init(&t_attr); //��ʼ���߳�����
	if (ret != 0)
	{
		perror("pthread_attr_init");
		return -1;
	}

	//�����̵߳Ķ�ջ��С
	ret = pthread_attr_setstacksize(&t_attr, nsize);
	if (ret != 0)
	{
		perror("pthread_attr_getstacksize");
		return -1;
	}

	//�����߳�
	return pthread_create(&tid, &t_attr, work, this);*/
	std::thread _thr(std::bind(&BaseThread::routine,this));
	this->_thread = std::move(_thr);
	//return CreateThread()
	return 0;
}

/****************************************************************
@���ܣ��̵߳����к������˴�Ϊ�գ���������ʵ��
@��������
@����ֵ: ��
******************************************************************/
void BaseThread::routine()
{
	printf("BaseThread routine");
}

/****************************************************************
@���ܣ���ȡ��ǰ�̵߳��̺߳�
@��������
@����ֵ: �̺߳�
******************************************************************/
/*pthread_t BaseThread::self()
{
	if (!tid)
	{
		tid = pthread_self(); //��ȡ�̺߳�
	}

	return tid;
}
*/
/****************************************************************
@���ܣ��Ƚ��̺߳��Ƿ����
@���������Ƚϵ��̺߳�
@����ֵ: ��ȣ�0������ȣ�-1
******************************************************************/
/*int BaseThread::equal(pthread_t t)
{
	int ret = 0;
	ret = pthread_equal(tid, t);
	return (ret) ? 0 : -1;
}
*/
/****************************************************************
@���ܣ������̣߳����߳̽���ʱ��ϵͳ�Զ���������Դ
@��������
@����ֵ: �ɹ���0��ʧ�ܣ�-1
******************************************************************/
/*int BaseThread::detach()
{
	return pthread_detach(tid);
}*/

/****************************************************************
@���ܣ������̣߳��ȴ�ָ�����߳̽���������������Դ
@��������
@����ֵ: �ɹ���0��ʧ�ܣ�-1
******************************************************************/
/*int BaseThread::join(pthread_t t)
{
	return pthread_join(t, NULL);
}*/

/****************************************************************
@���ܣ��߳��˳�
@��������
@����ֵ: �ɹ���0��ʧ�ܣ�-1
******************************************************************/
/*int BaseThread::exit()
{
	int ret = 0;
	pthread_exit(NULL);
	return ret;
}*/

/****************************************************************
@���ܣ�ȡ���߳�
@�������̺߳�
@����ֵ: �ɹ���0��ʧ�ܣ�-1
******************************************************************/
/*int BaseThread::cancel(pthread_t t)
{
	return  pthread_cancel(t);
}*/

/****************************************************************
@���ܣ������߳�
@�������̺߳�
@����ֵ: �ɹ���0��ʧ�ܣ�-1
******************************************************************/
/*int BaseThread::destroy()
{
	return cancel(tid);
}*/

/****************************************************************
@���ܣ��߳�������
@�������߳̾��
@����ֵ: ��
******************************************************************/
/*void BaseThread::cleaner(void *pHandle)
{
	ThreadBase *p = (ThreadBase *)pHandle;
	delete p;
	p = NULL;
	printf("after clean\n");
}*/

/****************************************************************
@���ܣ��̻߳ص�����
@�������߳̾��
@����ֵ: ��
******************************************************************/
/*void *BaseThread::work(void *pHandle)
{
	ThreadBase* pThread = (ThreadBase *)pHandle;

	//ע���̴߳�����
	pthread_cleanup_push(cleaner, pHandle);

	pThread->routine(); //�߳����к���

						//�߳���Դ�ͷţ�����Ϊ��0
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

