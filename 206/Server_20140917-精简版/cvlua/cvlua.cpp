//���ر�Ҫ��ͷ�ļ�
#include <windows.h>
#include <iostream>
using namespace std;

//������Щ��
extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

//���Դ���, ��Ŀ��δʹ��
int test(lua_State *L)
{
	int argc = lua_gettop(L);
	cerr<<"-- test called with "<<argc<<" arguments: ";
	for (int i = 1; i <= argc; i++)
		cerr<<lua_tostring(L, i) << ",";
	cerr<<endl;
	return 0;
}

//���ؽű��ļ�init
lua_State *engine_open(char *init)
{
	//����lua���Ŀ�
	lua_State *L = lua_open();
	luaL_openlibs(L);

	lua_register(L, "test", test);
	//ִ�нű��ļ�
	if (luaL_dofile(L, init) != 0) //���ִ�нű��ļ�ʧ��
	{
		const char* errmsg = lua_tostring(L, -1); //�õ�������Ϣ
		cerr<<errmsg<<endl; //���������Ϣ
		lua_pop(L,1);
	}
	return L;
}

//ִ�нű��ļ��е�cmd����
int engine_eval(lua_State *L, char *cmd)
{
	//ִ�нű��ļ��е�cmd����
	int retval = luaL_dostring(L, cmd);
	if (retval != 0) //���ִ��ʧ��
	{
		const char* errmsg = lua_tostring(L, -1); //�õ�������Ϣ
		cerr<<errmsg<<endl; //���������Ϣ
		lua_pop(L,1);
	}
	return retval;
}