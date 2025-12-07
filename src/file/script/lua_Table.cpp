//
// Created by kisly on 06.12.2025.
//

#include "lua_Table.hpp"
#include "lua_Stack.hpp"
#include <lua.hpp>
#include <utility>

namespace core
{
	namespace lua
	{
		Table::Table(Stack* stack, std::string name) : stack(stack), name(name) {}

		Table::~Table()
		{
			if (nFree != 0)
				stack->free(nFree);
		}

		Table::num Table::getNumber(const std::string& name)
		{
			if (nFree == 0)
				stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(name);
			double num = stack->getNumber(-1);
			if (nFree == 0)
				stack->free(2);
			else
				stack->free(1);
			return num;
		}

		Table::str Table::getString(const std::string& name)
		{
			if (nFree == 0)
				stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(name);
			std::string str = stack->getString(-1);
			if (nFree == 0)
				stack->free(2);
			else
				stack->free(1);
			return str;
		}

		int Table::getInteger(const std::string& name)
		{
			if (nFree == 0)
				stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(name);
			int num = stack->getInteger(-1);
			if (nFree == 0)
				stack->free(2);
			else
				stack->free(1);
			return num;
		}

		bool Table::getBoolean(const std::string& name)
		{
			if (nFree == 0)
				stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(name);
			bool flag = stack->getBoolean(-1);
			if (nFree == 0)
				stack->free(2);
			else
				stack->free(1);
			return flag;
		}

		void Table::goTo(const std::string& name)
		{
			if (nFree == 0)
			{
				stack->pushFromGlobal(this->name);
				nFree++;
			}

			lua_getfield(stack->state, -1, name.c_str());
			nFree++;
		}

		void Table::goTo(int index)
		{
			if (nFree == 0)
			{
				stack->pushFromGlobal(name);
				nFree++;
			}

			lua_rawgeti(stack->state, -1, index);
			nFree++;
		}

		void Table::goHome()
		{
			stack->free(nFree);
			nFree = 0;
		}

		void Table::goBack()
		{
			stack->free(1);
			nFree--;
		}

		Table::num Table::getNumber(int index)
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

		Table::str Table::getString(int index)
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

		int Table::getInteger(int index)
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

		bool Table::getBoolean(int index)
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
	} // lua
} // core