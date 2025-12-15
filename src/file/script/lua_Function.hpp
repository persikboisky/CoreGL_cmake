//
// Created by kisly on 06.12.2025.
//

#ifndef LUA_FUNCTION_HPP
#define LUA_FUNCTION_HPP

#include <string>
struct lua_State;

namespace core
{
	using State = lua_State;

	namespace lua
	{
		enum class TYPE : int
		{
			BOOLEAN,
			INTEGER,
			NUMBER,
			STRING,
			NIL,
			FUNCTION,
			USER_DATA
		};

		class Stack;
		class FunctionStack
		{
		private:
			using num = double;
			using str = std::string;

			State* state;

			FunctionStack(lua_State* state);

		public:
			static FunctionStack create(State* state);

			int getInteger(int idx);
			num getNumber(int idx);
			str getString(int idx);
			bool getBoolean(int idx);

			void pushNumber(num number);
			void pushInteger(int number);
			void pushString(std::string str);
			void pushBoolean(bool flag);

			void* newUserData(size_t size);
			void* getUserData(int idx);

			bool isType(const TYPE& type, int idx);
		};

		class Function
		{
		protected:
			friend class Stack;

		private:
			using num = double;
			using str = std::string;

			std::string name;
			Stack* stack = nullptr;

			int nArguments = 0;
			int nReturns = 0;
			bool flagGetFunction = true;

			Function(Stack* stack, std::string name);
			Function(Stack* stack);

		public:
			~Function() = default;

			void set(num number);
			void set(int integer);
			void set(str string);
			void set(bool boolean);

			void run(int nReturns);

			num getNumber();
			int getInteger();
			str getString();
			bool getBoolean();
		};
	} // lua
} // core

#endif //LUA_FUNCTION_HPP
