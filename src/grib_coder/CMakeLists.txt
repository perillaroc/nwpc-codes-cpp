project(grib_coder)

add_library(grib_coder STATIC)


find_package(OpenJPEG CONFIG REQUIRED)

if(OPENJPEG_FOUND)
	message(STATUS "Found OpenJPEG...${OPENJPEG_INCLUDE_DIRS} ${OPENJPEG_LIBRARIES}")
endif()

target_sources(grib_coder PRIVATE
	openjpeg_helper.cpp
	openjpeg_decoder.cpp
	grib_file_handler.cpp
	grib_message_handler.cpp
	grib_section.cpp
	sections/grib_section_0.cpp
	sections/grib_section_1.cpp
	sections/grib_section_3.cpp
	sections/grib_section_4.cpp
	sections/grib_section_5.cpp
	sections/grib_section_6.cpp
	sections/grib_section_7.cpp
	sections/grib_section_8.cpp
	number_convert.cpp
)

target_include_directories(grib_coder
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${OPENJPEG_INCLUDE_DIRS}
)

target_link_libraries(grib_coder
	PUBLIC
		${OPENJPEG_LIBRARIES}
		NwpcCodesCpp::GribProperty
)

target_compile_definitions(grib_coder
	PUBLIC
		OPJ_STATIC
)

add_library(NwpcCodesCpp::GribCoder ALIAS grib_coder)