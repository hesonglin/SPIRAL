#include "stdafx.h"
#include "LuaScript.h"

//hsl 2019 -02 -26
/*�˴���Ҫ������ÿһ������ģ�鶼��Ӧһ��lua��������������������
����Ӧһ��lua������á�*/
/*2019 -02 -26 ��д��ÿһ������ģ���Ӧһ��lua���������ʽ������Ŀǰ
ֻ��һ������ģ��*/
extern int tolua_server_open(lua_State* tolua_S);
extern int tolua_system_open(lua_State* tolua_S);
//����ģʽ���쵥��
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

void LuaScript::loadFunctionConfig()//װ�ؽű�����
{
	mapLuaFuncModeConfigBuffer.clear();
	luaFuncModeConfig buffer;
	buffer.luaFilePath = "./chatSystem.lua";//"./Data/luaScript/system/ChatSystem/chatSystem.lua";//"system\\ChatSystem\\chatSystem.lua";
	buffer.systemId = 1;
	buffer.Lvm = 0;
	mapLuaFuncModeConfigBuffer[1] = buffer;
	//map<int, luaFuncModeConfig>  mapLuaFuncModeConfig;
	//װ�������ݵ� mapLuaFuncModeConfigBuffer

	//�Ƚ�mapLuaFuncModeConfigBuffer �� mapLuaFuncModeConfig
	//1��ж�ص�ģ�� listLuaFuncDeleteMode
	//2���¼ӵ�ģ�� listLuaFuncAddMode
	//3���ı��ļ�·����ģ�� listLuaFuncChanagedMode
	std::map<int, luaFuncModeConfig>::iterator iter1;
	iter1 = mapLuaFuncModeConfig.begin();
	std::map<int, luaFuncModeConfig>::iterator iter2;
	iter2 = mapLuaFuncModeConfigBuffer.begin();

	listLuaFuncAddMode.clear();
	listLuaFuncChanagedMode.clear();
	listLuaFuncDeleteMode.clear();

	while (iter2 != mapLuaFuncModeConfigBuffer.end())
	{
		
		if (mapLuaFuncModeConfig.end() == mapLuaFuncModeConfig.find(iter2->first))//�Ҳ��������
		{
			//������ģ��
			listLuaFuncAddMode.push_back(iter2->first);
			mapLuaFuncModeConfig[iter2->first] = iter2->second;
		}
		else//�ҵ������
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
		if (mapLuaFuncModeConfigBuffer.end() == mapLuaFuncModeConfigBuffer.find(iter1->first))//�Ҳ��������
		{
			//��ɾ����ģ��
			listLuaFuncDeleteMode.push_back(iter2->second.Lvm);

			//luaFuncModeConfig buffer = iter1->second;
			//if (buffer.Lvm) { lua_close(buffer.Lvm); }//ģ�鱻ɾ�����ر�lua�����
			mapLuaFuncModeConfig.erase(iter1->first);
		}
		iter1++;
	}

	//ͬ��mapLuaFuncModeConfigBuffer �� mapLuaFuncModeConfig
/*	mapLuaFuncModeConfig.clear();
	iter2 = mapLuaFuncModeConfigBuffer.begin();
	while (iter2 != mapLuaFuncModeConfigBuffer.end())
	{
		//�����ǰ�е�ģ�飬�򱣳��������ַ����
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
void LuaScript::startUpLuaScript()//�����ű�ģ��
{
	std::map<int, luaFuncModeConfig>::iterator iter;
	iter = mapLuaFuncModeConfig.begin();
	while (iter != mapLuaFuncModeConfig.end())
	{
		//luaFuncModeConfig buffer = iter->second;
		if (iter->second.Lvm) { lua_close(iter->second.Lvm); }//δ�ر������������йر�
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		//tolua_server_open(L);
		tolua_system_open(L);
		//L = luaL_newstate();
		iter->second.systemId = iter->first;
		iter->second.Lvm = L;//���������

		//luaL_dofile����ֻʶ��/������ʶ��\��
		//./��ʾ��ǰ�ļ�����Ŀ¼
		int res = luaL_dofile(L, iter->second.luaFilePath);//�������ܳ���
		if (res == 1) { printf("%d�����������ʧ��", iter->second.systemId); }
		iter++;
	}
}

//�ȸ�֮ǰ����װ������
void LuaScript::reloadFunctionMode(int systemId)//�ȸ�ָ��ģ��
{
	loadFunctionConfig();
	//std::map<int, luaFuncModeConfig>::iterator iter;
	luaFuncModeConfig buffer = mapLuaFuncModeConfig[systemId];
	if(!buffer.Lvm)//��������ڣ��򴴽������
	{
		lua_State* L = luaL_newstate();
		buffer.systemId = systemId;
		buffer.Lvm = L;//���������
		luaL_openlibs(L);
		luaL_dofile(L, buffer.luaFilePath);//�������ܳ���
	}
	else//������ڣ�ֱ���ȸ�
	{
		lua_getglobal(buffer.Lvm, "rsf");   //������Ϊrsf
		lua_pcall(buffer.Lvm, 0, 0, 0);  //�ñ���ģʽ����lua��������θ���Ϊ0�����θ���Ϊ0�����Զ��������
		return;
	}
}

//�ȸ�֮ǰ����װ������
void LuaScript::reloadAllFunctionMode()//�ȸ�����ģ��
{
	loadFunctionConfig();
	std::map<int, luaFuncModeConfig>::iterator iter;
	iter = mapLuaFuncModeConfig.begin();
	while (iter != mapLuaFuncModeConfig.end())
	{
		//���1������ȸ������������б�����
		//���2������ȸ�������ɾ���б�����
		//���3������ȸ��������޸��б�����
		//���4���������
		if ((std::find(listLuaFuncAddMode.begin(), listLuaFuncAddMode.end(), iter->first) != listLuaFuncAddMode.end()) ||
			(std::find(listLuaFuncChanagedMode.begin(), listLuaFuncChanagedMode.end(), iter->first) != listLuaFuncChanagedMode.end()))
		{
			luaFuncModeConfig buffer = iter->second;
			if (buffer.Lvm) { lua_close(buffer.Lvm); }//δ�ر������������йر�
			lua_State* L = luaL_newstate();
			buffer.systemId = iter->first;
			buffer.Lvm = L;//���������
			luaL_openlibs(L);
			luaL_dofile(L, buffer.luaFilePath);//�������ܳ���
		}
		else
		{
			luaFuncModeConfig buffer = iter->second;
			if (!buffer.Lvm) { continue; }//��������Ϊ�գ����˳�
			lua_getglobal(buffer.Lvm, "rsf");   //������Ϊrsf
			lua_pcall(buffer.Lvm, 0, 0, 0);  //�ñ���ģʽ����lua��������θ���Ϊ0�����θ���Ϊ0�����Զ��������
		}
		iter++;
	}
	std::list<lua_State* >::iterator listiter;
	listiter = listLuaFuncDeleteMode.begin();
	while (listiter != listLuaFuncDeleteMode.end())
	{
		if (*listiter) { lua_close(*listiter); }//ģ�鱻ɾ�����ر�lua�����
		listiter++;
	}
}