#include <string>

#include <grib_coder/grib_file_handler.h>

int main() {
    const std::string grib_file_path{"./dist/data/t.850hpa.000.grb2"};

    auto f = std::fopen(grib_file_path.c_str(), "rb");

    grib_coder::GribFileHandler handler(f);

    auto message_handler = handler.next();

    auto discipline = message_handler->get<long>("discipline");
    auto ni = message_handler->get<long>("ni");
    auto nj = message_handler->get<std::string>("nj");
    auto category = message_handler->get<std::string>("parameterCategory");

    message_handler->dump();

    std::fclose(f);

    return 0;
}
