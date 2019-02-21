#include "stdafx.h"
#include "SpiralDbBuffer.h"

//饿汉模式构造单例
SpiralDbBuffer* SpiralDbBuffer::INSTANCE = new SpiralDbBuffer();
SpiralDbBuffer::SpiralDbBuffer()
{
}


SpiralDbBuffer::~SpiralDbBuffer()
{
}

int SpiralDbBuffer::updateDbBuffer()
{
	return 0;
}

SpiralDbBuffer* SpiralDbBuffer::getInstance()
{
	return INSTANCE;
}