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
	int systemId;//该模块对应的模块序号，该序号与map的key值必须是一致的
	char* luaFilePath;//脚本文件主路径
	char* modeName;//模块名称
	lua_State* Lvm;//该模块对应的lua虚拟机
};

class LuaScript
{
public:
	

	~LuaScript();
	static LuaScript* getInstance();
	void loadFunctionConfig();//装载脚本配置
	void startUpLuaScript();//开启脚本模块
	void reloadFunctionMode(int systemId);//热更指定模块
	void reloadAllFunctionMode();//热更所有模块
private:
	std::map<int, luaFuncModeConfig>  mapLuaFuncModeConfig;
	std::map<int, luaFuncModeConfig>  mapLuaFuncModeConfigBuffer;
	std::list<lua_State* > listLuaFuncDeleteMode;//记录本次修改卸载的模块
	std::list<int> listLuaFuncAddMode;//记录本次修改添加的模块
	std::list<int> listLuaFuncChanagedMode;//记录本次修改调整的模块
	static LuaScript* LUA_INSTANCE;
	LuaScript();
};

