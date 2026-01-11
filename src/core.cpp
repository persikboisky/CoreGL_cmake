//
// Created by kisly on 13.07.2025.
//

#include "../include/core/core.hpp"
#include "config.hpp"
#include <GLFW/glfw3.h>
#include <termcolor.hpp>
#include <toml++/toml.hpp>
#include <iostream>
#include <format>

using namespace std::literals;

namespace core::Core
{
    void Init()
    {
        int code = glfwInit();
        if (code == GLFW_FALSE)
        {
            throw core::Coders(0);
        }

        if (CORE_INFO)
        {
            int major;
            int minor;
            int rev;
            glfwGetVersion(&major, &minor, &rev);

            console::printTime();
            std::cout << std::format("Ok: init GLFW v{}.{}.{}", major, minor, rev) << std::endl;
        }

        // toml::parse_result config = toml::parse_file( "./res/config.toml" );
        // void* ptr = malloc(sizeof config);
        // memcpy(ptr, &config, sizeof config);
        //
        // // get key-value pairs
        // std::string_view library_name = config["library"]["name"].value_or(""sv);
        // std::string_view library_author = config["library"]["authors"][0].value_or(""sv);
        // int64_t depends_on_cpp_version = config["dependencies"]["cpp"].value_or(0);
        //
        // // modify the data
        // config.insert_or_assign("alternatives", toml::array{
        //     "cpptoml",
        //     "toml11",
        //     "Boost.TOML"
        // });
        //
        // // re-serialize as TOML
        // std::cout << config << "\n";
        //
        // // re-serialize as JSON
        // std::cout << toml::json_formatter{ config } << "\n";
        //
        // // re-serialize as YAML
        // std::cout << toml::yaml_formatter{ config } << "\n";
        //
        // std::cout << "Bytes: " << sizeof config << std::endl;
        //
        // free(ptr);
    }

    void Terminate()
    {
        glfwTerminate();
    }

    double getTime()
    {
        return glfwGetTime();
    }
}