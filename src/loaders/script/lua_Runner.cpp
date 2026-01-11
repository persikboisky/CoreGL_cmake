//
// Created by kisly on 05.12.2025.
//

#include "lua_Runner.hpp"
#include "../../config.hpp"
#include "../../util/Coders.hpp"
#include "../../util/console.hpp"
#include "../../window/Event.hpp"
#include "../../window/Window.hpp"
#include "../Code.hpp"
#include "lua_Stack.hpp"
#include <lua.hpp>
#include <iostream>


namespace core
{
    class luaWindow : public Window
    {
    public:
        luaWindow(int width, int height, const std::string& title, bool resizable, bool vkApi) :
            Window(width, height, title.c_str(), resizable, vkApi)
        {}
    };
}

auto CreateWindow = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    const int width = stack.getInteger(-5);
    const int height = stack.getInteger(-4);
    const std::string title = stack.getString(-3);
    const bool resizable = stack.getBoolean(-2);
    const bool vkApi = stack.getBoolean(-1);
    void* ptr = stack.newUserData(sizeof(core::luaWindow));
    new (ptr) core::luaWindow(width, height, title, resizable, vkApi);
    return 1;
};

auto UpdateWindow = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-1);
    window->update();
    return 0;
};

auto WindowEventClose = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-1);
    stack.pushBoolean(window->event->close());
    return 1;
};

auto WindowSwapBuffers = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-1);
    window->swapBuffers();
    return 0;
};

auto WindowIsGlContext = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-1);
    stack.pushBoolean(window->isGlContext());
    return 1;
};

auto WindowSetGlContext = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-1);
    window->setGlContext();
    return 0;
};

auto WindowSetIcon = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-2);
    std::string path = stack.getString(-1);
    window->setIcon(path.c_str());
    return 0;
};

auto WindowGetWidth = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-1);
    stack.pushInteger(window->getWidth());
    return 1;
};

auto WindowGetHeight = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-1);
    stack.pushInteger(window->getHeight());
    return 1;
};

auto WindowGetAspect = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-1);
    stack.pushNumber(window->getAspect());
    return 1;
};

auto WindowVerticalSynchronization = [](core::lua::State* state) -> int {
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-2);
    bool flag = stack.getBoolean(-1);
    window->VerticalSynchronization(flag);
    return 0;
};

static int WindowSetPos(core::lua::State* state)
{
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-3);
    int posX = stack.getInteger(-2);
    int posY = stack.getInteger(-1);
    window->setPos(posX, posY);
    return 0;
}

static int WindowSetSize(core::lua::State* state)
{
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-3);
    int width = stack.getInteger(-2);
    int height = stack.getInteger(-1);
    window->setSize(width, height);
    return 0;
}

static int WindowFullScreen(core::lua::State* state)
{
    core::lua::FunctionStack stack = core::lua::FunctionStack::create(state);
    auto window = (core::luaWindow*)stack.getUserData(-2);
    bool flag = stack.getBoolean(-1);
    window->fullScreen(flag);
    return 0;
}

namespace core::lua
{
    void Runner::pushCoreGLFunctions(const ImportCoreGLFunctionsInfo &info) const
    {
        if (info.flagWindow)
        {
            stack->pushFunction(CreateWindow, "CoreWindowCreate");
            stack->pushFunction(UpdateWindow, "CoreWindowUpdate");
            stack->pushFunction(WindowEventClose, "CoreWindowEventClose");
            stack->pushFunction(WindowSetGlContext, "CoreWindowSetGlContext");
            stack->pushFunction(WindowSwapBuffers, "coreWindowSwapBuffers");
            stack->pushFunction(WindowIsGlContext, "coreWindowIsGlContext");
            stack->pushFunction(WindowSetGlContext, "coreWindowSetGlContext");
            stack->pushFunction(WindowSetIcon, "coreWindowSetIcon");
            stack->pushFunction(WindowGetWidth, "coreWindowGetWidth");
            stack->pushFunction(WindowGetHeight, "coreWindowGetHeight");
            stack->pushFunction(WindowGetAspect, "coreWindowGetAspect");
            stack->pushFunction(WindowVerticalSynchronization, "coreWindowVerticalSynchronization");
            stack->pushFunction(WindowSetPos, "coreWindowSetPos");
            stack->pushFunction(WindowSetSize, "coreWindowSetSize");
            stack->pushFunction(WindowFullScreen, "coreWindowFullScreen");
        }
    }

