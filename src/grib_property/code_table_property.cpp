#include "code_table_property.h"

namespace GribCoder{

CodeTableProperty::CodeTableProperty() {

}

CodeTableProperty::~CodeTableProperty() {

}

void CodeTableProperty::setLong(long value) {
    value_ = value;
}

long CodeTableProperty::getLong() {
    return value_;
}

void CodeTableProperty::setDouble(double value) {
    value_ = static_cast<long>(value);
}

double CodeTableProperty::getDouble() {
    return value_;
}

void CodeTableProperty::setString(const std::string &value) {

}

std::string CodeTableProperty::getString() {
    return std::string();
}

void CodeTableProperty::setCodeTableId(const std::string &code_table_id) {
    code_table_id_ = code_table_id;
}

} // namespace GribCoder