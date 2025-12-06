//
// Created by kisly on 05.12.2025.
//

#ifndef LUA_RUNNER_HPP
#define LUA_RUNNER_HPP

#include <string>

struct lua_State;

namespace core::lua
{
	class Runner
	{
	protected:
		friend class Stack;

	private:
		lua_State *state = nullptr;

		Runner(const char *code, bool flagDebuInfo);

	public:
		class Stack* stack = nullptr;

		~Runner();

		static Runner compileFromFile(const char *path, bool flagDebuInfo = true);
		static Runner compileFromCode(const char *code, bool flagDebuInfo = true);
		static Runner *ptrCompileFromFile(const char *path, bool flagDebuInfo = true);
		static Runner *ptrCompileFromCode(const char *code, bool flagDebuInfo = true);

		void run();

		double nRun();
		int iRun();
		std::string strRun();
		bool bRun();
	};
}

#endif // LUA_RUNNER_HPP
