//
// Created by kisly on 06.12.2025.
//

#ifndef LUA_TABLE_HPP
#define LUA_TABLE_HPP

#include <string>

namespace core
{
	namespace lua
	{
		class Stack;
		class Table
		{
		protected:
			friend class Stack;

		private:
			using num = double;
			using str = std::string;

			std::string name;
			Stack* stack = nullptr;

			int nFree = 0;

			Table(Stack* stack, std::string name);

		public:
			~Table();

			num getNumber(const std::string& name);
			str getString(const std::string& name);
			int getInteger(const std::string& name);
			bool getBoolean(const std::string& name);

			num getNumber(int index);
			str getString(int index);
			int getInteger(int index);
			bool getBoolean(int index);

			void goTo(const std::string& name);
			void goTo(int index);
			void goHome();
			void goBack();
		};
	} // lua
} // core

#endif //LUA_TABLE_HPP
