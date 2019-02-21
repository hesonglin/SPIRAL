#pragma once
/*该类用于整个DBServer的内存缓存，内容来自于Spiral_Server的网络传输*/
#include "SpiralSqlManager.h"
class SpiralDbBuffer
{
public:
	
	~SpiralDbBuffer();
	static SpiralDbBuffer* SpiralDbBuffer::getInstance();
	int updateDbBuffer();
	static SpiralDbBuffer* INSTANCE;
private:
	SpiralDbBuffer();
};

