#include "stdafx.h"
#include "LuaScript.h"

//hsl 2019 -02 -26
/*此处需要考虑是每一个功能模块都对应一个lua虚拟机，还是整个服务端
都对应一个lua虚拟机好。*/
/*2019 -02 -26 先写出每一个功能模块对应一个lua虚拟机的形式，但是目前
只有一个功能模块*/
extern int tolua_server_open(lua_State* tolua_S);
extern int tolua_system_open(lua_State* tolua_S);
//饿汉模式构造单例
LuaScript* LuaScript::LUA_INSTANCE = new LuaScript();

LuaScript::LuaScript()
{
}


LuaScript::~LuaScript()
{
}

LuaScript* LuaScript::getInstance()
{
	return LUA_INSTANCE;
}

void LuaScript::loadFunctionConfig()//装载脚本配置
{
	mapLuaFuncModeConfigBuffer.clear();
	luaFuncModeConfig buffer;
	buffer.luaFilePath = "./chatSystem.lua";//"./Data/luaScript/system/ChatSystem/chatSystem.lua";//"system\\ChatSystem\\chatSystem.lua";
	buffer.systemId = 1;
	buffer.Lvm = 0;
	mapLuaFuncModeConfigBuffer[1] = buffer;
	//map<int, luaFuncModeConfig>  mapLuaFuncModeConfig;
	//装载完数据到 mapLuaFuncModeConfigBuffer

	//比较mapLuaFuncModeConfigBuffer 与 mapLuaFuncModeConfig
	//1、卸载的模块 listLuaFuncDeleteMode
	//2、新加的模块 listLuaFuncAddMode
	//3、改变文件路径的模块 listLuaFuncChanagedMode
	std::map<int, luaFuncModeConfig>::iterator iter1;
	iter1 = mapLuaFuncModeConfig.begin();
	std::map<int, luaFuncModeConfig>::iterator iter2;
	iter2 = mapLuaFuncModeConfigBuffer.begin();

	listLuaFuncAddMode.clear();
	listLuaFuncChanagedMode.clear();
	listLuaFuncDeleteMode.clear();

	while (iter2 != mapLuaFuncModeConfigBuffer.end())
	{
		
		if (mapLuaFuncModeConfig.end() == mapLuaFuncModeConfig.find(iter2->first))//找不到的情况
		{
			//新增的模块
			listLuaFuncAddMode.push_back(iter2->first);
			mapLuaFuncModeConfig[iter2->first] = iter2->second;
		}
		else//找到的情况
		{
			//luaFuncModeConfig buffer2 = iter2->second;
			luaFuncModeConfig buffer = mapLuaFuncModeConfig[iter2->first];
			if (strcmp(buffer.luaFilePath , iter2->second.luaFilePath)!=0)
			{
				listLuaFuncChanagedMode.push_back(iter2->first);
				mapLuaFuncModeConfig[iter2->first] = iter2->second;
			}
		}
		iter2++;
	}

	iter2 = mapLuaFuncModeConfigBuffer.begin();
	iter1 = mapLuaFuncModeConfig.begin();
	while (iter1 != mapLuaFuncModeConfig.end())
	{
		if (mapLuaFuncModeConfigBuffer.end() == mapLuaFuncModeConfigBuffer.find(iter1->first))//找不到的情况
		{
			//被删除的模块
			listLuaFuncDeleteMode.push_back(iter2->second.Lvm);

			//luaFuncModeConfig buffer = iter1->second;
			//if (buffer.Lvm) { lua_close(buffer.Lvm); }//模块被删除，关闭lua虚拟机
			mapLuaFuncModeConfig.erase(iter1->first);
		}
		iter1++;
	}

	//同步mapLuaFuncModeConfigBuffer 与 mapLuaFuncModeConfig
/*	mapLuaFuncModeConfig.clear();
	iter2 = mapLuaFuncModeConfigBuffer.begin();
	while (iter2 != mapLuaFuncModeConfigBuffer.end())
	{
		//如果以前有的模块，则保持虚拟机地址不变
		/*luaFuncModeConfig buffer;
		buffer.luaFilePath = iter2->second.luaFilePath;
		buffer.Lvm = iter2->second.Lvm;
		buffer.modeName = iter2->second.modeName;
		buffer.systemId = iter2->second.systemId;
		buffer = iter2->second;//
		mapLuaFuncModeConfig[iter2->first] = iter2->second;
		iter2++;
	}*/
}
//lua_State* L;
void LuaScript::startUpLuaScript()//开启脚本模块
{
	std::map<int, luaFuncModeConfig>::iterator iter;
	iter = mapLuaFuncModeConfig.begin();
	while (iter != mapLuaFuncModeConfig.end())
	{
		//luaFuncModeConfig buffer = iter->second;
		if (iter->second.Lvm) { lua_close(iter->second.Lvm); }//未关闭虚拟机，则进行关闭
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		//tolua_server_open(L);
		tolua_system_open(L);
		//L = luaL_newstate();
		iter->second.systemId = iter->first;
		iter->second.Lvm = L;//保存虚拟机

		//luaL_dofile函数只识别“/”，不识别“\”
		//./表示当前文件所在目录
		int res = luaL_dofile(L, iter->second.luaFilePath);//启动功能程序
		if (res == 1) { printf("%d号虚拟机启动失败", iter->second.systemId); }
		iter++;
	}
}

