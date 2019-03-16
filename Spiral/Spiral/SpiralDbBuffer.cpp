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

int SpiralDbBuffer::updateDbBuffer(char * buffer)
{
	//流转化为角色数据（结构体）
	//角色数据转化为mysql保存
	return 0;
}

SpiralDbBuffer* SpiralDbBuffer::getInstance()
{
	return INSTANCE;
}