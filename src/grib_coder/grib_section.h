#pragma once

#include <grib_property/grib_property.h>
#include <grib_property/number_property.h>
#include <grib_property/grib_component.h>

#include <vector>
#include <unordered_map>
#include <cstdio>

namespace grib_coder {

class GribSection : public GribComponent {
public:
    explicit GribSection(int section_number);
    GribSection(int section_number, long section_length);

    virtual ~GribSection() = default;

    void setLong(const std::string& key, long value) override;
    long getLong(const std::string& key) override;

    void setDouble(const std::string& key, double value) override;
    double getDouble(const std::string& key) override;

    void setString(const std::string& key, const std::string& value) override;
    std::string getString(const std::string& key) override;

    void setDoubleArray(const std::string& key, std::vector<double>& values) override;
    std::vector<double> getDoubleArray(const std::string& key) override;

    bool hasProperty(const std::string& key) override;

    void setSectionLength(long length);
    long getSectionLength() const;

    int getSectionNumber() const;

    virtual bool parseFile(std::FILE* file, bool header_only = false) = 0;

    bool decode(GribPropertyContainer* container) override;

    GribProperty* getProperty(const std::string& name);

    void registerProperty(const std::string& name, GribProperty* property);

protected:
    std::unordered_map<std::string, GribProperty*> property_map_;

    NumberProperty<int> section_number_;
    NumberProperty<uint64_t> section_length_;

    std::vector<std::unique_ptr<GribComponent>> components_;
};

GribProperty* get_property_from_section_list(
    const std::string& name,
    std::vector<std::shared_ptr<GribSection>>& section_list);

} // namespace grib_coder
