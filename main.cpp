#include "date/date.h"
#include <chrono>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <iostream>


using sys_ms = date::sys_time<std::chrono::milliseconds>;
using chr_m = std::chrono::minutes;

auto parse(std::string const & time_point) -> std::pair<sys_ms, chr_m>
{
    auto is = std::istringstream(time_point);
    auto tp = date::sys_time<std::chrono::milliseconds>();
    auto of = std::chrono::minutes();

    is >> date::parse("", tp, of);
    if (is.fail())
    {
        throw std::runtime_error("cannot parse '" + time_point + "'");
    }

    return {tp, of};
}

int main(int /* argc */, char * argv[])
{
    auto const [tp, of] = parse(argv[1]);

    std::cout << argv[1] << ":\n    " << tp.time_since_epoch().count() << "    " << of.count() << "\n";
}
