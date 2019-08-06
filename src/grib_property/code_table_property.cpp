#include "code_table_property.h"

#include <iostream>
#include <sstream>

namespace GribCoder{

CodeTableProperty::CodeTableProperty() {

}

CodeTableProperty::~CodeTableProperty() {

}

void CodeTableProperty::setTableDatabase(std::shared_ptr<GribTableDatabase> db)
{
	table_database_ = db;
}

void CodeTableProperty::setTablesVersion(const std::string& version)
{
	tables_version_ = version;
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
	std::stringstream ss;
	ss << value_;
	auto default_value = ss.str();

	auto table = table_database_->getGribTable(tables_version_, code_table_id_);
	if (!table) {
		std::cerr << "grib table (" << code_table_id_ << ") is not found." << std::endl;
		return default_value;
	}

	auto record_result = table->getRecord(value_);
	if (!record_result.has_value()) {
		return default_value;
	}
	auto record = record_result.value();
	return record.description_;
}

void CodeTableProperty::setCodeTableId(const std::string &code_table_id) {
    code_table_id_ = code_table_id;
}

void CodeTableProperty::setOctetCount(size_t count) {
    octet_count_ = count;
}

} // namespace GribCoder