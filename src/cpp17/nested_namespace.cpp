//
// Created by 阮波 on 2023/3/7.
//

#include "comm/log.h"


namespace cpp17 {

namespace ns1::ns2 {
void display() {
    cout << "ns1::ns2::display()" << endl;
}
}

namespace ns3 {
    namespace ns4 {
        void display() {
            cout << "ns3::ns4::display()" << endl;
        }
    }
}

void namespace_test() {
    ns1::ns2::display();

    ns3::ns4::display();
}

}