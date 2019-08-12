project(grib_property)

add_library(grib_property STATIC)

target_sources(grib_property
        PRIVATE
        grib_property.cpp
        code_table_property.cpp
		number_property.cpp
		grib_table.cpp
		grib_table_database.cpp)


target_include_directories(grib_property
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        )

target_link_libraries(grib_property
		PUBLIC
		NwpcCodesCpp::vendor
)

add_library(NwpcCodesCpp::GribProperty ALIAS grib_property)