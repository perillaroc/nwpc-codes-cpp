project(grib_property)

find_package(OpenJPEG CONFIG REQUIRED)

if(OPENJPEG_FOUND)
	message(STATUS "Found OpenJPEG...${OPENJPEG_INCLUDE_DIRS} ${OPENJPEG_LIBRARIES}")
endif()

add_library(grib_property STATIC)

target_sources(grib_property
	PRIVATE
		grib_table.cpp
		grib_table_database.cpp
		grib_component.cpp
        grib_property.cpp
		grib_property_container.cpp
        code_table_property.cpp
		string_property.cpp
		computed/openjpeg_helper.cpp
		computed/openjpeg_decoder.cpp
		computed/data_values_property.cpp
		computed/data_date_property.cpp
		computed/data_time_property.cpp
		computed/level_property.cpp
		computed/type_of_level_property.cpp
		computed/packing_type_property.cpp
		computed/grid_type_property.cpp
		computed/step_range_property.cpp)


target_include_directories(grib_property
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../
		${OPENJPEG_INCLUDE_DIRS}
        )

target_link_libraries(grib_property
	PUBLIC
		${OPENJPEG_LIBRARIES}
		NwpcCodesCpp::vendor
)

# OPTION(OPENJPEG_STATIC "Use static version of OpenJPEG" ON)
IF(NOT OPENJPEG_BUILD_SHARED_LIBS)
message("Use OpenJPEG static")
target_compile_definitions(grib_property
	PUBLIC
		OPJ_STATIC
)
ELSE()
message("Use OpenJPEG dynamic")
ENDIF()

add_library(NwpcCodesCpp::GribProperty ALIAS grib_property)