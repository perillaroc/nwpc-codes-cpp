#pragma once
#include <string>
#include <vector>
#include <memory>

namespace grib_coder {
class GribMessageHandler;
} // grib_coder

namespace grib_tool {

enum class property_type {
    Unknown,
    Long,
    Double,
    String,
};

struct PropertyItem {
    std::string name;
    property_type type;
};

struct Condition {
    std::string property_name;
    property_type value_type = property_type::String;
    std::string value;
};

std::vector<Condition> parse_conditions(const std::string& condition);

bool check_conditions(
    std::unique_ptr<grib_coder::GribMessageHandler>& message_handler,
    const std::vector<Condition>& conditions);
} // namespace grib_tool
