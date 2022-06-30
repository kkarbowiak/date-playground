#include "date/date.h"
#include <chrono>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstdlib>


using sys_ms = date::sys_time<std::chrono::milliseconds>;
using chr_m = std::chrono::minutes;

auto parse(std::string const & time_point) -> std::pair<sys_ms, chr_m>
{
    auto is = std::istringstream(time_point);
    auto tp = date::sys_time<std::chrono::milliseconds>();
    auto of = std::chrono::minutes();

    is >> date::parse("%FT%T%Ez", tp, of);
    if (is.fail())
    {
        throw std::runtime_error("cannot parse '" + time_point + "'");
    }

    return {tp, of};
}

int main(int /* argc */, char * argv[])
{
    try
    {
        auto const arg = std::string(argv[1]);

        auto const [tp, of] = parse(arg);

        std::cout << arg << ":\n    " << tp.time_since_epoch().count() << "    " << of.count() << "\n";
    }
    catch (std::exception const & e)
    {
        std::cout << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
