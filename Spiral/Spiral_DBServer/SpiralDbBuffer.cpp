#include "stdafx.h"
#include "SpiralDbBuffer.h"

//����ģʽ���쵥��
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