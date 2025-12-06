//
// Created by kisly on 05.12.2025.
//

#ifndef LUA_STACK_HPP
#define LUA_STACK_HPP

#include "lua_Function.hpp"

namespace core::lua
{
	class Table;
	class Function;

	enum class TYPE : int
	{
		BOOLEAN,
		INTEGER,
		NUMBER,
		STRING,
		NIL,
		FUNCTION
	};

	class Stack
	{
	protected:
		friend class Runner;

	private:
		using num = double;
		using str = std::string;

		lua_State* state = nullptr;

		Stack(lua_State* ptrState);

	public:
		~Stack();

		void push(bool value);
		void push(int value);
		void push(num value);
		void push(str value);
		void pushNil();

		bool isType(const TYPE& type, int idx);

		void pushFromGlobal(std::string name);
		void call(int nArguments, int nReturns);

		bool getBoolean(int idx);
		int getInteger(int idx);
		Stack::num getNumber(int idx);
		std::string getString(int idx);

		void free(int count);

		int getTopElementIndex();

		void pushFromGlobalTable(std::string name, int idx = -1);

		Table getTable(const std::string& name);
		Function getFunction(const std::string& name);

		void pushFunction((int)(FunctionStack*) func);
	};
} // core::lua

#endif //LUA_STACK_HPP
