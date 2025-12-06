//
// Created by kisly on 05.12.2025.
//

#include "lua_Stack.hpp"
#include "lua_Runner.hpp"
#include "lua_Table.hpp"
#include "lua_Function.hpp"
#include "../../util/coders.hpp"
#include <lua.hpp>
#include <format>

namespace core::lua
{
	Stack::Stack(lua_State* ptrState) : state(ptrState) {}

	Stack::~Stack()
	{

	}

	void Stack::push(bool value)
	{
		lua_pushboolean(this->state, value);
	}

	void Stack::push(int value)
	{
		lua_pushinteger(this->state, value);
	}

	void Stack::push(Stack::num value)
	{
		lua_pushnumber(this->state, value);
	}

	void Stack::push(Stack::str value)
	{
		lua_pushstring(state, value.c_str());
	}

	void Stack::pushNil()
	{
		lua_pushnil(state);
	}

	bool Stack::isType(const TYPE& type, int idx)
	{
		int state = 0;
		switch(type)
		{
		case TYPE::INTEGER:
			state = lua_isinteger(this->state, idx);
			break;
		case TYPE::NIL:
			state = lua_isnil(this->state, idx);
			break;
		case TYPE::NUMBER:
			state = lua_isnumber(this->state, idx);
			break;
		case TYPE::STRING:
			state = lua_isstring(this->state, idx);
			break;
		case TYPE::FUNCTION:
			state = lua_isfunction(this->state, idx);
			break;
		case TYPE::BOOLEAN:
		default:
			state = lua_isboolean(this->state, idx);
			break;
		}

		if (state == 0)
			return false;
		return true;
	}

	void Stack::pushFromGlobal(std::string name)
	{
		lua_getglobal(state, name.c_str());
		if (isType(TYPE::NIL, -1))
		{
			throw coders(NONE_CODERS, "Lua Error: (" + name + ") isn't variable");
		}
	}

	void Stack::call(int nArguments, int nReturns)
	{
		if (lua_pcall(state, nArguments, nReturns, 0) != LUA_OK)
		{
			std::string error = lua_tostring(state, -1);
			throw coders(NONE_CODERS, std::format("Lua Error: call({}, {}): ", nArguments, nReturns) + error);
		}
	}

	bool Stack::getBoolean(int idx)
	{
		if (!isType(TYPE::BOOLEAN, idx))
		{
			throw coders(NONE_CODERS, std::format("Lua Error: getBoolean({}) isn't boolean", idx));
		}
		return lua_toboolean(state, idx);
	}

	int Stack::getInteger(int idx)
	{
		if (!isType(TYPE::INTEGER, idx))
		{
			throw coders(NONE_CODERS, std::format("Lua Error: getInteger({}) isn't integer", idx));
		}
		return lua_tointeger(state, idx);
	}

	Stack::num Stack::getNumber(int idx)
	{
		if (!isType(TYPE::NUMBER, idx))
		{
			throw coders(NONE_CODERS, std::format("Lua Error: getNumber({}) isn't number", idx));
		}
		return lua_tonumber(state, idx);
	}

	std::string Stack::getString(int idx)
	{
		if (!isType(TYPE::STRING, idx))
		{
			throw coders(NONE_CODERS, std::format("Lua Error: getString({}) isn't string", idx));
		}
		return lua_tostring(state, idx);
	}

	void Stack::free(int count)
	{
		lua_pop(state, count);
	}

	int Stack::getTopElementIndex()
	{
		return lua_gettop(state);
	}

	void Stack::pushFromGlobalTable(std::string name, int idx)
	{
		lua_getfield(state, idx, name.c_str());
	}

	Table Stack::getTable(const std::string& name)
	{
		return Table(this, name);
	}

	Function Stack::getFunction(const std::string& name)
	{
		return Function(this, name);
	}

//	void Stack::pushFunction(const std::string& name, int (*)(FunctionStack*) func)
//	{
//
//	}

} // core::lua

