#include <string>

#include <grib_coder/grib_file_handler.h>

int main() {
    const std::string grib_file_path{ "./dist/data/t.850hpa.000.grb2" };
    const std::string output_grib_file_path{ "./dist/output.grb2" };
    //const std::string grib_file_path{ "./dist/data/39.grb2" };

    auto f = std::fopen(grib_file_path.c_str(), "rb");

    grib_coder::GribFileHandler handler(f);

    auto message_handler = handler.next();

    message_handler->dump();

    std::fclose(f);

    auto output_file = std::fopen(output_grib_file_path.c_str(), "wb");
    message_handler->packFile(output_file);

    std::fclose(output_file);

    return 0;
}

