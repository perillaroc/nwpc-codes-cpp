project(grib_property)

find_package(OpenJPEG CONFIG REQUIRED)

if(OPENJPEG_FOUND)
	message(STATUS "Found OpenJPEG...${OPENJPEG_INCLUDE_DIRS} ${OPENJPEG_LIBRARIES}")
endif()

add_library(grib_property STATIC)

target_sources(grib_property
	PRIVATE
		openjpeg_helper.cpp
		openjpeg_decoder.cpp
        grib_property.cpp
		grib_property_container.cpp
        code_table_property.cpp
		data_values_property.cpp
		level_property.cpp
		grib_table.cpp
		grib_table_database.cpp)


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

target_compile_definitions(grib_property
	PUBLIC
		OPJ_STATIC
)

add_library(NwpcCodesCpp::GribProperty ALIAS grib_property)