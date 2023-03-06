//
// Created by 阮波 on 2023/3/6.
//

#include "comm/log.h"
#include <utility>
#include <vector>


namespace cpp14 {
    class stream {
    private:
        int _flags = 0;

    public:
        int flags() const {
            return 0;
        }

        int flags(int new_flag) {
            return std::exchange(_flags, new_flag);
        }
    };

    // https://en.cppreference.com/w/cpp/utility/exchange
    void exchange_test() {
        {
            std::vector<int> v1 = {1, 2, 3};
            std::vector<int> v2 = {7, 8};
            auto ret = std::exchange(v1, v2);
            log_vec(v1, "v1");  // 7 8
            log_vec(v2, "v2");  // 7 8
            log_vec(ret, "ret");  // 1 2 3
        }

    }
}