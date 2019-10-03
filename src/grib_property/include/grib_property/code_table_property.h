#pragma once

#include <grib_property/grib_property.h>
#include <grib_property/grib_table_database.h>


namespace grib_coder {

class CodeTableProperty: public GribProperty {
public:
    void setTableDatabase(std::shared_ptr<GribTableDatabase> db);
    void setTablesVersion(const std::string& version);

    void setLong(long value) override;
    long getLong() override;

    void setDouble(double value) override;
    double getDouble() override;

    void setString(const std::string& value) override;
    std::string getString() override;

    /**
     * \brief get title from table record. If table record is not available, load table using getTableRecord().
     * \return table record title
     */
    auto getTitle();
    auto getAbbreviation();
    auto getUnits();

    auto getValue() const {
        return value_;
    }

    void setCodeTableId(const std::string& code_table_id);
    void setOctetCount(size_t count);

    bool parse(std::vector<std::byte>::const_iterator& iterator, size_t count = 1) override;

    void dump(const DumpConfig& dump_config) override;

    void pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) override;

private:
    std::optional<GribTableRecord> getTableRecord();

    std::string code_table_id_ = "";
    size_t octet_count_ = 1;
    long value_ = 255;

    std::string tables_version_;
    std::shared_ptr<GribTableDatabase> table_database_;
};


} // namespace grib_coder
