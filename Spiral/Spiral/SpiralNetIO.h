#pragma once
#include "SpiralNetManager.h"

class SpiralNetIO
{
public:
	SpiralNetIO();
	~SpiralNetIO();
	bool sendMsg(int clientId, const char * msg, int sz);
	bool sendBroadcastMsg(const char* msg, int sz);
};

