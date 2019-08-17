#pragma once

#include "grib_property.h"
#include "grib_table_database.h"

namespace grib_coder {

class CodeTableProperty: public GribProperty {
public:
    CodeTableProperty();
    ~CodeTableProperty();

	void setTableDatabase(std::shared_ptr<GribTableDatabase> db);
	void setTablesVersion(const std::string& version);

    void setLong(long value) override;
    long getLong() override;

    void setDouble(double value) override;
    double getDouble() override;

    void setString(const std::string &value) override;
    std::string getString() override;

    std::string getTitle();
    std::string getAbbreviation();
    std::string getUnits();

    void setCodeTableId(const std::string &code_table_id);
    void setOctetCount(size_t count);

private:
    std::optional<GribTableRecord> getTableRecord();

    std::string code_table_id_ = "";
    size_t octet_count_ = 1;
    long value_ = 255;

	std::string tables_version_;
	std::shared_ptr<GribTableDatabase> table_database_;
};


} // namespace grib_coder
