#include "grib_table_database.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <exception>

std::string& trim(std::string& s)
{
	if (s.empty())
	{
		return s;
	}

	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

namespace grib_coder {

GribTableDatabase::GribTableDatabase()
{
	auto eccodes_env = std::getenv("ECCODES_DEFINITION_PATH");
	if (eccodes_env == nullptr) {
		std::cerr << "Please set ECCODES_DEFINITION_PATH to use Grib Table Database." << std::endl;
	} else {
		eccodes_definition_path_.append(eccodes_env);
	}
}

GribTableDatabase::~GribTableDatabase()
{
}

std::shared_ptr<GribTable> GribTableDatabase::getGribTable(const std::string& table_version, const std::string& name)
{
	if (tables_.find(name) != tables_.end()) {
		return tables_[name];
	}
	auto table = loadGribTable(table_version, name);
	return table;
}

std::shared_ptr<GribTable> GribTableDatabase::loadGribTable(const std::string& table_version, const std::string& name)
{
	if (eccodes_definition_path_.empty()) {
		throw std::exception("ECCODES_DEFINITION_PATH must be set.");
	}
	std::filesystem::path table_path = eccodes_definition_path_;
	table_path = table_path.append("grib2").append("tables").append(table_version).append(name + ".table");

	std::ifstream table_stream;
	table_stream.open(table_path);
	if (!table_stream.is_open()) {
		std::cerr << "table file "<<name <<" can't be opened." <<std::endl;
		return std::shared_ptr<GribTable>();
	}
	auto table = std::make_shared<GribTable>();
	std::string line;
	while (std::getline(table_stream, line)) {

		line = trim(line);

		if (line[0] == '#') {
			continue;
		}

		GribTableRecord record;

		size_t pos = 0;
		pos = line.find_first_of(' ');
		if (pos == std::string::npos) {
			continue;
		}
        auto code_string = line.substr(0, pos);
		record.code_ = std::stoi(code_string);

        auto abbreviation_start_pos = pos + 1;
		size_t abbreviation_end_pos = line.find_first_of(' ', abbreviation_start_pos);
		if (abbreviation_end_pos == std::string::npos) {
			continue;
		}

        auto abbreviation_string = line.substr(abbreviation_start_pos, abbreviation_end_pos - abbreviation_start_pos);
        if (abbreviation_string != code_string) {
            record.abbreviation_ = abbreviation_string;
        }

        auto title_start_pos = abbreviation_end_pos + 1;
        auto title_end_pos = line.find_last_of("(");
        if (title_end_pos == std::string::npos) {
            record.title_ = line.substr(title_start_pos);
        } else {
            record.title_ = line.substr(title_start_pos, title_end_pos - title_start_pos - 1);
            auto unit_start_pos = title_end_pos + 1;
            auto unit_end_pos = line.find_last_of(")");
            if (unit_end_pos == std::string::npos) {
                throw std::exception("table record line has error");
            }
            record.units_ = line.substr(unit_start_pos, unit_end_pos - unit_start_pos);
        }

		table->records_.push_back(record);
	}

	table_stream.close();

	tables_[table_version + "." + name] = table;

	return table;
}

} // namespace grib_coder


