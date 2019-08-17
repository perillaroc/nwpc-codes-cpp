#pragma once 

#include "grib_section.h"
#include "grib_section_5.h"

#include <vector>
#include <cstdint>
#include <memory>

namespace grib_coder {

class GribSection7 : public GribSection {
public:
	GribSection7();
	explicit GribSection7(int section_length);
	~GribSection7();

	bool parseFile(std::FILE* file) override;

	bool decode(std::vector<std::shared_ptr<GribSection>> section_list) override;

	bool decodeValues(std::vector<std::shared_ptr<GribSection>> section_list);

private:
	void init() override;

public:
	std::vector<unsigned char> raw_value_bytes_;
	std::vector<double> code_values_;
};

} // namespace grib_coder