#include "condition.h"
#include <grib_coder/grib_message_handler.h>

#include <stdexcept>

namespace grib_tool {

Condition parse_condition(const std::string& condition) {
    const auto pos = condition.find('=');
    if (pos == std::string::npos) {
        throw std::runtime_error("parse condition error");
    }
    const auto name = condition.substr(0, pos);
    const auto value = condition.substr(pos + 1);
    Condition c;
    c.property_name = name;
    c.value = value;
    return c;
}

std::vector<Condition> parse_conditions(const std::string& condition)
{
    auto s{ condition };
    std::vector<Condition> conditions;

    const auto delimiter = ',';

    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        auto token = s.substr(0, pos);
        s.erase(0, pos + 1);
        conditions.emplace_back(parse_condition(token));
    }
    if (!s.empty()) {
        conditions.emplace_back(parse_condition(s));
    }

    return conditions;
}

bool check_conditions(
    std::unique_ptr<grib_coder::GribMessageHandler>& message_handler,
    const std::vector<Condition>& conditions) {
    for (const auto& condition : conditions) {
        auto name = condition.property_name;
        auto value = condition.value;
        auto value_type = condition.value_type;
        auto message_value = message_handler->getString(name);
        if (value != message_value) {
            return false;
        }
    }
    return true;
}
} // namespace grib_tool