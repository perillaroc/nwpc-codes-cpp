#pragma once

#include <grib_property/grib_property_container.h>
#include <grib_property/number_property.h>

#include <unordered_map>


namespace grib_coder {
class GribTableDatabase;
class GribSection;

class GribMessageHandler final: public GribPropertyContainer {
public:
    explicit GribMessageHandler(std::shared_ptr<GribTableDatabase>& db, bool header_only = false);
    ~GribMessageHandler();

    GribMessageHandler(GribMessageHandler&&) = default;
    GribMessageHandler& operator= (GribMessageHandler&&) = default;

    GribMessageHandler(const GribMessageHandler&) = delete;
    GribMessageHandler& operator= (GribMessageHandler) = delete;

    // parse, dump and pack

    // parse current grib message from file.
    // current pos of file will be changed.
    bool parseFile(std::FILE* file);

    // decode values in section 7 regardless of handler_only flag.
    bool decodeValues();

    // dump grib message into stdout.
    void dump(const DumpConfig& dump_config = DumpConfig{});

    // encode values in section 7
    bool encodeValues();

    // pack message into file.
    bool packFile(std::FILE* file);

    // properties
    void setCount(long count);

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

    GribProperty* getProperty(const std::string& name);

    auto getTableDatabase() const {
        return table_database_;
    }

    // calculate total length of all sections.
    // used for section 0.
    long calculateTotalLength() const;

    double getMissingValue() const {
        return missing_value_;
    }

    void setMissingValue(double value) {
        missing_value_ = value;
    }

private:
    // parse next section 1 - 7. currently section 2 is not supported.
    bool parseNextSection(std::FILE* file);

    auto getSection(int section_number, size_t begin_pos = 0);

    // same as header only flag in GribFileHandler.
    bool header_only_ = false;

    std::vector<std::shared_ptr<GribSection>> section_list_;
    std::shared_ptr<GribTableDatabase> table_database_;

    // message offset in file.
    NumberProperty<uint64_t> offset_;

    // current message count.
    NumberProperty<uint64_t> count_;

    // store message only properties.
    std::unordered_map<std::string, GribProperty*> property_map_;

    double missing_value_ = 9999;
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
