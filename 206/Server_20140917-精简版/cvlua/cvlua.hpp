//导出这些库
extern "C"	
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

//条件编译
#ifdef _WIN32
#define LUA_API __declspec(dllexport)
#else
#define LUA_API
#endif

//函数原型声明
lua_State *engine_open(char *init="init.lua");
int engine_eval(lua_State *L, char *cmd);