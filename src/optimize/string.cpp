//
// Created by 阮波 on 2023/6/29.
//

#include <iostream>
#include <string_view>
using std::cout, std::endl, std::string;
using std::string_view;


static int32_t g_malloc_count = 0;

void* operator new(size_t size) {
    g_malloc_count += 1;

    return malloc(size);
}

namespace optimize {

void display_str(const string& s) {
    cout << "s:" << s << endl;
}

void display_view_string(const string_view& s) {
    cout << "view s:" << s << endl;
}

void normal() {
    string s1 = "Hello World";

    display_str(s1);

    cout << "g_malloc_count:" << g_malloc_count << endl;
}

void const_string() {
    display_str("Hello");

    cout << "g_malloc_count:" << g_malloc_count << endl;
}

void string_view_sub_string() {
    string s = "Hello World";

    string_view s1(s.c_str(), 5);
    string_view s2(s.c_str()+6, 5);

    display_view_string(s1);
    display_view_string(s2);

    cout << "g_malloc_count:" << g_malloc_count << endl;
}


void string_view_with_const_char_str() {
    const char* name = "Hello World";

    string_view s1(name, 5);
    string_view s2(name+6, 5);

    display_view_string(s1);
    display_view_string(s2);

    cout << "g_malloc_count:" << g_malloc_count << endl;
}


void string_less_malloc() {
    normal();

//    const_string();

//    string_view_sub_string();

//    string_view_with_const_char_str();
}

}  // end of namespace
