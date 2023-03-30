//
// Created by 阮波 on 2023/3/30.
//

#include <unordered_map>
#include "StudentTemplateHash.h"
#include "comm/log.h"


namespace templates {


void template_with_hash() {
    std::unordered_map<StudentTemplateHash, int> students;
    StudentTemplateHash s1 = {"Tom", 10, 100};
    StudentTemplateHash s2 = {"Jack", 10, 101};
    StudentTemplateHash s3 = {"John", 11, 102};
    students[s1] = 100;
    students[s2] = 101;
    students[s1] = 102;

    for(auto &each: students) {
        Log("%s:%d, %d", each.first.name.c_str(), each.first.age, each.first.score);
    }

}

}  // end of namespace

