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

int SpiralDbBuffer::updateDbBuffer(char * buffer)
{
	//��ת��Ϊ��ɫ���ݣ��ṹ�壩
	//��ɫ����ת��Ϊmysql����
	return 0;
}

SpiralDbBuffer* SpiralDbBuffer::getInstance()
{
	return INSTANCE;
}