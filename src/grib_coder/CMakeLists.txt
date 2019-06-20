project(grib_coder)

add_library(grib_coder STATIC)

target_sources(grib_coder PRIVATE
	openjpeg_helper.cpp
	openjpeg_decoder.cpp
)

target_include_directories(grib_coder
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		D:/lib/cpp/openjpeg/openjpeg-v2.3.0-windows-x64/include/openjpeg-2.3
)

target_link_libraries(grib_coder
	PUBLIC
		D:/lib/cpp/openjpeg/openjpeg-v2.3.0-windows-x64/lib/openjp2.lib
)

add_library(NwpcCodesCpp::GribCoder ALIAS grib_coder)