#include "codes_dump.h"

#include <grib_coder/grib_file_handler.h>
#include <fmt/format.h>

namespace grib_tool {

int dump_grib_file(const std::string& file_path, const std::vector<Condition>& conditions) {
    fmt::print("{file_path}\n", fmt::arg("file_path", file_path));
    auto f = std::fopen(file_path.c_str(), "rb");

    //auto start_time = std::chrono::system_clock::now();

    grib_coder::GribFileHandler handler(f, false);
    auto current_index = 0;
    auto message_selected = 0;
    auto message_handler = handler.next();

    while (message_handler) {
        current_index++;
        if (!check_conditions(message_handler, conditions)) {
            message_handler = handler.next();
            continue;
        }

        message_selected++;
        message_handler->decodeValues();
        message_handler->dump();
        message_handler = handler.next();
    }

    std::fclose(f);

    fmt::print("{message_selected} of {count} grib2 messages in {file_path}\n",
               fmt::arg("message_selected", message_selected),
               fmt::arg("count", current_index),
               fmt::arg("file_path", file_path));

    return 0;
}


} // namespace grib_tool
