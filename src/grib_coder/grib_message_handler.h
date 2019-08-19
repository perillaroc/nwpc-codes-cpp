#pragma once

#include "grib_section.h"
#include <grib_property/grib_table_database.h>
#include <grib_property/grib_property_container.h>

namespace grib_coder {

class GribMessageHandler: public GribPropertyContainer {
public:
	GribMessageHandler(std::shared_ptr<GribTableDatabase> db, bool header_only = false);
	~GribMessageHandler();

	bool parseFile(std::FILE* file);

	void setLong(const std::string& key, long value) override;
	long getLong(const std::string& key) override;

	void setDouble(const std::string& key, double value) override;
	double getDouble(const std::string& key) override;

	void setString(const std::string& key, const std::string& value) override;
	std::string getString(const std::string& key) override;

private:
	bool parseNextSection(std::FILE* file);

	std::shared_ptr<GribSection> getSection(int section_number, size_t begin_pos = 0);

	GribProperty* getProperty(const std::string& name);

	std::vector < std::shared_ptr<GribSection>> section_list_;
	std::shared_ptr<GribTableDatabase> table_database_;

	bool header_only_ = false;
};

} // namespace grib_coder

