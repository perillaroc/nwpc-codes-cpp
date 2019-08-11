#include "code_table_property.h"

#include <iostream>
#include <fmt/format.h>

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
    auto default_value = fmt::format("{}", value_);

    auto record_result = getTableRecord();
    if (!record_result.has_value()) {
        return default_value;
    }

	auto record = record_result.value();

    if (record.abbreviation_ == RecordUnknownValue) {
        return record.title_;
    }
    else {
        return record.abbreviation_;
    }

	return record.title_;
}

std::string CodeTableProperty::getTitle()
{
    auto default_value = fmt::format("{}", value_);

    auto record_result = getTableRecord();
    if (!record_result.has_value()) {
        return default_value;
    }
    auto record = record_result.value();

    return record.title_;
}

std::string CodeTableProperty::getAbbreviation()
{
    auto default_value = fmt::format("{}", value_);

    auto record_result = getTableRecord();
    if (!record_result.has_value()) {
        return default_value;
    }
    auto record = record_result.value();

    return record.abbreviation_;
}

std::string CodeTableProperty::getUnits()
{
    auto default_value = fmt::format("{}", value_);

    auto record_result = getTableRecord();
    if (!record_result.has_value()) {
        return default_value;
    }
    auto record = record_result.value();

    return record.units_;
}

void CodeTableProperty::setCodeTableId(const std::string &code_table_id) {
    code_table_id_ = code_table_id;
}

void CodeTableProperty::setOctetCount(size_t count) {
    octet_count_ = count;
}

std::optional<GribTableRecord> CodeTableProperty::getTableRecord()
{
    auto table = table_database_->getGribTable(tables_version_, code_table_id_);
    if (!table) {
        std::cerr << "grib table (" << code_table_id_ << ") is not found." << std::endl;
        return std::optional<GribTableRecord>();
    }

    auto record = table->getRecord(value_);
    return record;
}

} // namespace GribCoder