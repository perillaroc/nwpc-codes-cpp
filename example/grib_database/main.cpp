#include <cassert>

#include <grib_property/grib_table_database.h>

int main() {
	grib_coder::GribTableDatabase db;
	const auto table = db.getGribTable("4", "4.1.0");
	assert(table != nullptr);

	const auto missed_table = db.getGribTable("50", "1.1");
	assert(missed_table == nullptr);

    return 0;
}