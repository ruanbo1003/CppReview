//
// Created by 阮波 on 2023/1/31.
//

#include <sys/resource.h>
#include "comm/log.h"

namespace code_analysis {

static void enable_core_dump_when_crash() {
    struct rlimit core_limit;
    core_limit.rlim_cur = RLIM_INFINITY;
    core_limit.rlim_max = RLIM_INFINITY;

    auto set_ret = setrlimit(RLIMIT_CORE, &core_limit);
    if(set_ret < 0) {
        Log("setrlimit failed:%d", errno);
    } else {
        Log("enable core-dump success");
    }
}

void core_dump_test() {
    enable_core_dump_when_crash();

    Log("generate a crash");
    {
        int *array = new int[10];
        array[1] = 100;
        delete [] array;

        Log("array[11]:%d", array[11]);
    }

    Log("generate a crash 2");
    {
        int *p = 0;
        *p = 7;
        Log("*p:%d", *p);
    }
}

} // end of namespace