#pragma once

#include "grib_section.h"
#include <grib_property/grib_table_database.h>
#include <grib_property/grib_property_container.h>
#include <grib_property/number_property.h>

namespace grib_coder {

class GribMessageHandler : public GribPropertyContainer {
public:
    GribMessageHandler(std::shared_ptr<GribTableDatabase> &db, bool header_only = false);
    ~GribMessageHandler();

    void setCount(long count);

    bool parseFile(std::FILE* file);

    void setLong(const std::string& key, long value) override;
    long getLong(const std::string& key) override;

    void setDouble(const std::string& key, double value) override;
    double getDouble(const std::string& key) override;

    void setString(const std::string& key, const std::string& value) override;
    std::string getString(const std::string& key) override;

    template<typename T> T get(const std::string& key);

private:
    bool parseNextSection(std::FILE* file);

    std::shared_ptr<GribSection> getSection(int section_number, size_t begin_pos = 0);

    GribProperty* getProperty(const std::string& name);

    bool header_only_ = false;

    std::vector<std::shared_ptr<GribSection>> section_list_;
    std::shared_ptr<GribTableDatabase> table_database_;

    NumberProperty<uint64_t> offset_;
    NumberProperty<uint64_t> count_;

    std::unordered_map<std::string, GribProperty*> property_map_;
};

template<typename T>
inline T GribMessageHandler::get(const std::string& key)
{
    throw std::runtime_error("not implemented");
}

template<>
inline long GribMessageHandler::get(const std::string& key)
{
    return getLong(key);
}

template<>
inline double GribMessageHandler::get(const std::string& key)
{
    return getDouble(key);
}

template<>
inline std::string GribMessageHandler::get(const std::string& key)
{
    return getString(key);
}

template<>
inline std::vector<double> GribMessageHandler::get(const std::string& key)
{
    return getDoubleArray(key);
}

} // namespace grib_coder
