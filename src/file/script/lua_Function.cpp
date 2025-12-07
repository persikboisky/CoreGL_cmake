//
// Created by kisly on 06.12.2025.
//

#include "lua_Function.hpp"
#include "lua_Stack.hpp"
#include <utility>
#include <lua.hpp>

namespace core
{
	namespace lua
	{
		FunctionStack::FunctionStack(lua_State* state) : state(state)
		{}

		FunctionStack FunctionStack::create(lua_State* state)
		{
			return FunctionStack(state);
		}

		int FunctionStack::getInteger(int idx)
		{
			return lua_tonumber(state, idx);
		}

		FunctionStack::num FunctionStack::getNumber(int idx)
		{
			return lua_tonumber(state, idx);
		}

		FunctionStack::str FunctionStack::getString(int idx)
		{
			return lua_tostring(state, idx);
		}

		bool FunctionStack::getBoolean(int idx)
		{
			return lua_toboolean(state, idx);
		}

		void FunctionStack::pushNumber(FunctionStack::num number)
		{
			lua_pushnumber(state, number);
		}

		void FunctionStack::pushInteger(int number)
		{
			lua_pushinteger(state, number);
		}

		void FunctionStack::pushString(std::string str)
		{
			lua_pushstring(state, str.c_str());
		}

		void FunctionStack::pushBoolean(bool flag)
		{
			lua_pushboolean(state, flag);
		}

		Function::Function(lua::Stack* stack, std::string name) : stack(stack), name(std::move(name))
		{}

		Function::Function(Stack* stack) : stack(stack)
		{}

		void Function::set(Function::num number)
		{
			if (flagGetFunction)
			{
				stack->pushFromGlobal(name);
				flagGetFunction = false;
			}

			nArguments++;
			stack->push(number);
		}

		void Function::set(int integer)
		{
			if (flagGetFunction)
			{
				stack->pushFromGlobal(name);
				flagGetFunction = false;
			}

			nArguments++;
			stack->push(integer);
		}

		void Function::set(Function::str string)
		{
			if (flagGetFunction)
			{
				stack->pushFromGlobal(name);
				flagGetFunction = false;
			}

			nArguments++;
			stack->push(std::move(string));
		}

		void Function::set(bool boolean)
		{
			if (flagGetFunction)
			{
				stack->pushFromGlobal(name);
				flagGetFunction = false;
			}

			nArguments++;
			stack->push(boolean);
		}

		void Function::run(int nReturns)
		{
			this->nReturns = nReturns;
			stack->call(nArguments, nReturns);
		}

		Function::num Function::getNumber()
		{
			nReturns--;
			Function::num num = stack->getNumber(-nReturns - 1);
			if (nReturns == 0)
				stack->free(1);
			return num;
		}

		int Function::getInteger()
		{
			nReturns--;
			int num = stack->getInteger(-nReturns - 1);
			if (nReturns == 0)
				stack->free(1);
			return num;
		}

		Function::str Function::getString()
		{
			nReturns--;
			std::string str = stack->getString(-nReturns - 1);
			if (nReturns == 0)
				stack->free(1);
			return str;
		}

		bool Function::getBoolean()
		{
			nReturns--;
			bool flag = stack->getBoolean(-nReturns - 1);
			if (nReturns == 0)
				stack->free(1);
			return flag;
		}

	}
} // core