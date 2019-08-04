#pragma once

#include <grib_property/grib_property.h>

#include <vector>
#include <map>
#include <memory>
#include <cstdio>

namespace GribCoder {

class GribSection {
public:
	explicit GribSection(int section_number);
	GribSection(int section_number, long section_length);

	virtual ~GribSection();

	void setSectionLength(long length);

	virtual bool parseFile(std::FILE* file) = 0;

	virtual bool decode(std::vector<std::shared_ptr<GribSection>> section_list);

	GribProperty* getProperty(const std::string& name);

protected:
	virtual void init() = 0;

public:
	int section_number_;
	long section_length_;

protected:
	std::map<std::string, GribProperty*> property_map_;
};

} // namespace GribCoder