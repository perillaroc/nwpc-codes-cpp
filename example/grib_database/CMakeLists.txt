project(grib_database)

add_executable(grib_database
    main.cpp
	)

target_link_libraries(
	grib_database
	PUBLIC
	NwpcCodesCpp::GribCoder
)