# CMakeLists.txt для сборки Lua 5.4
cmake_minimum_required(VERSION 3.10)
project(lua VERSION 5.4.4 LANGUAGES C)

set(LUA_SOURCES
    src/lapi.c src/lcode.c src/lctype.c src/ldebug.c
    src/ldo.c src/ldump.c src/lfunc.c src/lgc.c
    src/llex.c src/lmem.c src/lobject.c src/lopcodes.c
    src/lparser.c src/lstate.c src/lstring.c src/ltable.c
    src/ltm.c src/lundump.c src/lvm.c src/lzio.c
    src/lauxlib.c src/lbaselib.c src/lcorolib.c
    src/ldblib.c src/liolib.c src/lmathlib.c
    src/loadlib.c src/loslib.c src/lstrlib.c
    src/ltablib.c src/lutf8lib.c src/linit.c
)

add_library(lua STATIC ${LUA_SOURCES})
target_include_directories(lua PUBLIC src)

add_executable(lua_exe src/lua.c)
target_link_libraries(lua_exe lua)
set_target_properties(lua_exe PROPERTIES OUTPUT_NAME lua)

# Для luac
add_executable(luac_exe src/luac.c)
target_link_libraries(luac_exe lua)
set_target_properties(luac_exe PROPERTIES OUTPUT_NAME luac)