//热更之前，先装载配置
void LuaScript::reloadFunctionMode(int systemId)//热更指定模块
{
	loadFunctionConfig();
	//std::map<int, luaFuncModeConfig>::iterator iter;
	luaFuncModeConfig buffer = mapLuaFuncModeConfig[systemId];
	if(!buffer.Lvm)//如果不存在，则创建虚拟机
	{
		lua_State* L = luaL_newstate();
		buffer.systemId = systemId;
		buffer.Lvm = L;//保存虚拟机
		luaL_openlibs(L);
		luaL_dofile(L, buffer.luaFilePath);//启动功能程序
	}
	else//如果存在，直接热更
	{
		lua_getglobal(buffer.Lvm, "rsf");   //函数名为rsf
		lua_pcall(buffer.Lvm, 0, 0, 0);  //用保护模式调用lua函数，入参个数为0、出参个数为0、无自定义错误处理
		return;
	}
}

//热更之前，先装载配置
void LuaScript::reloadAllFunctionMode()//热更所有模块
{
	loadFunctionConfig();
	std::map<int, luaFuncModeConfig>::iterator iter;
	iter = mapLuaFuncModeConfig.begin();
	while (iter != mapLuaFuncModeConfig.end())
	{
		//情况1、如果热更对象在新增列表里面
		//情况2、如果热更对象在删除列表里面
		//情况3、如果热更对象在修改列表里面
		//情况4、其余情况
		if ((std::find(listLuaFuncAddMode.begin(), listLuaFuncAddMode.end(), iter->first) != listLuaFuncAddMode.end()) ||
			(std::find(listLuaFuncChanagedMode.begin(), listLuaFuncChanagedMode.end(), iter->first) != listLuaFuncChanagedMode.end()))
		{
			luaFuncModeConfig buffer = iter->second;
			if (buffer.Lvm) { lua_close(buffer.Lvm); }//未关闭虚拟机，则进行关闭
			lua_State* L = luaL_newstate();
			buffer.systemId = iter->first;
			buffer.Lvm = L;//保存虚拟机
			luaL_openlibs(L);
			luaL_dofile(L, buffer.luaFilePath);//启动功能程序
		}
		else
		{
			luaFuncModeConfig buffer = iter->second;
			if (!buffer.Lvm) { continue; }//如果虚拟机为空，则退出
			lua_getglobal(buffer.Lvm, "rsf");   //函数名为rsf
			lua_pcall(buffer.Lvm, 0, 0, 0);  //用保护模式调用lua函数，入参个数为0、出参个数为0、无自定义错误处理
		}
		iter++;
	}
	std::list<lua_State* >::iterator listiter;
	listiter = listLuaFuncDeleteMode.begin();
	while (listiter != listLuaFuncDeleteMode.end())
	{
		if (*listiter) { lua_close(*listiter); }//模块被删除，关闭lua虚拟机
		listiter++;
	}
}