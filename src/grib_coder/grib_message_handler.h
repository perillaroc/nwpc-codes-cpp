#pragma once

#include <cstdio>
#include <vector>
#include <memory>

#include "grib_section.h"
#include <grib_property/grib_table_database.h>

namespace GribCoder {

class GribMessageHandler {
public:
	GribMessageHandler(std::shared_ptr<GribTableDatabase> db);
	~GribMessageHandler();

	bool parseFile(std::FILE* file);

	void setLong(const std::string& key, long value);
	long getLong(const std::string& key);

	void setDouble(const std::string& key, double value);
	double getDouble(const std::string& key);

	void setString(const std::string& key, const std::string& value);
	std::string getString(const std::string& key);

private:
	bool parseNextSection(std::FILE* file);

	std::shared_ptr<GribSection> getSection(int section_number, size_t begin_pos = 0);

	GribProperty* getProperty(const std::string& name);

	std::vector < std::shared_ptr<GribSection>> section_list_;
	std::shared_ptr<GribTableDatabase> table_database_;
};

} // namespace GribCoder

