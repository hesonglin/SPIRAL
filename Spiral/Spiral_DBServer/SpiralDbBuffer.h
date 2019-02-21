#pragma once
/*该类用于整个DBServer的内存缓存，内容来自于Spiral_Server的网络传输*/
class SpiralDbBuffer
{
public:
	SpiralDbBuffer();
	~SpiralDbBuffer();

	int updateDbBuffer();
};

