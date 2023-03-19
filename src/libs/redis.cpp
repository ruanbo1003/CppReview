//
// Created by 阮波 on 2023/3/19.
//

#include <hiredis/hiredis.h>
#include "comm/log.h"


void redis_test() {
    redisContext *c = redisConnect("localhost", 6379);
    if (c != NULL && c->err) {
        Log("connect error:%s", c->errstr);
        // handle error
    } else {
        Log("connect to redis");
    }
}
