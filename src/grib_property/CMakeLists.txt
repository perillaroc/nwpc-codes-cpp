project(grib_property)

add_library(grib_property STATIC)

target_sources(grib_property
        PRIVATE
        grib_property.cpp
        code_table_property.cpp
		number_property.cpp)


target_include_directories(grib_property
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        )

add_library(NwpcCodesCpp::GribProperty ALIAS grib_property)