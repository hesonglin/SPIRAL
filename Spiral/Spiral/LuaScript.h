#pragma once
#include <map>
#include <list>
extern "C"
{
	#include "lua.h"  
	#include "lualib.h"  
	#include "lauxlib.h"  
	#include "luaconf.h"  
}
#pragma comment(lib, "lua5.1.4.lib")
#pragma comment(lib, "tolua++.lib")
#include "tolua++.h"
#include"Student.h"
struct luaFuncModeConfig
{
	int systemId;//��ģ���Ӧ��ģ����ţ��������map��keyֵ������һ�µ�
	char* luaFilePath;//�ű��ļ���·��
	char* modeName;//ģ������
	lua_State* Lvm;//��ģ���Ӧ��lua�����
};

class LuaScript
{
public:
	

	~LuaScript();
	static LuaScript* getInstance();
	void loadFunctionConfig();//װ�ؽű�����
	void startUpLuaScript();//�����ű�ģ��
	void reloadFunctionMode(int systemId);//�ȸ�ָ��ģ��
	void reloadAllFunctionMode();//�ȸ�����ģ��
private:
	std::map<int, luaFuncModeConfig>  mapLuaFuncModeConfig;
	std::map<int, luaFuncModeConfig>  mapLuaFuncModeConfigBuffer;
	std::list<lua_State* > listLuaFuncDeleteMode;//��¼�����޸�ж�ص�ģ��
	std::list<int> listLuaFuncAddMode;//��¼�����޸���ӵ�ģ��
	std::list<int> listLuaFuncChanagedMode;//��¼�����޸ĵ�����ģ��
	static LuaScript* LUA_INSTANCE;
	LuaScript();
};

