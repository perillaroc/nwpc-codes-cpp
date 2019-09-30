#pragma once
#include <grib_property/grib_component.h>

namespace grib_coder {

class PropertyComponent final : public GribComponent {

public:
    PropertyComponent(int byte_count, std::string property_name, GribProperty* property);

    void setByteCount(const int byte_count);

    long getByteCount() const override {
        return byte_count_;
    }

    GribProperty* getProperty();
    std::string getPropertyName() const;

    bool parse(std::vector<std::byte>::const_iterator& iterator) override;

    bool decode(GribMessageHandler* handler) override;

    void dump(std::size_t start_octec, const DumpConfig& dump_config = DumpConfig{}) override;

    void pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) override;

private:
    long byte_count_ = 1;
    std::string property_name_;
    GribProperty* property_ = nullptr;
};


} // namespace grib_coder
