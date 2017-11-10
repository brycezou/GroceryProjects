//加载必要的头文件
#include <windows.h>
#include <iostream>
using namespace std;

//导出这些库
extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

//测试代码, 项目中未使用
int test(lua_State *L)
{
	int argc = lua_gettop(L);
	cerr<<"-- test called with "<<argc<<" arguments: ";
	for (int i = 1; i <= argc; i++)
		cerr<<lua_tostring(L, i) << ",";
	cerr<<endl;
	return 0;
}

//加载脚本文件init
lua_State *engine_open(char *init)
{
	//加载lua核心库
	lua_State *L = lua_open();
	luaL_openlibs(L);

	lua_register(L, "test", test);
	//执行脚本文件
	if (luaL_dofile(L, init) != 0) //如果执行脚本文件失败
	{
		const char* errmsg = lua_tostring(L, -1); //得到错误信息
		cerr<<errmsg<<endl; //输出错误信息
		lua_pop(L,1);
	}
	return L;
}

//执行脚本文件中的cmd函数
int engine_eval(lua_State *L, char *cmd)
{
	//执行脚本文件中的cmd函数
	int retval = luaL_dostring(L, cmd);
	if (retval != 0) //如果执行失败
	{
		const char* errmsg = lua_tostring(L, -1); //得到错误信息
		cerr<<errmsg<<endl; //输出错误信息
		lua_pop(L,1);
	}
	return retval;
}