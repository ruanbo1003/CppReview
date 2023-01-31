//
// Created by 阮波 on 2023/1/26.
//

#include <unordered_map>
#include <unordered_set>
#include "comm/log.h"


/*
 *
 *  unordered_map
 *  unordered_multimap
 *
 *  unordered_set
 *  unordered_multiset
 */

namespace cpp11 {

static void unordered_map_test() {
    Log("\nunordered map test");

    std::unordered_map<int, std::string> m;
    m.insert(std::pair(1, std::string("a")));
    m[2] = std::string("b");
    m[3] = "c";

    for(auto& item : m) {
        Log("m[%d]=%s", item.first, item.second.c_str());
    }
}

static void unordered_multimap_test() {
    Log("unordered_multimap test");

    std::unordered_multimap<int, std::string> mm;
    mm.insert(std::pair(1, "a"));
    mm.insert(std::pair(2, "b"));
    mm.insert(std::pair(3, "c"));
    mm.insert(std::pair(4, "d"));

    mm.insert(std::make_pair(1, "aa"));
    mm.insert(std::make_pair(2, "bb"));
    mm.insert(std::make_pair(3, "cc"));
    mm.insert(std::make_pair(4, "dd"));

    for(auto & each : mm) {
        Log("mm[%d]=%s", each.first, each.second.c_str());
    }

}

static void unordered_set_test() {
    Log("unordered set test");
    {
        std::unordered_set<int> s;
        s.insert(1);
        s.insert(1);
        s.insert(2);
        s.insert(3);
        s.insert(0);

        for(auto& each : s) {
            LogLine("%d ", each);
        }  // 0 3 2 1
    }

    Log("\n\nunordered_multiset test");
    {
        std::unordered_multiset<int> ms;
        ms.insert(1);
        ms.insert(1);
        ms.insert(2);
        ms.insert(3);
        ms.insert(0);

        for(auto& each : ms) {
            LogLine("%d ", each);
        }  // 0 3 2 1 1

        Log("\n\nunordered_multiset find");
        auto f_begin = ms.find(1);
        if(f_begin != ms.end()) {
            // found
            Log("found")
        } else {
            Log("not found");
        }
    }
}

void unordered_container_test() {
//    unordered_map_test();

//    unordered_multimap_test();

    unordered_set_test();
}

}  // end of namespace
