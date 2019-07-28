#pragma once

#include "grib_property.h"

namespace GribCoder {

class CodeTableProperty: public GribProperty {
public:
    CodeTableProperty();
    ~CodeTableProperty();

    void setLong(long value) override;
    long getLong() override;

    void setDouble(double value) override;
    double getDouble() override;

    void setString(const std::string &value) override;
    std::string getString() override;

    void setCodeTableId(const std::string &code_table_id);

private:
    std::string code_table_id_ = "";
    size_t octet_bytes_ = 1;
    long value_ = 255;
};


} // namespace GribCoder
