#include "date/date.h"
#include <chrono>
#include <string>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstdlib>


using sys_ms = date::sys_time<std::chrono::milliseconds>;
using loc_ms = date::local_time<std::chrono::milliseconds>;
using chr_m = std::chrono::minutes;

auto parse_with_format(std::string const & time_point, std::string const & format) -> std::pair<loc_ms, chr_m>
{
    auto is = std::istringstream(time_point);
    auto tp = loc_ms();
    auto of = chr_m();

    is >> date::parse(format.c_str(), tp, of);
    if (is.fail())
    {
        throw std::runtime_error("cannot parse '" + time_point + "' with format '" + format + "'");
    }

    return {tp, of};
}

auto parse(std::string const & time_point) -> std::pair<loc_ms, chr_m>
{
    return parse_with_format(time_point, "%FT%T%Ez");
}

auto format(loc_ms time_point, chr_m offset) -> std::string
{
    auto of_seconds = std::chrono::seconds(offset);
    auto os = std::ostringstream();
    date::to_stream(os, "%FT%T%Ez", time_point, nullptr, &of_seconds);
    if (os.fail())
    {
        throw std::runtime_error("cannot format");
    }

    return os.str();
}

auto parse_abbr(std::string const & time_point) -> std::pair<loc_ms, std::string>
{
    auto is = std::istringstream(time_point);
    auto tp = loc_ms();
    auto ab = std::string();

    is >> date::parse("%FT%T%Z", tp, ab);
    if (is.fail())
    {
        throw std::runtime_error("cannot parse '" + time_point + "'");
    }

    return {tp, ab};
}

auto format_abbr(loc_ms time_point, std::string const & abbr) -> std::string
{
    auto os = std::ostringstream();
    date::to_stream(os, "%FT%T%Z", time_point, &abbr, nullptr);
    if (os.fail())
    {
        throw std::runtime_error("cannot format");
    }

    return os.str();
}

int main(int /* argc */, char * argv[])
{
    try
    {
        auto const arg = std::string(argv[1]);

        auto const [tp, ab] = parse_abbr(arg);
        auto const formatted = format_abbr(tp, ab);
        std::cout
            << arg << ":\n    "
            << tp.time_since_epoch().count() << "    " << ab << "\n    "
            << formatted << '\n';
        // auto const [tp, of] = parse(arg);
        // auto const formatted = format(tp, of);

        // std::cout
        //     << arg << ":\n    "
        //     << tp.time_since_epoch().count() << "    " << of.count() << "\n    "
        //     << formatted << '\n';
    }
    catch (std::exception const & e)
    {
        std::cout << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
