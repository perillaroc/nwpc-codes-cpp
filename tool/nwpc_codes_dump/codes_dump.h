#pragma once
#include "../tool_util/condition.h"

namespace grib_tool {
int dump_grib_file(const std::string& file_path, const std::vector<Condition>& conditions);
} // namespace grib_tool
