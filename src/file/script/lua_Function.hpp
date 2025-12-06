//
// Created by kisly on 06.12.2025.
//

#ifndef LUA_FUNCTION_HPP
#define LUA_FUNCTION_HPP

#include <string>
struct lua_State;

namespace core
{
	namespace lua
	{
		class Stack;

		class FunctionStack
		{
		protected:
			friend class Stack;

		private:
			lua_State* stack = nullptr;

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
