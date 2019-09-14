#include "codes_ls.h"

#include <grib_file_handler.h>
#include <fmt/printf.h>

#include <stdexcept>

namespace grib_tool {

int list_grib_file(const std::string& file_path, const std::vector<Condition>& conditions) {
    fmt::print("{file_path}\n", fmt::arg("file_path", file_path));
    auto f = std::fopen(file_path.c_str(), "rb");

    //auto start_time = std::chrono::system_clock::now();

    std::vector<PropertyItem> property_list{
        {"count", property_type::String},
        {"offset", property_type::String},
        {"dataDate", property_type::String},
        {"dataTime", property_type::String},
        {"typeOfProcessedData", property_type::String},
        {"gridType", property_type::String},
        {"parameterCategory", property_type::String},
        {"parameterNumber", property_type::String},
        {"typeOfLevel", property_type::String},
        {"level", property_type::String},
        {"stepRange", property_type::String},
        {"packingType", property_type::String},
    };

    grib_coder::GribFileHandler handler(f, true);
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
        std::vector<std::string> tokens;
        for (const auto& property_item : property_list) {
            const auto property_type = property_item.type;
            const auto property_name = property_item.name;
            switch (property_type) {
            case property_type::Long:
                tokens.emplace_back(fmt::format("{}", message_handler->getLong(property_name)));
                break;
            case property_type::Double:
                tokens.emplace_back(fmt::format("{}", message_handler->getDouble(property_name)));
                break;
            case property_type::String:
            default:
                tokens.emplace_back(fmt::format("{}", message_handler->getString(property_name)));
                break;
            }
        }

        fmt::print("{}\n", fmt::join(tokens, " | "));
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
