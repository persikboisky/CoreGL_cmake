//
// Created by kisly on 05.12.2025.
//

#include "lua_Runner.hpp"
#include "../code.hpp"
#include "../../config.hpp"
#include "../../util/coders.hpp"
#include "../../util/console.hpp"
#include "lua_Stack.hpp"
#include <lua.hpp>
#include <iostream>

namespace core::lua
{
	Runner::Runner(const char *code, bool flagDebuInfo)
	{
		this->state = luaL_newstate();
		if (this->state == nullptr)
			throw coders(NONE_CODERS, "Failed create lua state");
		luaL_openlibs(this->state);

		if (luaL_loadstring(this->state, code) != LUA_OK)
			throw coders(NONE_CODERS, "Syntax error: " + std::string(lua_tostring(this->state, -1)));

		else
		{
			if (CORE_INFO && flagDebuInfo)
			{
				console::printTime();
				std::cout << "Ok: compile lua script" << std::endl;
			}
		}

		this->stack = new lua::Stack(this->state);
	}

	Runner::~Runner()
	{
		delete this->stack;
		lua_close(this->state);
	}

	Runner Runner::compileFromFile(const char *path, bool flagDebuInfo)
	{
		return Runner(code::loadStr(path, flagDebuInfo).c_str(), flagDebuInfo);
	}

	Runner Runner::compileFromCode(const char *code, bool flagDebuInfo)
	{
		return Runner(code, flagDebuInfo);
	}

	Runner *Runner::ptrCompileFromFile(const char *path, bool flagDebuInfo)
	{
		return new Runner(code::loadStr(path, flagDebuInfo).c_str(), flagDebuInfo);
	}

	Runner *Runner::ptrCompileFromCode(const char *code, bool flagDebuInfo)
	{
		return new Runner(code, flagDebuInfo);
	}

	void Runner::run()
	{
		if (lua_pcall(this->state, 0, 0, 0) != LUA_OK)
			throw coders(NONE_CODERS, "Runtime error: " + std::string(lua_tostring(this->state, -1)));
	}

	double Runner::nRun()
	{
		if (lua_pcall(this->state, 0, 1, 0) == LUA_OK)
		{
			double lua_result = lua_tonumber(this->state, -1);
			lua_pop(this->state, 1);
			return lua_result;
		}
		else
			throw coders(NONE_CODERS, "Runtime error: " + std::string(lua_tostring(this->state, -1)));
	}

	int Runner::iRun()
	{
		if (lua_pcall(this->state, 0, 1, 0) == LUA_OK)
		{
			int lua_result = lua_tointeger(this->state, -1);
			lua_pop(this->state, 1);
			return lua_result;
		}
		else
			throw coders(NONE_CODERS, "Runtime error: " + std::string(lua_tostring(this->state, -1)));
	}

	std::string Runner::strRun()
	{
		if (lua_pcall(this->state, 0, 1, 0) == LUA_OK)
		{
			std::string lua_result = lua_tostring(this->state, -1);
			lua_pop(this->state, 1);
			return lua_result;
		}
		else
			throw coders(NONE_CODERS, "Runtime error: " + std::string(lua_tostring(this->state, -1)));
	}

	bool Runner::bRun()
	{
		if (lua_pcall(this->state, 0, 1, 0) == LUA_OK)
		{
			bool lua_result = lua_toboolean(this->state, -1);
			lua_pop(this->state, 1);
			return lua_result;
		}
		else
			throw coders(NONE_CODERS, "Runtime error: " + std::string(lua_tostring(this->state, -1)));
	}
}
