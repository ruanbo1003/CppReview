//
// Created by 阮波 on 2023/3/7.
//
#include "comm/log.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace cpp17 {


void file_system_test() {
    fs::path file_path_1{"data/fs"};
    fs::path file_path_2{"data2"};

    // current path
    {
        auto cur_path = fs::current_path();
        cout << cur_path << endl;
    }

    //
    {
        bool directory_exists = fs::is_directory(file_path_1);
        cout << directory_exists << endl;  // 0
        if(directory_exists) {
            fs::remove(file_path_1);
        }

        // fs::create_directory(): only create a single directory, like: data
        try {
            bool ok = fs::create_directory(file_path_1);
            if(ok) {
                cout << "create directory:" << file_path_1 << " ok" << endl;
            }
        } catch(exception &e) {
            // No such file or directory ["data/fs"] exception
            cout <<"create file_path_1:" << e.what() << " exception" << endl;
        }

        // fs::create_directories(): can create nested directory, like: data/fs/movies
        try {
            bool ok = fs::create_directories(file_path_1);
            if(ok) {
                // ok
                cout << "create " << file_path_1 << " ok" << endl;
            }
        } catch (exception &e) {
            cout <<"create file_path_2:" << e.what() << " exception" << endl;
        }



    }
}

} // end of namespace
