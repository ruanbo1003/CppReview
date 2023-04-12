#include <iostream>
#include <unistd.h>
#include "main.h"


int main() {
    entry();

    std::cout << std::endl << "end of main[" << getpid() << "]" << std::endl;

    return 0;
}
