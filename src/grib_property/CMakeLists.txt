project(grib_property)

find_package(OpenJPEG CONFIG REQUIRED)

if(OPENJPEG_FOUND)
	message(STATUS "Found OpenJPEG...${OPENJPEG_INCLUDE_DIRS} ${OPENJPEG_LIBRARIES}")
endif()

add_library(grib_property STATIC)

target_sources(grib_property
	PRIVATE
		src/grib_table.cpp
		src/grib_table_database.cpp
		src/grib_component.cpp
		src/property_component.cpp
        src/grib_property.cpp
		src/grib_property_container.cpp
        src/code_table_property.cpp
		src/string_property.cpp
		src/computed/computed_property.cpp
		src/computed/openjpeg_helper.cpp
		src/computed/openjpeg_decoder.cpp
		src/computed/data_values_property.cpp
		src/computed/data_date_property.cpp
		src/computed/data_time_property.cpp
		src/computed/level_property.cpp
		src/computed/type_of_level_property.cpp
		src/computed/packing_type_property.cpp
		src/computed/grid_type_property.cpp
		src/computed/step_range_property.cpp)


target_include_directories(grib_property
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/grib_property>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../grib_coder/include>
		$<INSTALL_INTERFACE:include>
		${GSL_INCLUDE_DIR}
)

target_link_libraries(grib_property
	PUBLIC
		# GSL::GSL
		openjp2
		fmt::fmt-header-only
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

install(TARGETS grib_property EXPORT NwpcCodesCppTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)