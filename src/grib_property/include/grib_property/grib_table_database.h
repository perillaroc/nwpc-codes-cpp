#pragma once
#include <map>
#include <memory>

#include <grib_property/grib_table.h>

namespace grib_coder {

class GribTableDatabase {
public:
    GribTableDatabase();

    std::shared_ptr<GribTable> getGribTable(const std::string& table_version, const std::string& name);

private:
    std::shared_ptr<GribTable> loadGribTable(const std::string& table_version, const std::string& name);

    // table_version.table_id
    std::map<std::string, std::shared_ptr<GribTable>> tables_;
    std::string eccodes_definition_path_;
};


} // namespace grib_coder
