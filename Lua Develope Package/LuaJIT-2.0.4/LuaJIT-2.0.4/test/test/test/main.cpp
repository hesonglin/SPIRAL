#include <stdio.h>  
#include<windows.h>  

extern "C"
{
	#include "lua.h"  
	#include "lualib.h"  
	#include "lauxlib.h"  
	#include "luaconf.h"  
}
#include "tolua++.h"
#include"Student.h"

extern int tolua_server_open(lua_State* tolua_S);
lua_State * rtLuaVm()
{
	lua_State * lvm = luaL_newstate();
	return lvm;
}
int main(int argc, char* argv[])
{
	lua_State* L = rtLuaVm();
	luaL_openlibs(L);

	tolua_server_open(L);

	int res = luaL_dofile(L, "./system.lua");
	
	while (true)
	{
		char msg[100] = "";
		std::cin >> msg;
		//if (msg == "rsf")
		{
			//luaL_dofile(L, "./main.lua");
			lua_getglobal(L, "rsf");   //������Ϊruler
			lua_pcall(L, 0, 0, 0);  //�ñ���ģʽ����lua��������θ���Ϊ0�����θ���Ϊ0�����Զ��������
		}
		//system("pause");
		if (msg == "exit")
		{
			lua_close(L);
			break;
		}
		
	}
	return 0;
}

