#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>

namespace GribCoder{

class GribTableRecord {
public:
	bool isValid() {
		return code_ != -1;
	}

	int code_ = -1;
	std::string figure_;
	std::string description_;
};

class GribTable {
public:
	std::vector<GribTableRecord> records_;
};

class GribTableDatabase {
public:
	GribTableDatabase();
	~GribTableDatabase();
	
	std::shared_ptr<GribTable> getGribTable(const std::string& table_version, const std::string& name);

private:
	std::shared_ptr<GribTable> loadGribTable(const std::string& table_version, const std::string& name);

	// table_version.table_id
	std::map<std::string, std::shared_ptr<GribTable>> tables_;
	std::string eccodes_definition_path_;
};


} // namespace GribCoder