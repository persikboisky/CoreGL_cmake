//
// Created by kisly on 07.12.2025.
//

#ifndef LUA_ARRAY_HPP
#define LUA_ARRAY_HPP

#include <string>

namespace core
{
	namespace lua
	{
		class Stack;
		class Array
		{
		protected:
			friend class Stack;

		private:
			using num = double;
			using str = std::string;

			std::string name;
			Stack* stack = nullptr;

			int nFree = 0;

			Array(Stack* stack, std::string name);

		public:
			~Array() = default;

			num getNumber(int index);
			str getString(int index);
			int getInteger(int index);
			bool getBoolean(int index);

			void goTo(int index);
			void goHome();
			void goBack();
		};
	} // lua
} // core

#endif //LUA_ARRAY_HPP
