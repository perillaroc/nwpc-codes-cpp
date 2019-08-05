#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cmath>

#include <grib_property/grib_table_database.h>

int main() {
	GribCoder::GribTableDatabase db;
	auto table = db.getGribTable("4", "4.1.0");

    return 0;
}