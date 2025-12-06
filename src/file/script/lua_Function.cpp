//
// Created by kisly on 06.12.2025.
//

#include "lua_Function.hpp"

#include <utility>
#include "lua_Stack.hpp"

namespace core
{
	namespace lua
	{
		Function::Function(lua::Stack* stack, std::string name) : stack(stack), name(std::move(name))
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