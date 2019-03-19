#include "stdafx.h"
#include "SpiralNetThread.h"
#include "SpiralNetManager.h"

SpiralNetThread::SpiralNetThread(int index) :index(index)
{

}

SpiralNetThread::~SpiralNetThread()
{
	event_base_loopexit(base, 0);
}

void SpiralNetThread::routine()
{
	while (true)
	{
		if (!base) { Sleep(1000); continue; }//Ã¿¸ô1s,¼ì²âÒ»´Î
		event_base_loop(base, EVLOOP_NONBLOCK);
		Sleep(1);
	}
}
void SpiralNetThread::clientConnected(int threadIndex, evutil_socket_t fd, bufferevent *bev)
{
	std::pair<std::map<long long int, connInfo>::iterator, bool> Insert_Pair;
	//Insert_Pair = client_list_.insert(pair<evutil_socket_t, bufferevent *>(1, "student_one"));
	connInfo connBuffer;
	connBuffer.threadIndex = threadIndex;
	connBuffer.bev = bev;
	//bev_list_.push_back(bev);
	//connBuffer.fd = fd;
	//client_list_[connBuffer] = bev;
	Insert_Pair = client_list_.insert(std::pair<long long int, connInfo>((long long int)fd, connBuffer));
	if (Insert_Pair.second)
	{
		printf("client_list insert successfully");
	}
	else
	{
		printf("client_list insert failure");
	}
}
void SpiralNetThread::clientDisconnected(evutil_socket_t fd)
{
	client_list_.erase(fd);//É¾³ý
}