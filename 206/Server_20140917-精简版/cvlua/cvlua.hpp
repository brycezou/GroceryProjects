//������Щ��
extern "C"	
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

//��������
#ifdef _WIN32
#define LUA_API __declspec(dllexport)
#else
#define LUA_API
#endif

//����ԭ������
lua_State *engine_open(char *init="init.lua");
int engine_eval(lua_State *L, char *cmd);