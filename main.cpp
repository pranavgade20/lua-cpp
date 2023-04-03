#include <iostream>

// include Lua headers
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

// *** define C++ function ***
static int MyCppFunction(lua_State* L) // Lua callable functions must be this format
{
    const int num = (int)lua_tonumber(L,1); // get first param from stack
    const char* str = lua_tostring(L,2); // get second param from stack
    std::cout << "Hello from C++!" << std::endl;
    std::cout << "num = " << num << ", str = " << str << std::endl;
    return 0; // how many params we're passing to Lua
}

int main(int argc, const char * argv[])
{
    lua_State* L = luaL_newstate(); // create a new lua instance
    luaL_openlibs(L); // give lua access to basic libraries
    luaL_dofile(L, "main.lua"); // loads the Lua script

    // *** call Lua function from C++ ***
    lua_getglobal(L, "increment"); // find the Lua function
    lua_pushnumber(L, 42); // push number as param
    if (lua_pcall(L, 1, 1, 0) != 0) // call the function
        std::cerr << "error running function `increment`:" << lua_tostring(L, -1);
    if (!lua_isnumber(L, -1))
        std::cerr << "function `increment` must return a number";
    int num = lua_tonumber(L, -1);
    lua_pop(L, 1);  /* pop returned value */
    std::cout << "in c++, lua returned num = " << num;
    return 0;
}