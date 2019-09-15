#pragma once

#include <grib_coder/grib_section.h>
#include <grib_property/grib_property_container.h>
#include <grib_property/number_property.h>

namespace grib_coder {
class GribTableDatabase;

class GribMessageHandler : public GribPropertyContainer {
public:
    GribMessageHandler(std::shared_ptr<GribTableDatabase>& db, bool header_only = false);
    ~GribMessageHandler() = default;

    void setCount(long count);

    bool parseFile(std::FILE* file);
    bool decodeValues();

    void setLong(const std::string& key, long value) override;
    long getLong(const std::string& key) override;

    void setDouble(const std::string& key, double value) override;
    double getDouble(const std::string& key) override;

    void setString(const std::string& key, const std::string& value) override;
    std::string getString(const std::string& key) override;

    // NOTE: need to optimization
    bool hasProperty(const std::string& key) override;

    template <typename T>
    T get(const std::string& key);

    void dump(const DumpConfig& dump_config = DumpConfig{});

    GribProperty* getProperty(const std::string& name);

    auto getTableDatabase() const {
        return table_database_;
    }

private:
    bool parseNextSection(std::FILE* file);

    auto getSection(int section_number, size_t begin_pos = 0);

    bool header_only_ = false;

    std::vector<std::shared_ptr<GribSection>> section_list_;
    std::shared_ptr<GribTableDatabase> table_database_;

    NumberProperty<uint64_t> offset_;
    NumberProperty<uint64_t> count_;

    std::unordered_map<std::string, GribProperty*> property_map_;
};

template <typename T>
T GribMessageHandler::get(const std::string& key) {
    throw std::runtime_error("not implemented");
}

template <>
inline long GribMessageHandler::get(const std::string& key) {
    return getLong(key);
}

template <>
inline double GribMessageHandler::get(const std::string& key) {
    return getDouble(key);
}

template <>
inline std::string GribMessageHandler::get(const std::string& key) {
    return getString(key);
}

template <>
inline std::vector<double> GribMessageHandler::get(const std::string& key) {
    return getDoubleArray(key);
}

} // namespace grib_coder
