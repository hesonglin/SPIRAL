#pragma once
/*������������DBServer���ڴ滺�棬����������Spiral_Server�����紫��*/
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

