#pragma once
#include <grib_property/grib_component.h>

namespace grib_coder {

class PropertyComponent final: public GribComponent {
public:
    PropertyComponent(int byte_count, std::string property_name, GribProperty* property);

    void setByteCount(const int byte_count);
    int getByteCount() const override {
        return byte_count_;
    }

    GribProperty* getProperty();
    std::string getPropertyName() const;

    // parse binary bytes read from grib message
    bool parse(std::vector<std::byte>::const_iterator& iterator) override;

    bool decode(GribPropertyContainer* container) override;

    void dump(std::size_t start_octec, const DumpConfig& dump_config = DumpConfig{}) override;

private:
    int byte_count_ = 1;
    std::string property_name_;
    GribProperty* property_ = nullptr;
};


} // namespace grib_coder