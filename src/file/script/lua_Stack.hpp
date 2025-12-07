//
// Created by kisly on 05.12.2025.
//

#ifndef LUA_STACK_HPP
#define LUA_STACK_HPP

#include "lua_Function.hpp"

namespace core::lua
{
	using State = lua_State;

	class Table;
	class Function;
	class Array;

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
		friend class Table;
		friend class Array;
		friend class Function;

	private:
		using num = double;
		using str = std::string;
		using FunctionPtr = int(*)(core::lua::State);

		lua_State* state = nullptr;

		Stack(lua_State* ptrState);

	public:
		~Stack();

		/// @brief добовляет элемент типа bool в стэк lua
		/// @param value значение
		void push(bool value);

		/// @brief добовляет элемент типа int в стэк lua
		/// @param value значение
		void push(int value);

		/// @brief добовляет элемент типа number(double) в стэк lua
		/// @param value значение
		void push(num value);

		/// @brief добовляет элемент типа string в стэк lua
		/// @param value cстрока
		void push(str value);

		/// @brief добовляет элемент со значением nil
		void pushNil();

		/// @brief проверяет можно ли выбранный элемент представить в виде заданного типа
		/// @param type тип (пример lua::TYPE::BOOLEAN)
		/// @param idx индекс элемента в стеке (пример: -1 отсчёт от последнего элемента(со знаком минус), 
		/// 1 отсчёт от первого элемента)
		/// @return пример (возвращает true если элемент с индексом -1, можно использовать как тип bool)
		bool isType(const TYPE& type, int idx);

		/// @brief добовляет глобальную переменую из lua кода в стек
		/// @param name название переменой
		void pushFromGlobal(std::string name);


		void call(int nArguments, int nReturns);

		bool getBoolean(int idx);
		int getInteger(int idx);
		Stack::num getNumber(int idx);
		std::string getString(int idx);

		void free(int count);
		void free();

		int getTopElementIndex();

		void pushFromGlobalTable(std::string name, int idx = -1);
		void pushFromGlobalTable(int index, int idx = -1);

		Table getTable(const std::string& name);
		Function getFunction(const std::string& name);
		Array getArray(const std::string& name);

		void pushFunction(int(func)(State*), const std::string& name);
	};
} // core::lua

#endif //LUA_STACK_HPP
