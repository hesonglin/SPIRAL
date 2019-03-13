#pragma once
#include "SystemInfo.pb.h"
class SystemProtoInfo
{
public:
	SystemProtoInfo();
	~SystemProtoInfo();
	void writeName(const char* name);
	void writeId(const int id);
	void readName();
	void readId();
	void test();
private:
	systemInfo::system *data;
};

