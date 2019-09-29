project(grib_coder)

add_library(grib_coder STATIC)



target_sources(grib_coder 
	PRIVATE
		src/grib_file_handler.cpp
		src/grib_message_handler.cpp
		src/grib_section.cpp
		src/grib_template.cpp
		src/template_component.cpp
		src/template_code_table_property.cpp
		src/sections/grib_section_0.cpp
		src/sections/grib_section_1.cpp
		src/sections/grib_section_3.cpp
		src/sections/grib_section_4.cpp
		src/sections/grib_section_5.cpp
		src/sections/grib_section_6.cpp
		src/sections/grib_section_7.cpp
		src/sections/grib_section_8.cpp
		src/templates/template_4_0.cpp
		src/templates/template_4_1.cpp
		src/templates/template_4_8.cpp
		src/templates/template_4_11.cpp
)

target_include_directories(grib_coder
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
		${OPENJPEG_INCLUDE_DIRS}
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/grib_coder>
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