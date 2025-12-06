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

			Table(Stack* stack, std::string name);

		public:
			~Table() = default;

			num getNumber(const std::string& name);
			str getString(const std::string& name);
			int getInteger(const std::string& name);
			bool getBoolean(const std::string& name);
		};
	} // lua
} // core

#endif //LUA_TABLE_HPP
