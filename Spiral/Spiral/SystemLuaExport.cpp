#include "stdafx.h"
#include "SystemLuaExport.h"

/*int print(lua_State* L)
{
	int n = lua_gettop(L);  // number of arguments
	int i;
	lua_getglobal(L, "tostring");

	for (i = 1; i <= n; i++)
	{
		const char* s;
		lua_pushvalue(L, -1);  // function to be called 
		lua_pushvalue(L, i);   // value to print 
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);  // get result 

		if (s == NULL)
			return luaL_error(L, LUA_QL("tostring") " must return a string to " LUA_QL("print"));

		// 调试用，对于一些特殊的输出，又不知道在哪里输出的，用这个
		//if (strcmp(s, "---------------------------------------------------:") == 0)
		//{
		//	lua_Debug ar;
		//	int nLvl = 0;
		//	while (lua_getstack(L, (int)nLvl, &ar))
		//	{
		//		lua_getinfo(L, "Snl", &ar);
		//		//lua:field:name(file:line)
		//		OutputMsg(rmError, "  %s:%s:%s",
		//			ar.what, ar.namewhat, ar.name ? ar.name : "<NA>");
		//		nLvl++;
		//	}
		//}

		//OutputMsg(rmNormal, s);
		lua_pop(L, 1);  // pop result 
	}

	return 0;
}*/
namespace LSystem
{
	//LSystem.version = 2019;
	int getVersion()
	{
		SpiralNetManager * netManager = SpiralNetManager::getInstance();
		//netManager->num;
		return netManager->num;
	}

	int setVersionId(int versionId)
	{
		int version = 1;
		if (!versionId) { return 1; }
		SpiralNetManager * netManager = SpiralNetManager::getInstance();
		//netManager->num;
		netManager->num = versionId;
		return 0;
	}
/*	int writeInt(void * et)
	{
		return 0;
	}
	const char* readString(void * p)
	{
		return "test";
	}
	*/
}
