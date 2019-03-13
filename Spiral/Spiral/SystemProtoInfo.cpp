#include "stdafx.h"
#include "SystemProtoInfo.h"
#include "iostream"
//#include "SystemInfo.pb.h"
//using namespace std;

SystemProtoInfo::SystemProtoInfo()
{
	data = new systemInfo::system();
}


SystemProtoInfo::~SystemProtoInfo()
{
}
void ListMsg(const systemInfo::system & sys)
{

}
void SystemProtoInfo::writeName(const char* name) {
	data->set_name(name);
	//data->SerializeToOstream
}
void SystemProtoInfo::writeId(const int id) {
	data->set_id(id);
}
void SystemProtoInfo::readName() {
	//printf( "[readName] %s \n" ,data->name());
	std::cout << "[readName] " << data->name() << std::endl;
}
void SystemProtoInfo::readId() {
	printf("[readId] %d \n", data->id());
}

void SystemProtoInfo::test() {
	readName();
	readId();
	std::string buff{};
	data->SerializeToString(&buff);
	//-----------½âÎö-------------

	systemInfo::system buffer{};

	if (!buffer.ParseFromString(buff))
	{
		printf("parse error\n");
	}
	//auto tempInfo = buffer.user_info();
	//printf("[buffer] name %s\n",buffer.name());
	std::cout << "[buffer] name " << buffer.name() << std::endl;
	printf("[buffer] id %d\n", buffer.id());
	//std::cout << "name:" << buffer.name() << std::endl;
	printf("------------²âÊÔ³É¹¦------------\n");
}

