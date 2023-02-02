//
// Created by 阮波 on 2023/2/1.
//
#include <string>
#include <iostream>
#include "comm/log.h"


namespace cpp11 {

static void string_literal_test();


void literal_test() {
    string_literal_test();
}

static void string_literal_test() {
    Log("raw-string-literal: the GOD");
    {
        std::string fo_zu = R"(
                            _ooOoo_
                           o8888888o
                           88" . "88
                           (| -_- |)
                            O\ = /O
                        ____/`---'\____
                      .   ' \\| |// `.
                       / \\||| : |||// \
                     / _||||| -:- |||||- \
                       | | \\\ - /// | |
                     | \_| ''\---/'' | |
                      \ .-\__ `-` ___/-. /
                   ___`. .' /--.--\ `. . __
                ."" '< `.___\_<|>_/___.' >'"".
               | | : `- \`.;`\ _ /`;.`/ - ` : | |
                 \ \ `-. \_ __\ /__ _/ .-` / /
         ======`-.____`-.___\_____/___.-`____.-'======
                            `=---='
        )";
        Log("%s", fo_zu.c_str());
    }

    Log("compare normal string and string literal");
    {
        // in normal string, there are many escape chars, like \n \r \t
        std::string str_1 = "hello\n\n world";
        Log("str_1:%s", str_1.c_str());

        // in string literal, '\n' is the sub-string like 'hello', not escape char.
        std::string str_2 = R"(hello\n world)";
        // the terminal output is: hello\n world. no newline.
        Log("str_2:%s", str_2.c_str());
    }

    Log("\nraw-string-literal");
    {
        // By default, raw-string is identified by 'R',
        // and start with '(', end with ')'
        std::string str_1 = R"(this is a raw-string-1\n\t)";
        Log("str_1:%s", str_1.c_str());  // this is a raw-string-1\n\t

        // we can customize our own delimiter: R"delimiter()delimiter".
        // The raw-string is identified by 'R',
        // and start with 'delimiter(', end with ')delimiter'.
        std::string str_2 = R"abc_xyz(this is a raw-string-2\n\t)abc_xyz";
        Log("str_2:%s", str_2.c_str());  // this is a raw-string-2\n\t
    }

    Log("raw-string of u8, u, U, L");
    {
        // u8: const char* , UTF-8 string literal.
        std::string str_utf8 = u8"Hello, 中国.";
        Log("utf8:%s", str_utf8.c_str());

        // u: const char16_t* , UTF-16 string literal.
        auto str_utf16 = u"string-utf16:你好，中国.";
        // 'std::cout' has no special << overload for const char16_t*, so the output is not as expected.
        std::cout << str_utf16 << std::endl;

        // U: const char32_t* , UTF-32 string literal.
        auto str_utf32 = U"string-utf32:你好，世界.";
        // 'std::cout' has no special << overload for const char32_t*, so the output is not as expected.
        std::cout << str_utf32 << std::endl;

        // L: const wchar_t* , wide string literal.
        auto str_wide = L"string-wide";
        std::wcout << str_wide << std::endl;
    }

}

}  // end of namespace
