#pragma once
#include <string>
#include <vector>

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

int list_grib_file(const std::string& file_path, const std::vector<Condition>& conditions);

std::vector<Condition> parse_conditions(const std::string& condition);

} // namespace grib_tool