#include <iostream>
#include <string>
#include <chrono>

#include <grib_file_handler.h>

#include <CLI11/CLI11.hpp>
#include <fmt/printf.h>

int list_grib_file(const std::string& file_path) {
    fmt::print("{file_path}\n", fmt::arg("file_path", file_path));
    auto f = std::fopen(file_path.c_str(), "rb");

    //auto start_time = std::chrono::system_clock::now();

    grib_coder::GribFileHandler handler(f, true);
    auto current_index = 0;
    auto message_handler = handler.next();

    while (message_handler) {
        current_index++;
        auto edition = message_handler->getLong("editionNumber");

        // section 1
        auto centre = message_handler->getString("centre");

        //		dataDate
        auto dataDate = message_handler->getString("dataDate");
        auto dataTime = message_handler->getString("dataTime");

        auto dataType = message_handler->getString("typeOfProcessedData");

        // section 3
        //		grid type

        // section 4
        //		typeOfLevel
        auto typeOfLevel = message_handler->getString("typeOfLevel");

        //		level
        auto level = message_handler->getString("level");

        //		stepRange
        auto forecastTime = message_handler->getLong("forecastTime");
        auto indicator_of_unit_of_time_range = message_handler->getLong("indicatorOfUnitOfTimeRange");
        auto stepRange = fmt::format("{forecastTime}", fmt::arg("forecastTime", forecastTime));

        // section 5
        //		packagingType
        auto packing_type = message_handler->getString("packingType");

        auto category = message_handler->getString("parameterCategory");
        auto number = message_handler->getString("parameterNumber");
        fmt::print(
            "{edition} | {centre} | {dataDate} {dataTime} | {dataType} | {category} | {number} | {stepRange} | {typeOfLevel} | {level} | {packing_type} \n",
            fmt::arg("edition", edition),
            fmt::arg("centre", centre),
            fmt::arg("dataDate", dataDate),
            fmt::arg("dataTime", dataTime),
            fmt::arg("dataType", dataType),
            fmt::arg("category", category),
            fmt::arg("number", number),
            fmt::arg("stepRange", stepRange),
            fmt::arg("typeOfLevel", typeOfLevel),
            fmt::arg("level", level),
            fmt::arg("packing_type", packing_type));
        message_handler = handler.next();
    }

    std::fclose(f);

    fmt::print("{count} grib2 messages in {file_path}\n",
               fmt::arg("count", current_index),
               fmt::arg("file_path", file_path));

    return 0;
}


int main(int argc, char** argv) {
    CLI::App app{"nwpc_codes_ls"};

    std::string file_path;
    app.add_option("file_path", file_path);

    CLI11_PARSE(app, argc, argv);

    auto result = list_grib_file(file_path);

    return result;
}
