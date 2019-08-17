#pragma once

#include <grib_property/grib_property.h>
#include <grib_property/number_property.h>

#include <vector>
#include <unordered_map>
#include <memory>
#include <cstdio>

namespace grib_coder {

class GribSection : public std::enable_shared_from_this<GribSection> {
public:
	explicit GribSection(int section_number);
	GribSection(int section_number, long section_length);

	virtual ~GribSection();

	void setSectionLength(long length);
    long getSectionLength() const;

    int getSectionNumber() const;

	virtual bool parseFile(std::FILE* file, bool header_only=false) = 0;

	virtual bool decode(std::vector<std::shared_ptr<GribSection>> &section_list);

	GribProperty* getProperty(const std::string& name);

    void registerProperty(const std::string& name, GribProperty* property);

protected:
	std::unordered_map<std::string, GribProperty*> property_map_;

    NumberProperty<int> section_number_;
    NumberProperty<long> section_length_;
};

GribProperty* get_property_from_section_list(const std::string& name, std::vector<std::shared_ptr<GribSection>>& section_list);

} // namespace grib_coder