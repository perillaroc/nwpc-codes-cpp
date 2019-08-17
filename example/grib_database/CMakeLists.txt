project(grib_database)

add_executable(grib_database)

target_sources(grib_database
	PRIVATE
		main.cpp
)

target_link_libraries(
	grib_database
	PUBLIC
	NwpcCodesCpp::GribCoder
)