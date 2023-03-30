//
// Created by 阮波 on 2023/3/30.
//

#ifndef CPPREVIEW_STUDENTTEMPLATEHASH_H
#define CPPREVIEW_STUDENTTEMPLATEHASH_H

#include <string>
#include <functional>


namespace templates {

class StudentTemplateHash {
public:
    std::string name;
    int age = 0;
    int score = 0;

public:
    bool operator == (const StudentTemplateHash& obj) const {
        return this->name == obj.name;
    }
};

}

namespace std {
template<>
struct hash<templates::StudentTemplateHash> {
public:
    size_t operator()(const templates::StudentTemplateHash& key) const {
        return hash<std::string>()(key.name);
    }
};

}


#endif //CPPREVIEW_STUDENTTEMPLATEHASH_H
