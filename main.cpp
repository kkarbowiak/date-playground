#include "date/date.h"
#include <chrono>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstdlib>


using sys_ms = date::sys_time<std::chrono::milliseconds>;
using loc_ms = date::local_time<std::chrono::milliseconds>;
using chr_m = std::chrono::minutes;

auto parse(std::string const & time_point) -> std::pair<sys_ms, chr_m>
{
    auto is = std::istringstream(time_point);
    auto tp = sys_ms();
    auto of = chr_m();

    is >> date::parse("%FT%T%Ez", tp, of);
    if (is.fail())
    {
        throw std::runtime_error("cannot parse '" + time_point + "'");
    }

    return {tp, of};
}

auto format(sys_ms time_point, chr_m offset) -> std::string
{
    auto tp_seconds = time_point.time_since_epoch();
    auto loc = loc_ms(tp_seconds);
    auto of_seconds = std::chrono::seconds(offset);
    auto os = std::ostringstream();
    date::to_stream(os, "%FT%T%Ez", loc, nullptr, &of_seconds);
    return os.str();
}

int main(int /* argc */, char * argv[])
{
    try
    {
        auto const arg = std::string(argv[1]);

        auto const [tp, of] = parse(arg);

        std::cout
            << arg << ":\n    "
            << tp.time_since_epoch().count() << "    " << of.count() << "\n    "
            << format(tp, of) << '\n';
    }
    catch (std::exception const & e)
    {
        std::cout << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
