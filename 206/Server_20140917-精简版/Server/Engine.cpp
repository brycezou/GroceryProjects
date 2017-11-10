#include "MServer.hpp"
#include <windows.h>

#include <iostream>
using namespace std;

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int write_log(lua_State *L)
{
	int argc = lua_gettop(L);
	cerr<<"-- write_log called with "<<argc<<" arguments: ";
	for (int i = 1; i <= argc; i++)
		cerr<<lua_tostring(L, i) << endl;
	return 0;
}

lua_State *engine_open()
{
	lua_State *L = lua_open();

	//luaopen_io(L);
	luaopen_base(L);
	//luaopen_table(L);
	luaopen_string(L);

	lua_register(L, "write_log", write_log);
	if (luaL_dofile(L, "init.lua") != 0){
		const char* errmsg = lua_tostring(L, -1);
		cerr<<errmsg<<endl;
		lua_pop(L,1);
	}
	return L;
}

int Engine(void)
{
	lua_State *L = engine_open();

	while (1){
		WaitForSingleObject(cmd_mutex, INFINITE);
		while (!cmds.empty()){
			string cmd = cmds.front();
			cmds.pop();
			cout<<cmd<<endl;
			if (luaL_dostring(L, cmd.c_str()) != 0){
				const char* errmsg = lua_tostring(L, -1);
				cerr<<errmsg<<endl;
				lua_pop(L,1);
			};
		}
		ReleaseMutex(cmd_mutex);
	}
}