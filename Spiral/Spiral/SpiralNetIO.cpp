#include "stdafx.h"
#include "SpiralNetIO.h"


SpiralNetIO::SpiralNetIO()
{

}


SpiralNetIO::~SpiralNetIO()
{

}

bool SpiralNetIO::sendMsg(int clientId, const char * msg, int sz)
{
	SpiralNetManager* netManager = SpiralNetManager::getInstance();
	std::list<SpiralNetThread *>::iterator threadIt;
	std::map<long long int, connInfo>::iterator clientIt;
	for (threadIt = netManager->thread_list_.begin(); threadIt != netManager->thread_list_.end(); threadIt++)
	{
		SpiralNetThread * pThread = *threadIt;
		clientIt = pThread->client_list_.find(clientId);
		if(clientIt != pThread->client_list_.end())
		{
			//struct bufferevent * bev = &(*clientIt->second.bev);
			if (clientIt->second.bev)
			{
				bufferevent_write(clientIt->second.bev, msg, sz);
				return true;
			}
		}
	}
	printf("cannot find the client");
	return false;
}
bool SpiralNetIO::sendBroadcastMsg(const char* msg, int sz)
{
	SpiralNetManager* netManager = SpiralNetManager::getInstance();
	std::list<SpiralNetThread *>::iterator threadIt;
	//std::list<bufferevent *>::iterator bevIt;
	std::map<long long int, connInfo>::iterator clientIt;
	for (threadIt = netManager->thread_list_.begin(); threadIt != netManager->thread_list_.end(); threadIt++)
	{
		SpiralNetThread * pThread = *threadIt;
		for (clientIt = pThread->client_list_.begin(); clientIt != pThread->client_list_.end(); clientIt++)
		{
			if (clientIt->second.bev)
			{
				bufferevent_write(clientIt->second.bev, msg, sz);
			}
		}
		//pThread->start();
		//if (pThread->bev)
		//{
			//for (bevIt = pThread->bev_list_.begin(); bevIt != pThread->bev_list_.end(); bevIt++)
			//{
			//	bufferevent_write(*bevIt, msg, sz);
			//}
		//}
	}
	return true;
}