	Runner::Runner(const char *code, bool flagDebuInfo)
    {
        this->state = luaL_newstate();
        if (this->state == nullptr)
            throw Coders(NONE_CODERS, "Failed create lua state");
        luaL_openlibs(this->state);

        if (luaL_loadstring(this->state, code) != LUA_OK)
            throw Coders(NONE_CODERS, "Syntax error: " + std::string(lua_tostring(this->state, -1)));

        if (CORE_INFO && flagDebuInfo)
        {
            console::printTime();
            std::cout << "Ok: compile lua script" << std::endl;
        }

        this->stack = new lua::Stack(this->state);
    }

	Runner::~Runner()
	{
		delete this->stack;
		lua_close(this->state);
	}

	Runner Runner::compileFromFile(const char *path, bool flagDebuInfo)
	{
		return Runner(Code::loadStr(path, flagDebuInfo).c_str(), flagDebuInfo);
	}

	Runner Runner::compileFromCode(const char *code, bool flagDebuInfo)
	{
		return Runner(code, flagDebuInfo);
	}

	Runner *Runner::ptrCompileFromFile(const char *path, bool flagDebuInfo)
	{
		return new Runner(Code::loadStr(path, flagDebuInfo).c_str(), flagDebuInfo);
	}

	Runner *Runner::ptrCompileFromCode(const char *code, bool flagDebuInfo)
	{
		return new Runner(code, flagDebuInfo);
	}

	void Runner::run() const
    {
		if (lua_pcall(this->state, 0, 0, 0) != LUA_OK)
			throw Coders(NONE_CODERS,
			    "[Runner::run()] Runtime error: " + std::string(lua_tostring(this->state, -1)));
	}

	double Runner::nRun() const
    {
		if (lua_pcall(this->state, 0, 1, 0) == LUA_OK)
		{
			double lua_result = lua_tonumber(this->state, -1);
			lua_pop(this->state, 1);
			return lua_result;
		}
		else
			throw Coders(NONE_CODERS,
			    "[Runner::nRun()] Runtime error: " + std::string(lua_tostring(this->state, -1)));
	}

	int Runner::iRun() const
    {
        if (lua_pcall(this->state, 0, 1, 0) == LUA_OK)
        {
            int lua_result = lua_tointeger(this->state, -1);
            lua_pop(this->state, 1);
            return lua_result;
        }
        throw Coders(NONE_CODERS,
            "[Runner::iRun()] Runtime error: " + std::string(lua_tostring(this->state, -1)));
    }

	std::string Runner::strRun() const
    {
        if (lua_pcall(this->state, 0, 1, 0) == LUA_OK)
        {
            std::string lua_result = lua_tostring(this->state, -1);
            lua_pop(this->state, 1);
            return lua_result;
        }
        throw Coders(NONE_CODERS,
            "[Runner::strRun()] Runtime error: " + std::string(lua_tostring(this->state, -1)));
    }

	bool Runner::bRun() const
    {
        if (lua_pcall(this->state, 0, 1, 0) == LUA_OK)
        {
            bool lua_result = lua_toboolean(this->state, -1);
            lua_pop(this->state, 1);
            return lua_result;
        }
        throw Coders(NONE_CODERS,
            "[Runner::bRun()] Runtime error: " + std::string(lua_tostring(this->state, -1)));
    }

	void Runner::operator=(const Runner& runner)
	{
		lua_close(state);
		this->state = runner.state;
		this->stack = runner.stack;
	}
} // namespace core::lua
