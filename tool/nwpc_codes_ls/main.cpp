#include "codes_ls.h"

#include <CLI11/CLI11.hpp>
#include <fmt/format.h>


int main(int argc, char** argv) {
    CLI::App app{"nwpc_codes_ls"};

    std::string file_path;
    app.add_option("file_path", file_path, "grib file path")
       ->check(CLI::ExistingFile);
    std::string conditions_option;
    app.add_option("-w", conditions_option, "filter condition");

    CLI11_PARSE(app, argc, argv);

    if (file_path.empty()) {
        fmt::print("{}\n", app.help());
        return 0;
    }

    const auto conditions = grib_tool::parse_conditions(conditions_option);

    const auto result = grib_tool::list_grib_file(file_path, conditions);

    return result;
}
