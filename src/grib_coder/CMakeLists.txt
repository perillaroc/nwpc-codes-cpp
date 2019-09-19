project(grib_coder)

add_library(grib_coder STATIC)



target_sources(grib_coder 
	PRIVATE
		grib_file_handler.cpp
		grib_message_handler.cpp
		grib_section.cpp
		grib_template.cpp
		template_component.cpp
		sections/grib_section_0.cpp
		sections/grib_section_1.cpp
		sections/grib_section_3.cpp
		sections/grib_section_4.cpp
		sections/grib_section_5.cpp
		sections/grib_section_6.cpp
		sections/grib_section_7.cpp
		sections/grib_section_8.cpp
		templates/template_4_0.cpp
		templates/template_4_1.cpp
		templates/template_4_8.cpp
		templates/template_4_11.cpp
)

target_include_directories(grib_coder
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
		$<INSTALL_INTERFACE:include>
		${OPENJPEG_INCLUDE_DIRS}
)

target_link_libraries(grib_coder
	PUBLIC
		NwpcCodesCpp::GribProperty
)

add_library(NwpcCodesCpp::GribCoder ALIAS grib_coder)

install(TARGETS grib_coder EXPORT NwpcCodesCppTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)