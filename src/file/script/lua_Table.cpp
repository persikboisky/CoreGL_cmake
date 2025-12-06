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
		Table::Table(Stack* stack, std::string name) : stack(stack), name(std::move(name))
		{}

		Table::num Table::getNumber(const std::string& name)
		{
			stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(name);
			double num = stack->getNumber(-1);
			stack->free(2);
			return num;
		}

		Table::str Table::getString(const std::string& name)
		{
			stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(name);
			std::string str = stack->getString(-1);
			stack->free(2);
			return str;
		}

		int Table::getInteger(const std::string& name)
		{
			stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(name);
			int num = stack->getInteger(-1);
			stack->free(2);
			return num;
		}

		bool Table::getBoolean(const std::string& name)
		{
			stack->pushFromGlobal(this->name);
			stack->pushFromGlobalTable(name);
			bool flag = stack->getBoolean(-1);
			stack->free(2);
			return flag;
		}
	} // lua
} // core