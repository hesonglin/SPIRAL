#pragma once
/*C++ -> lua */
//tolua++²Î¿¼ÊÖ²á£ºhttps://blog.csdn.net/zgl390963305/article/details/79948879
//tolua_begin
#include "LuaScript.h"
#include "SpiralNetManager.h"
//int print(lua_State* L);
//int version = 20190215;
namespace LSystem
{
	//int version; 
	int getVersion();
	int setVersionId(int versionId);
	//int writeInt(void * et);
	//const char* readString(void * p);
};
//tolua_end

