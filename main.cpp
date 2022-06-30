#include "date/date.h"
#include <chrono>
#include <sstream>
#include <iostream>


int main(int /* argc */, char * argv[])
{
    auto is = std::istringstream(argv[1]);
    auto tp = date::sys_time<std::chrono::milliseconds>();
    auto of = std::chrono::minutes();

    is >> date::parse("", tp, of);

    std::cout << argv[1] << ":\n    " << tp.time_since_epoch().count() << "    " << of.count() << "\n";
}
