/*
** Lua binding: system
** Generated automatically by tolua++-1.0.92 on Sat Mar  2 15:53:24 2019.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_system_open (lua_State* tolua_S);

#include "SystemLuaExport.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: LSystem::getVersion */
#ifndef TOLUA_DISABLE_tolua_system_LSystem_getVersion00
static int tolua_system_LSystem_getVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  LSystem::getVersion();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LSystem::setVersionId */
#ifndef TOLUA_DISABLE_tolua_system_LSystem_setVersionId00
static int tolua_system_LSystem_setVersionId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int versionId = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  LSystem::setVersionId(versionId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVersionId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_system_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"LSystem",0);
  tolua_beginmodule(tolua_S,"LSystem");
   tolua_function(tolua_S,"getVersion",tolua_system_LSystem_getVersion00);
   tolua_function(tolua_S,"setVersionId",tolua_system_LSystem_setVersionId00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_system (lua_State* tolua_S) {
 return tolua_system_open(tolua_S);
};
#endif

