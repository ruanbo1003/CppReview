//
// Created by 阮波 on 2023/1/13.
//

#include <iostream>
#include <string>
#include <map>
#include "comm/log.h"

namespace stl {

class MapItem {
private:
    int _id;
    std::string _name;

public:
    MapItem(): _id(0), _name("") {
        Log("MapItem()");
    }
    MapItem(int id, std::string name): _id(id), _name(name) {
        Log("MapItem(int, std::string)");
    }
    MapItem(const MapItem& rhs) {
        _id = rhs._id;
        _name = rhs._name;
        Log("MapItem(const MapItem& rhs)");
    }
    MapItem& operator = (const MapItem& other) {
        _id = other._id;
        _name = other._name;
        Log("MapItem& operator = (const MapItem& other)");
        return *this;
    }
    ~MapItem() {
        Log("~MapItem()");
    }

public:
    friend std::ostream& operator << (std::ostream& os, const MapItem& item);
};

std::ostream& operator << (std::ostream& os, const MapItem& item) {
//    os << "<" << item._id << ",\"" << item._name << "\">" << std::endl;
}


void map_test() {
    MapItem item;
    std::cout << item;

//    std::string name = "Tom";
//    std::cout << "name:" << name << std::endl;

//    MapItem item2(1, std::string(""));
//    MapItem item2(1, name);
//    std::cout << item2;
}

}  // end of namespace
