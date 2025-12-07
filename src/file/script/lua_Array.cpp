//
// Created by kisly on 07.12.2025.
//

#include "lua_Array.hpp"
#include "lua_Stack.hpp"
#include <lua.hpp>
#include <utility>

namespace core
{
	namespace lua
	{
		Array::Array(Stack* stack, std::string name) : stack(stack), name(std::move(name))
		{}

		Array::num Array::getNumber(int index)
		{
			if (nFree == 0)
				stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(index);
			double num = stack->getNumber(-1);
			if (nFree == 0)
				stack->free(2);
			else
				stack->free(1);
			return num;
		}

		Array::str Array::getString(int index)
		{
			if (nFree == 0)
				stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(index);
			std::string str = stack->getString(-1);
			if (nFree == 0)
				stack->free(2);
			else
				stack->free(1);
			return str;
		}

		int Array::getInteger(int index)
		{
			if (nFree == 0)
				stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(index);
			int num = stack->getInteger(-1);
			if (nFree == 0)
				stack->free(2);
			else
				stack->free(1);
			return num;
		}

		bool Array::getBoolean(int index)
		{
			if (nFree == 0)
				stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(index);
			bool flag = stack->getBoolean(-1);
			if (nFree == 0)
				stack->free(2);
			else
				stack->free(1);
			return flag;
		}

		void Array::goTo(int index)
		{
			if (nFree == 0)
			{
				stack->pushFromGlobal(name);
				nFree++;
			}

			lua_rawgeti(stack->state, -1, index);
			nFree++;
		}

		void Array::goHome()
		{
			stack->free(nFree);
			nFree = 0;
		}

		void Array::goBack()
		{
			stack->free(1);
			nFree--;
		}
	} // lua
} // core